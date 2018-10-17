#include "GS_Game.h"
#include "StateManager.h"

GS_Game::GS_Game(StateManager* stateMgr) :
	GameState(stateMgr),
	m_world({ 1200, 800 }, 8),
	m_bulletManager(m_stateMgr->GetContext()),
	m_entityManager(m_stateMgr->GetContext()),
	m_effectManager(m_stateMgr->GetContext()),
	m_spawnTimer(12.0f),
	m_spawnInterval(1.0f),
	m_difficultyTimer(0.0f),
	m_difficultyInterval(10.0f),
	m_debugView(m_stateMgr->GetContext())
{
	m_stateMgr->GetContext()->m_world = &m_world;
	m_stateMgr->GetContext()->m_bulletManager = &m_bulletManager;
	m_stateMgr->GetContext()->m_entityManager = &m_entityManager;
	m_stateMgr->GetContext()->m_effectManager = &m_effectManager;

	m_view = m_stateMgr->GetContext()->m_window->getDefaultView();

	m_font.loadFromFile("fonts/BMjapan.TTF");
	m_scoreText.setFont(m_font);
	m_scoreText.setPosition(32, 32);
}

GS_Game::~GS_Game() {}

void GS_Game::OnCreate() {
	m_player = new Player(m_stateMgr->GetContext());
	m_stateMgr->GetContext()->m_player = m_player;

	m_player->SetPosition({ 
		m_stateMgr->GetContext()->m_world->GetSize().x / 2,
		m_stateMgr->GetContext()->m_world->GetSize().y / 2 });

	m_bg.setFillColor(sf::Color(90, 90, 90, 255));
	m_bg.setPosition({ 0,0 });
	m_bg.setSize((sf::Vector2f)m_stateMgr->GetContext()->m_world->GetSize());
}

void GS_Game::OnDestroy() {
	delete m_player;
}

void GS_Game::OnEnable() {

}

void GS_Game::OnDisable() {

}

void GS_Game::Update(float dt) {
	// update entities
	m_player->Update(dt);
	m_entityManager.Update(dt);
	m_bulletManager.Update(dt);
	m_effectManager.Update(dt);

	// set view
	SetView();

	// enemy spawning logic
	m_spawnTimer += dt;
	while (m_spawnTimer > m_spawnInterval) {
		m_spawnTimer -= m_spawnInterval;

		float spawnX = rand() % (int)m_stateMgr->GetContext()->
			m_world->GetSize().x;
		float spawnY = rand() % (int)m_stateMgr->GetContext()->
			m_world->GetSize().y;
		if (rand() % 2) {
		if (rand() % 2) { spawnX = 40; }
		else { spawnX = m_stateMgr->GetContext()->
			m_world->GetSize().x - 40; }
		}
		else {
		if (rand() % 2) { spawnY = 40; }
		else { spawnY = m_stateMgr->GetContext()->
			m_world->GetSize().y - 40; }
		}

		m_stateMgr->GetContext()->m_entityManager->
			Spawn(EntityType::Drone, { spawnX, spawnY });
	}

	// difficulty increase + stompy spawn
	m_difficultyTimer += dt;
	while (m_difficultyTimer > m_difficultyInterval) {
		m_difficultyTimer -= m_difficultyInterval;
		m_spawnInterval = std::max(m_spawnInterval - 0.2f, 0.5f);

		float spawnX, spawnY;
		if (rand() % 2) spawnX = 90;
		else spawnX = m_stateMgr->GetContext()->
			m_world->GetSize().x - 90;
		if (rand() % 2) spawnY = 90;
		else spawnY = m_stateMgr->GetContext()->
			m_world->GetSize().y - 90;
		m_stateMgr->GetContext()->m_entityManager->Spawn(
			EntityType::Stompy, { spawnX, spawnY });
	}

	// game over
	if (!m_player->IsAlive()) {
		m_gameOverTimer += dt;
		if (m_gameOverTimer > 2) {
			m_stateMgr->SetState(StateType::GameOver);
			
		}
	}

	// score counter
	m_scoreText.setString("SCORE: " + 
		std::to_string(m_stateMgr->GetContext()->
			m_player->GetScore()));
}

void GS_Game::Draw() {
	m_stateMgr->GetContext()->m_window->setView(m_view);

	m_stateMgr->GetContext()->m_window->draw(m_bg);
	m_player->Draw();
	m_entityManager.Draw();
	m_bulletManager.Draw();
	m_world.Draw(m_stateMgr->GetContext()->m_window);
	m_effectManager.Draw();
	//m_debugView.Draw();

	// switch view to draw UI elements
	m_stateMgr->GetContext()->m_window->setView(
		m_stateMgr->GetContext()->m_window->getDefaultView());
	m_stateMgr->GetContext()->m_window->draw(m_scoreText);

	// switch back to preserve correct mouse coordinates
	m_stateMgr->GetContext()->m_window->setView(m_view);
}

void GS_Game::SetView() {
	sf::Vector2f viewSize = m_view.getSize();
	sf::Vector2f viewCenter = m_player->GetPosition();

	if (m_world.GetSize().x <= viewSize.x) {
		viewCenter.x = m_world.GetSize().x / 2;
	}
	else {
		if (viewCenter.x + viewSize.x / 2 > m_world.GetSize().x)
			viewCenter.x = m_world.GetSize().x - viewSize.x / 2;
		if (viewCenter.x - viewSize.x / 2 < 0)
			viewCenter.x = viewSize.x / 2;
	}
	if (m_world.GetSize().y <= viewSize.y) {
		viewCenter.y = m_world.GetSize().y / 2;
	}
	else {
		if (viewCenter.y + viewSize.y / 2 > m_world.GetSize().y)
			viewCenter.y = m_world.GetSize().y - viewSize.y / 2;
		if (viewCenter.y - viewSize.y / 2 < 0)
			viewCenter.y = viewSize.y / 2;
	}
	
	m_view.setCenter(viewCenter);
}