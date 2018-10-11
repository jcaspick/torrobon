#include "EnemyBullet.h"
#include "Context.h"

EnemyBullet::EnemyBullet(Context* context) :
	m_context(context),
	m_active(true)
{
	m_sprite.setTexture(
		*m_context->m_textureHolder->GetTexture("redBullet"));
	m_sprite.setOrigin(
		m_sprite.getTextureRect().width / 2,
		m_sprite.getTextureRect().height / 2);
	m_rectSize = { 9, 9 };
}

EnemyBullet::~EnemyBullet() {}

void EnemyBullet::Update(float dt) {
	Move(m_direction * m_speed * dt);
	m_sprite.setPosition(m_position);
	UpdateRect();
}

void EnemyBullet::Draw() {
	m_context->m_window->draw(m_sprite);
}

void EnemyBullet::OnDeath() {
	m_context->m_effectManager->CreateEffect(
		EffectType::SmallRedExplosion2, m_position);
}

void EnemyBullet::Move(const sf::Vector2f& delta) {
	m_position += delta;
}

void EnemyBullet::UpdateRect() {
	m_rect.left = m_position.x - m_rectSize.x / 2;
	m_rect.top = m_position.y - m_rectSize.y / 2;
	m_rect.width = m_rectSize.x;
	m_rect.height = m_rectSize.y;
}

// setters
void EnemyBullet::SetSpeed(float speed) { m_speed = speed; }
void EnemyBullet::SetPosition(const sf::Vector2f& pos) { m_position = pos; }
void EnemyBullet::SetDirection(const sf::Vector2f& dir) { m_direction = dir; }
void EnemyBullet::SetActive(bool active) { m_active = active; }

// getters
bool EnemyBullet::IsActive() { return m_active; }
float EnemyBullet::GetSpeed() { return m_speed; }
sf::Vector2f EnemyBullet::GetPosition() { return m_position; }
sf::Vector2f EnemyBullet::GetDirection() { return m_direction; }
sf::FloatRect EnemyBullet::GetRect() { return m_rect; }