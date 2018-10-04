#include "GS_Menu.h"
#include "StateManager.h"

GS_Menu::GS_Menu(StateManager* stateMgr) : GameState(stateMgr) {}

GS_Menu::~GS_Menu() {}

void GS_Menu::OnCreate() {
	m_sprite.setTexture(
		*m_stateMgr->GetContext()->m_textureHolder->GetTexture("title"));
	m_sprite.setOrigin(
		m_sprite.getTexture()->getSize().x / 2,
		m_sprite.getTexture()->getSize().y / 2);
	m_sprite.setPosition(
		m_stateMgr->GetContext()->m_window->getSize().x / 2,
		m_stateMgr->GetContext()->m_window->getSize().y / 2);
}

void GS_Menu::OnDestroy() {}
void GS_Menu::OnEnable() {}
void GS_Menu::OnDisable() {}

void GS_Menu::Update(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		m_stateMgr->SetState(StateType::Game);
	}
}

void GS_Menu::Draw() {
	m_stateMgr->GetContext()->m_window->draw(m_sprite);
}