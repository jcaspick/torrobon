#include "Enemy.h"
#include "Context.h"

Enemy::Enemy(Context* context) :
	m_spriteSheet("config/bot1.cfg"),
	m_context(context),
	m_speed(150.0f),
	m_elapsed(0.0f),
	m_directionInterval(0.5f),
	m_health(8)
{
	m_spriteSheet.SetScale({ 2.0f, 2.0f });
}

Enemy::~Enemy() {};

void Enemy::Update(float dt) {
	m_elapsed += dt;
	if (m_elapsed >= m_directionInterval) {
		m_elapsed -= m_directionInterval;
		ChooseDirection();
	}

	SetPosition({
		m_position.x + m_direction.x * m_speed * dt,
		m_position.y + m_direction.y * m_speed * dt
	});

	m_spriteSheet.SetPosition(m_position);
	m_spriteSheet.Update(dt);
	UpdateAABB();
}

void Enemy::Draw() {
	m_spriteSheet.Draw(m_context->m_window);
	/*sf::RectangleShape debug({ 0,0 });
	debug.setSize({ m_AABB.width * 2, m_AABB.height * 2 });
	debug.setPosition({ m_position.x - (m_AABB.width),
		m_position.y - (m_AABB.height) });
	debug.setFillColor(sf::Color(0, 255, 0, 100));
	m_context->m_window->draw(debug);*/
}

void Enemy::SetPosition(const sf::Vector2f& pos) {
	m_position = pos;
}

void Enemy::Damage(int damage) {
	m_health -= damage;
}

int Enemy::GetHealth() { return m_health; }
sf::Vector2f Enemy::GetPosition() { return m_position; }
sf::FloatRect Enemy::GetAABB() { return m_AABB; }

void Enemy::ChooseDirection() {
	if (abs(m_context->m_playerPos->x - m_position.x)
		> abs(m_context->m_playerPos->y - m_position.y))
	{
		if (m_context->m_playerPos->x > m_position.x) {
			m_direction = { 1, 0 };
			m_spriteSheet.SetAnimation("right");
		}
		else {
			m_direction = { -1, 0 };
			m_spriteSheet.SetAnimation("left");
		}
	}
	else {
		if (m_context->m_playerPos->y > m_position.y) {
			m_direction = { 0, 1 };
			m_spriteSheet.SetAnimation("down");
		}
		else {
			m_direction = { 0, -1 };
			m_spriteSheet.SetAnimation("up");
		}
	}
}

void Enemy::UpdateAABB() {
	m_AABB = sf::FloatRect(
		m_position.x - m_spriteSheet.GetSize().x,
		m_position.y,
		m_spriteSheet.GetSize().x * 2,
		m_spriteSheet.GetSize().y);
}