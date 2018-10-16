#include "StaticBullet.h"
#include "Context.h"

StaticBullet::StaticBullet(Context* context, sf::Vector2f pos, 
	sf::Vector2f dir, float speed, std::string& texture) :
	Bullet(context, pos, dir, speed)
{
	m_sprite.setTexture(*m_context->m_textureHolder->GetTexture(texture));
}

StaticBullet::~StaticBullet() {}

void StaticBullet::Update(float dt) {
	Bullet::Update(dt);
	m_sprite.setPosition(m_position);
}

void StaticBullet::Draw() {
	m_context->m_window->draw(m_sprite);
}