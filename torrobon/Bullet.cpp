#include "Bullet.h"
#include "Context.h"

Bullet::Bullet(Context* context, sf::Vector2f pos, sf::Vector2f dir, float speed) :
	m_context(context),
	m_position(pos),
	m_direction(dir),
	m_speed(speed),
	m_alive(true)
{}

Bullet::~Bullet() {}

void Bullet::Update(float dt) {
	Move(m_direction * m_speed * dt);
	UpdateRect();
}

void Bullet::OnDeath() {}

void Bullet::Move(sf::Vector2f delta) {
	SetPosition(m_position + delta);
}

void Bullet::UpdateRect() {
	m_rect = sf::FloatRect(
		m_position.x - m_rectSize.x / 2,
		m_position.y - m_rectSize.y / 2,
		m_rectSize.x,
		m_rectSize.y);
}

// setters
void Bullet::SetPosition(sf::Vector2f pos) { m_position = pos; }
void Bullet::SetDirection(sf::Vector2f dir) { m_direction = dir; }
void Bullet::SetAlive(bool alive) { m_alive = alive; }
void Bullet::SetSpeed(float speed) { m_speed = speed; }

// getters
sf::Vector2f Bullet::GetPosition() { return m_position; }
sf::Vector2f Bullet::GetDirection() { return m_direction; }
sf::FloatRect Bullet::GetRect() { return m_rect; }
bool Bullet::IsAlive() { return m_alive; }