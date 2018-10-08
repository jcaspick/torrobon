#include "EntityManager.h"
#include <iostream>
#include "Context.h"

// entity classes
#include "Drone.h"
#include "Stompy.h"
#include "EnemyBullet.h"

EntityManager::EntityManager(Context* context) :
	m_context(context)
{
	// factory definitions
	m_entityFactory[EntityType::Drone] = [this]() -> Entity* {
		return new Drone(this->GetContext()); };
	m_entityFactory[EntityType::Stompy] = [this]() -> Entity* {
		return new Stompy(this->GetContext()); };
}

EntityManager::~EntityManager() {
	Purge();
}

void EntityManager::Update(float dt) {
	for (auto itr : m_entities) {
		itr->Update(dt);
	}
	CheckPlayerCollision();
	RemoveDead();
}

void EntityManager::Draw() {
	for (auto itr : m_entities) {
		itr->Draw();
	}
}

void EntityManager::Spawn(EntityType type, const sf::Vector2f& pos) {
	auto itr = m_entityFactory.find(type);
	if (itr == m_entityFactory.end()) {
		std::cout << "entity type " << std::to_string((int)type) << " has not been defined in factory" << std::endl;
		return;
	}

	Entity* entity = itr->second();
	entity->SetPosition(pos);
	m_entities.emplace_back(entity);
}

void EntityManager::SpawnBullet(sf::Vector2f pos, sf::Vector2f dir, float speed) {
	EnemyBullet* bullet = new EnemyBullet(m_context);
	bullet->SetPosition(pos);
	bullet->SetDirection(dir);
	bullet->SetSpeed(speed);

	m_entities.emplace_back(bullet);
}

void EntityManager::Purge() {
	for (auto &itr : m_entities) {
		delete itr;
	}
	m_entities.clear();
}

void EntityManager::RemoveDead() {
	for (int i = m_entities.size() - 1; i >= 0; --i) {
		if (m_entities[i]->GetHealth() <= 0) {
			m_entities[i]->OnDeath();
			m_context->m_effectManager->BigExplosion(m_entities[i]->GetPosition());
			delete m_entities[i];
			m_entities.erase(m_entities.begin() + i);
		}
	}
}

void EntityManager::CheckPlayerCollision() {
	if (!m_context->m_player->IsAlive()) return;
	sf::FloatRect playerAABB = m_context->m_player->GetAABB();
	for (auto itr : m_entities) {
		if (itr->GetRect().intersects(playerAABB)) {
			m_context->m_effectManager->BigExplosion(
				m_context->m_player->GetPosition());
			m_context->m_player->Kill();
		}
	}
}

// getters
Context* EntityManager::GetContext() { return m_context; }
std::vector<Entity*>* EntityManager::GetEntities() { return &m_entities; }

