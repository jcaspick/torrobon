#include "Entity.h"
#include "Context.h"

Entity::Entity(Context* context) :
	m_context(context),
	m_health(1)
{}

Entity::~Entity() {}

void Entity::AddDamage(const float& damage) {
	m_health -= damage;
}

void Entity::Move(const sf::Vector2f& delta) {
	SetPosition({
		m_position.x + delta.x,
		m_position.y + delta.y });
}

void Entity::OnDeath() {}

// setters
void Entity::SetPosition(const sf::Vector2f& pos) { m_position = pos; }
void Entity::SetCollisionSize(const sf::Vector2f& size) { m_rectSize = size; }
void Entity::SetCollisionOffset(const sf::Vector2f& offset) { m_rectOffset = offset; }

// getters
sf::Vector2f Entity::GetPosition() { return m_position; }
sf::Vector2f Entity::GetCollisionSize() { return m_rectSize; }
sf::Vector2f Entity::GetCollisionOffset() { return m_rectOffset; }
sf::FloatRect Entity::GetRect() { return m_rect; }
float Entity::GetHealth() { return m_health; }
unsigned int Entity::GetCollisionMask() { return m_collisionMask; }

void Entity::UpdateRect() {
	float posX, posY;

	switch (m_rectAnchor)
	{
	case Anchor::Center:
		posX = m_position.x - m_rectSize.x / 2;
		posY = m_position.y - m_rectSize.y / 2;
		break;
	case Anchor::Bottom:
		posX = m_position.x - m_rectSize.x / 2;
		posY = m_position.y - m_rectSize.y;
		break;
	}

	m_rect = sf::FloatRect(
		posX + m_rectOffset.x,
		posY + m_rectOffset.y,
		m_rectSize.x,
		m_rectSize.y);
}