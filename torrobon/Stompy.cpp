#include "Stompy.h"
#include "Context.h"
#include "Utilities.h"
#include "EnemyBullet.h"

Stompy::Stompy(Context* context) :
	Entity(context),
	m_mode(Mode::Waiting),
	m_spriteSheet("config/stompy.cfg"),
	m_shotInterval(0.4f)
{
	m_health = 50;
	m_rectSize = { 90, 96 };
}

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
			m_mode = Mode::Shooting;
		}
		Move(m_direction * dt * 50.0f);
		break;

	case Stompy::Mode::Shooting:
		m_shotTimer += dt;
		if (m_shotTimer > m_shotInterval) {
			m_shotTimer -= m_shotInterval;
			m_context->m_entityManager->SpawnBullet(
				m_position, 
				Utils::Normalize(m_context->m_player->GetPosition() - m_position), 
				200);
		}
		if (m_elapsed > 2.0f) {
			m_elapsed -= 2.0f;
			m_shotTimer = 0.0f;
			m_mode = Mode::Chasing;
		}
		break;
	}

	m_spriteSheet.SetPosition(m_position);
	m_spriteSheet.Update(dt);
	UpdateRect();
}

void Stompy::Draw() {
	m_spriteSheet.Draw(m_context->m_window);
}

void Stompy::OnDeath() {
	m_context->m_player->AddScore(10);
}

void Stompy::ChooseDirection() {
	sf::Vector2f playerPos = m_context->m_player->GetPosition();
	float rotation = Utils::Vec2Rot(playerPos - m_position);
	m_direction = Utils::Rot2Vec(rotation);
}