#include "Bullet.h"
#include "Utilities.h"
#include "BulletManager.h"
#include "Context.h"
#include "TextureHolder.h"

Bullet::Bullet(BulletManager* bulletMgr) :
	m_bulletMgr(bulletMgr),
	m_speed(900),
	m_hitRadius(6),
	m_sprite(m_bulletMgr->GetContext()->m_textureHolder),
	m_deleteFlag(false)
{
	m_sprite.LoadConfig("config/directionalBullet.cfg");
}

Bullet::~Bullet() {};

void Bullet::Update(float dt) {
	SetPosition({
		m_position.x + m_direction.x * m_speed * dt,
		m_position.y + m_direction.y * m_speed * dt
	});
	m_sprite.SetPosition(m_position);
	UpdateAABB();
}

void Bullet::Draw(sf::RenderWindow* window) {
	m_sprite.Draw(window);
	/*sf::RectangleShape debug({ m_hitRadius * 2, m_hitRadius * 2 });
	debug.setPosition(m_position - sf::Vector2f(m_hitRadius, m_hitRadius));
	debug.setFillColor(sf::Color::Red);
	window->draw(debug);*/
}

void Bullet::SetPosition(sf::Vector2f pos) {
	m_position = pos;
}

void Bullet::SetDirection(float degrees) {
	m_direction = Utils::Rot2Vec(degrees);
	m_sprite.SetDirection(degrees);
}

void Bullet::UpdateAABB() {
	m_AABB = sf::FloatRect(
		m_position.x - m_hitRadius,
		m_position.y - m_hitRadius,
		m_hitRadius * 2,
		m_hitRadius * 2);
}