#include "Gem.h"
#include "Context.h"
#include "Utilities.h"

Gem::Gem(Context* context) :
	Entity(context),
	m_sprite("config/gem.cfg"),
	collected(false),
	m_speed(500)
{
	m_rectSize = { 16, 16 };
	m_collisionMask = c_Player;
}

Gem::~Gem() {}

void Gem::Update(float dt) {
	sf::Vector2f offset = m_context->m_player->GetPosition() - m_position;
	if (!collected) {
		float collectionRadius = m_context->m_player->GetCollectionRadius();
		if (offset.x * offset.x + offset.y * offset.y <= collectionRadius * collectionRadius) {
			collected = true;
		}
	}
	else {
		Move(Utils::Normalize(offset) * m_speed * dt);
		if (m_speed < 2000) m_speed += dt * 2000;
	}

	m_sprite.SetPosition(m_position);
	m_sprite.Update(dt);
	UpdateRect();
}

void Gem::Draw() {
	m_sprite.Draw(m_context->m_window);
}

void Gem::OnPlayerCollision(sf::FloatRect intersection) {
	m_context->m_player->AddEnergy(1);
	m_health = 0;
}