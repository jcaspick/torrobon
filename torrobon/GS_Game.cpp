#include "GS_Game.h"
#include "StateManager.h"

GS_Game::GS_Game(StateManager* stateMgr) :
	GameState(stateMgr),
	m_bulletManager(m_stateMgr->GetContext()),
	m_enemyManager(m_stateMgr->GetContext()),
	m_effectManager(m_stateMgr->GetContext()),
	m_spawnTimer(12.0f),
	m_spawnInterval(3.0f),
	m_difficultyTimer(0.0f),
	m_difficultyInterval(10.0f)
{
	m_stateMgr->GetContext()->m_bulletManager = &m_bulletManager;
	m_stateMgr->GetContext()->m_enemyManager = &m_enemyManager;
	m_stateMgr->GetContext()->m_effectManager = &m_effectManager;
}

GS_Game::~GS_Game() {}

void GS_Game::OnCreate() {
	m_player = new Player(m_stateMgr->GetContext());
	m_stateMgr->GetContext()->m_player = m_player;

	m_player->SetPosition({ 
		(float)m_stateMgr->GetContext()->m_window->getSize().x / 2,
		(float)m_stateMgr->GetContext()->m_window->getSize().y / 2 });
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
	m_stateMgr->GetContext()->m_enemyManager->Update(dt);
	m_stateMgr->GetContext()->m_bulletManager->Update(dt);
	m_stateMgr->GetContext()->m_effectManager->Update(dt);

	// enemy spawning logic
	m_spawnTimer += dt;
	while (m_spawnTimer > m_spawnInterval) {
		m_spawnTimer -= m_spawnInterval;

		float spawnX = rand() % m_stateMgr->GetContext()->
			m_window->getSize().x;
		float spawnY = rand() % m_stateMgr->GetContext()->
			m_window->getSize().y;
		if (rand() % 2) {
		if (rand() % 2) { spawnX = 40; }
		else { spawnX = m_stateMgr->GetContext()->
			m_window->getSize().x - 40; }
		}
		else {
		if (rand() % 2) { spawnY = 40; }
		else { spawnY = m_stateMgr->GetContext()->
			m_window->getSize().y - 40; }
		}

		m_stateMgr->GetContext()->m_enemyManager->
			SpawnEnemy({ spawnX, spawnY });
	}

	// difficulty increase logic
	m_difficultyTimer += dt;
	while (m_difficultyTimer > m_difficultyInterval) {
		m_difficultyTimer -= m_difficultyInterval;
		m_spawnTimer += 5;
		m_spawnInterval = std::max(m_spawnInterval - 0.2f, 0.5f);
	}

	// game over
	if (!m_player->IsAlive()) {
		m_gameOverTimer += dt;
		if (m_gameOverTimer > 2) {
			m_stateMgr->SetState(StateType::GameOver);
			
		}
	}
}

void GS_Game::Draw() {
	m_player->Draw();
	m_stateMgr->GetContext()->m_enemyManager->Draw();
	m_stateMgr->GetContext()->m_bulletManager->Draw();
	m_stateMgr->GetContext()->m_effectManager->Draw();

	sf::Vector2f wind = (sf::Vector2f)m_stateMgr->GetContext()->m_window->getSize();

	sf::RectangleShape wallH = sf::RectangleShape({ wind.x, 8 });
	sf::RectangleShape wallV = sf::RectangleShape({ 8, wind.y });

	wallH.setPosition({ 0, 0 });
	m_stateMgr->GetContext()->m_window->draw(wallH);
	wallH.setPosition({ 0, wind.y - 8 });
	m_stateMgr->GetContext()->m_window->draw(wallH);

	wallV.setPosition({ 0, 0 });
	m_stateMgr->GetContext()->m_window->draw(wallV);
	wallV.setPosition({ wind.x - 8, 0 });
	m_stateMgr->GetContext()->m_window->draw(wallV);
}