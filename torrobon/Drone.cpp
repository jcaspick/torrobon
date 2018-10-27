#include "Drone.h"
#include "Context.h"

Drone::Drone(Context* context) :
	Entity(context),
	m_spriteSheet("config/bot1.cfg"),
	m_speed(75.0f),
	m_directionInterval(0.25f)
{
	m_rectSize = { 32, 40 };
	m_rectOffset = { 0, 12 };
	m_spriteSheet.SetScale({ 2, 2 });
	m_health = 1;
	m_collisionMask = c_Player | c_Bullets;
}

Drone::~Drone() {}

void Drone::Update(float dt) {
	m_elapsed += dt;
	if (m_elapsed >= m_directionInterval) {
		m_elapsed -= m_directionInterval;
		ChooseDirection();
	}

	Move(m_direction * m_speed * dt);
	m_spriteSheet.SetPosition(m_position);
	m_spriteSheet.Update(dt);
	UpdateRect();
}

void Drone::Draw() {
	m_spriteSheet.Draw(m_context->m_window);
}

void Drone::OnDeath() {
	m_context->m_entityManager->Spawn(EntityType::Gem, m_position);
	m_context->m_effectManager->CreateEffect(
		EffectType::BigExplosion, m_position);
}

void Drone::OnPlayerCollision(sf::FloatRect intersection) {
	m_context->m_effectManager->CreateEffect(
		EffectType::BigExplosion, m_context->m_player->GetPosition());
	m_context->m_player->Kill();
}

void Drone::ChooseDirection() {
	sf::Vector2f goal = m_context->m_flowField->QueryFlowField(m_position);

	if (abs(goal.x) > abs(goal.y))
	{
		if (goal.x > 0) {
			m_direction = { 1, 0 };
			m_spriteSheet.SetAnimation("right");
		}
		else {
			m_direction = { -1, 0 };
			m_spriteSheet.SetAnimation("left");
		}
	}
	else {
		if (goal.y > 0) {
			m_direction = { 0, 1 };
			m_spriteSheet.SetAnimation("down");
		}
		else {
			m_direction = { 0, -1 };
			m_spriteSheet.SetAnimation("up");
		}
	}
}