#include "Player.h"
#include "Utilities.h"
#include "Context.h"

Player::Player(Context* context) :
	m_context(context),
	m_speed(250.0f),
	m_texture("player"),
	m_elapsed(0),
	m_shotInterval(0.05f),
	m_alive(true)
{
	m_sprite.setTexture(*context->m_textureHolder->GetTexture(m_texture));
	m_sprite.setOrigin(
		m_sprite.getTexture()->getSize().x / 2,
		m_sprite.getTexture()->getSize().y / 2);
	m_sprite.setPosition(m_position);
}

Player::~Player() {}

void Player::Update(float dt) {
	if (!m_alive) return;
	m_elapsed += dt;
	if (m_elapsed >= m_shotInterval) {
		if (m_shooting) {
			m_context->m_bulletManager->CreateBullet(
				m_position, 
				Utils::Vec2Rot(m_mousePos - m_position));
			m_elapsed = 0;
		}
	}

	HandleInput();
	m_position.x += m_deltaPos.x * dt * m_speed;
	m_position.y += m_deltaPos.y * dt * m_speed;
	m_sprite.setPosition(m_position);
	EnforceWorldBoundary();
	UpdateAABB();
}

void Player::Draw() {
	if (!m_alive) return;
	m_context->m_window->draw(m_sprite);
}

void Player::Kill() {
	m_alive = false;
}

void Player::SetPosition(sf::Vector2f pos) {
	m_position = pos;
}

sf::Vector2f Player::GetPosition() { return m_position; }

sf::FloatRect Player::GetAABB() {
	return m_AABB;
}

bool Player::IsAlive() { return m_alive; }

void Player::AddScore(int score) { m_score += score; }

int Player::GetScore() { return m_score; }

void Player::UpdateAABB() {
	m_AABB = sf::FloatRect(
		m_position.x - m_sprite.getTexture()->getSize().x / 2,
		m_position.y - m_sprite.getTexture()->getSize().y / 2,
		m_sprite.getTexture()->getSize().x,
		m_sprite.getTexture()->getSize().y);
}

void Player::HandleInput() {
	m_deltaPos = { 0, 0 };
	m_shooting = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_deltaPos.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_deltaPos.x -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_deltaPos.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_deltaPos.x += 1;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		m_shooting = true;
		m_mousePos = m_context->m_window->
			mapPixelToCoords(sf::Mouse::getPosition(*m_context->m_window));
	}
}

void Player::EnforceWorldBoundary() {
	// TODO make this less bad
	float offsetX = 8 + m_sprite.getTextureRect().width / 2;
	float offsetY = 8 + m_sprite.getTextureRect().height / 2;

	if (m_position.x > m_context->m_window->getSize().x - offsetX)
		m_position.x = m_context->m_window->getSize().x - offsetX;
	if (m_position.y > m_context->m_window->getSize().y - offsetY)
		m_position.y = m_context->m_window->getSize().y - offsetY;
	if (m_position.x < offsetX) m_position.x = offsetX;
	if (m_position.y < offsetY) m_position.y = offsetY;
}