#include "Player.h"
#include "Utilities.h"
#include "Context.h"

Player::Player(Context* context) :
	m_context(context),
	m_speed(250.0f),
	m_texture("player"),
	m_elapsed(0),
	m_shotInterval(0.05f),
	m_alive(true),
	m_rectSize(18, 32),
	m_hitboxSize(6, 6)
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
			m_context->m_bulletManager->AimedBullet(
				true, BulletType::PlayerBasic, m_position,
				Utils::Vec2Rot(m_mousePos - m_position), 800.0f, 2.0f);
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

void Player::AddScore(int score) { m_score += score; }

void Player::UpdateAABB() {
	m_rect = sf::FloatRect(
		m_position.x - m_rectSize.x / 2,
		m_position.y - m_rectSize.y / 2,
		m_rectSize.x,
		m_rectSize.y);
	m_hitbox = sf::FloatRect(
		m_position.x - m_hitboxSize.x / 2,
		m_position.y - m_hitboxSize.y / 2,
		m_hitboxSize.x,
		m_hitboxSize.y);
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
	sf::Vector2f worldSize = m_context->m_world->GetSize();
	float thickness = m_context->m_world->GetWallThickness();

	if (m_position.x < thickness + m_rectSize.x / 2)
		m_position.x = thickness + m_rectSize.x / 2;
	if (m_position.y < thickness + m_rectSize.y / 2)
		m_position.y = thickness + m_rectSize.y / 2;
	if (m_position.x > worldSize.x - thickness - m_rectSize.x / 2)
		m_position.x = worldSize.x - thickness - m_rectSize.x / 2;
	if (m_position.y > worldSize.y - thickness - m_rectSize.y / 2)
		m_position.y = worldSize.y - thickness - m_rectSize.y / 2;
}

// getters
sf::Vector2f Player::GetPosition() { return m_position; }
sf::FloatRect Player::GetRect() { return m_rect; }
sf::FloatRect Player::GetHitbox() { return m_hitbox; }
int Player::GetScore() { return m_score; }
bool Player::IsAlive() { return m_alive; }

// setters
void Player::SetPosition(sf::Vector2f pos) { m_position = pos; }