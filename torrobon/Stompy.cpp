#include "Stompy.h"
#include "Context.h"
#include "Utilities.h"

Stompy::Stompy(Context* context) :
	Entity(context),
	m_mode(Mode::Waiting),
	m_spriteSheet("config/stompy.cfg")
{}

Stompy::~Stompy() {}

void Stompy::Update(float dt) {
	m_elapsed += dt;

	switch (m_mode)
	{
	case Stompy::Mode::Waiting:
		if (m_elapsed > 0.5f) {
			m_elapsed -= 0.5f;
			ChooseDirection();
			m_mode = Mode::Chasing;
		}
		break;
	case Stompy::Mode::Chasing:
		if (m_elapsed > 1.5f) {
			m_elapsed -= 1.5f;
			m_mode = Mode::Waiting;
		}
		Move(m_direction * dt * 50.0f);
		break;
	}

	m_spriteSheet.SetPosition(m_position);
	m_spriteSheet.Update(dt);
}

void Stompy::Draw() {
	m_spriteSheet.Draw(m_context->m_window);
}

void Stompy::ChooseDirection() {
	sf::Vector2f playerPos = m_context->m_player->GetPosition();
	float rotation = Utils::Vec2Rot(playerPos - m_position);
	m_direction = Utils::Rot2Vec(rotation);
}