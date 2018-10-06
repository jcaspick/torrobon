#include "Explosion.h"
#include "EffectManager.h"

Explosion::Explosion(EffectManager* effectMgr, const std::string& config) :
	m_effectMgr(effectMgr),
	m_sprite(config)
{
	m_sprite.SetLooped(false);
}

Explosion::~Explosion() {}

void Explosion::Update(float dt) {
	m_sprite.Update(dt);
}

void Explosion::Draw(sf::RenderWindow* window) {
	m_sprite.Draw(window);
}

void Explosion::SetAnimation(const std::string& name) {
	m_sprite.SetAnimation(name);
}