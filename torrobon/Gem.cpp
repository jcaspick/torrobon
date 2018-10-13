#include "Gem.h"
#include "Context.h"

Gem::Gem(Context* context) :
	Entity(context),
	m_sprite("config/gem.cfg")
{
	m_rectSize = { 16, 16 };
	m_collisionMask = c_Player;
}

Gem::~Gem() {}

void Gem::Update(float dt) {
	m_sprite.SetPosition(m_position);
	m_sprite.Update(dt);
	UpdateRect();
}

void Gem::Draw() {
	m_sprite.Draw(m_context->m_window);
}

void Gem::OnPlayerCollision(sf::FloatRect intersection) {
	m_context->m_player->AddScore(1);
	m_health = 0;
}