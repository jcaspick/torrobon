#include "DirectionalBullet.h"
#include "Utilities.h"
#include "BulletManager.h"
#include "Context.h"
#include "TextureHolder.h"

DirectionalBullet::DirectionalBullet(Context* context, sf::Vector2f pos, 
	sf::Vector2f dir, float speed, const std::string& config) :
	Bullet(context, pos, dir, speed),
	m_sprite(m_context->m_textureHolder)
{
	m_sprite.LoadConfig(config);
	m_sprite.SetDirection(Utils::Vec2Rot(dir));
	m_rectSize = static_cast<sf::Vector2f>(m_sprite.GetFrameSize());
}

DirectionalBullet::~DirectionalBullet() {};

void DirectionalBullet::Update(float dt) {
	Bullet::Update(dt);
	m_sprite.SetPosition(m_position);
}

void DirectionalBullet::Draw() {
	m_sprite.Draw(m_context->m_window);
}