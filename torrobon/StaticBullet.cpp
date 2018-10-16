#include "StaticBullet.h"
#include "Context.h"

StaticBullet::StaticBullet(Context* context, sf::Vector2f pos, 
	sf::Vector2f dir, float speed, const std::string& texture) :
	Bullet(context, pos, dir, speed)
{
	m_sprite.setTexture(*m_context->m_textureHolder->GetTexture(texture));
	m_sprite.setOrigin(
		m_sprite.getTexture()->getSize().x / 2,
		m_sprite.getTexture()->getSize().y / 2);
	m_rectSize = static_cast<sf::Vector2f>(m_sprite.getTexture()->getSize());
}

StaticBullet::~StaticBullet() {}

void StaticBullet::Update(float dt) {
	Bullet::Update(dt);
	m_sprite.setPosition(m_position);
}

void StaticBullet::Draw() {
	m_context->m_window->draw(m_sprite);
}

void StaticBullet::OnDeath() {
	m_context->m_effectManager->
		CreateEffect(EffectType::SmallRedExplosion2, m_position);
}