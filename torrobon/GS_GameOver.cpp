#include "GS_GameOver.h"
#include "StateManager.h"

GS_GameOver::GS_GameOver(StateManager* stateMgr) : GameState(stateMgr) {}

GS_GameOver::~GS_GameOver() {}

void GS_GameOver::OnCreate() {
	m_sprite.setTexture(
		*m_stateMgr->GetContext()->m_textureHolder->GetTexture("gameOver"));
	m_sprite.setOrigin(
		m_sprite.getTexture()->getSize().x / 2,
		m_sprite.getTexture()->getSize().y / 2);
	m_sprite.setPosition(
		m_stateMgr->GetContext()->m_window->getSize().x / 2,
		m_stateMgr->GetContext()->m_window->getSize().y / 2);
}

void GS_GameOver::OnDestroy() {}
void GS_GameOver::OnEnable() {}
void GS_GameOver::OnDisable() {}

void GS_GameOver::Update(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		m_stateMgr->SetState(StateType::Game);
	}
}

void GS_GameOver::Draw() {
	m_stateMgr->GetContext()->m_window->draw(m_sprite);
}