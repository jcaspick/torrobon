#include "Stompy.h"
#include "Context.h"
#include "Utilities.h"
#include "EnemyBullet.h"

Stompy::Stompy(Context* context) :
	Entity(context),
	m_mode(Mode::Waiting),
	m_spriteSheet("config/stompy.cfg"),
	m_shotInterval(0.2f)
{
	m_health = 75;
	m_rectSize = { 90, 96 };
	m_collisionMask = c_Player | c_Bullets;
}

Stompy::~Stompy() {}

void Stompy::Update(float dt) {
	m_elapsed += dt;

	switch (m_mode)
	{
	case Stompy::Mode::Waiting:
		if (m_elapsed > 0.4f) {
			m_elapsed -= 0.4f;
			ChooseDirection();
			m_pauses++;
			m_mode = Mode::Chasing;
		}
		break;

	case Stompy::Mode::Chasing:
		if (m_elapsed > 1.5f) {
			m_elapsed -= 1.5f;
			if (m_pauses >= 2) {
				m_pauses = 0;
				m_mode = Mode::Shooting;
			}
			else {
				m_mode = Mode::Waiting;
			}
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
				300);
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
	m_context->m_effectManager->CreateEffect(
		EffectType::BigExplosion, m_position);
}

void Stompy::ChooseDirection() {
	sf::Vector2f playerPos = m_context->m_player->GetPosition();
	float rotation = Utils::Vec2Rot(playerPos - m_position);
	m_direction = Utils::Rot2Vec(rotation);
}