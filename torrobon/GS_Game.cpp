#include "GS_Game.h"
#include "StateManager.h"

GS_Game::GS_Game(StateManager* stateMgr) :
	GameState(stateMgr)
{}

GS_Game::~GS_Game() {}

void GS_Game::OnCreate() {
	m_player = new Player(m_stateMgr->GetContext());
	m_stateMgr->GetContext()->m_playerPos = &m_playerPos;
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
}

void GS_Game::Draw() {

}