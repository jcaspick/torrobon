#include "GS_GameOver.h"
#include "StateManager.h"

GS_GameOver::GS_GameOver(StateManager* stateMgr) : 
	GameState(stateMgr) 
{
	m_transparent = true;
}

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
		m_stateMgr->RemoveState(StateType::Game);
		// this actually resets the game in a hacky way
		// the state is set to the main menu, which immediately
		// captures the spacebar event and begins the game
		m_stateMgr->SetState(StateType::Menu);
	}
}

void GS_GameOver::Draw() {
	sf::RectangleShape overlay = sf::RectangleShape(
		(sf::Vector2f)m_stateMgr->GetContext()->m_window->getSize());
	overlay.setFillColor(sf::Color(0, 0, 0, 150));
	m_stateMgr->GetContext()->m_window->draw(overlay);
	m_stateMgr->GetContext()->m_window->draw(m_sprite);
}