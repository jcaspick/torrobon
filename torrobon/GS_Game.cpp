#include "GS_Game.h"
#include "StateManager.h"

GS_Game::GS_Game(StateManager* stateMgr) :
	GameState(stateMgr),
	m_elapsed(0.0f),
	m_spawnInterval(3.0f)
{}

GS_Game::~GS_Game() {}

void GS_Game::OnCreate() {
	m_player = new Player(m_stateMgr->GetContext());
	m_stateMgr->GetContext()->m_playerPos = &m_playerPos;

	m_player->SetPosition({ 200, 200 });
}

void GS_Game::OnDestroy() {
	delete m_player;
}

void GS_Game::OnEnable() {

}

void GS_Game::OnDisable() {

}

void GS_Game::Update(float dt) {
	m_player->Update(dt);
	m_stateMgr->GetContext()->m_enemyManager->Update(dt);
	m_stateMgr->GetContext()->m_bulletManager->Update(dt);
	m_stateMgr->GetContext()->m_effectManager->Update(dt);
	m_playerPos = m_player->GetPosition();

	m_elapsed += dt;
	while (m_elapsed > m_spawnInterval) {
		m_elapsed -= m_spawnInterval;

		float spawnX = rand() % m_stateMgr->GetContext()->
			m_window->getSize().x;
		float spawnY = rand() % m_stateMgr->GetContext()->
			m_window->getSize().y;
		if (rand() % 2) {
		if (rand() % 2) { spawnX = 0; }
		else { spawnX = m_stateMgr->GetContext()->
			m_window->getSize().x; }
		}
		else {
		if (rand() % 2) { spawnY = 0; }
		else { spawnY = m_stateMgr->GetContext()->
			m_window->getSize().y; }
		}

		m_stateMgr->GetContext()->m_enemyManager->
			SpawnEnemy({ spawnX, spawnY });
	}
}

void GS_Game::Draw() {
	m_player->Draw();
	m_stateMgr->GetContext()->m_enemyManager->Draw();
	m_stateMgr->GetContext()->m_bulletManager->Draw();
	m_stateMgr->GetContext()->m_effectManager->Draw();
}