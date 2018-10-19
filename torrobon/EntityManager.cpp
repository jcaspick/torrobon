#include "EntityManager.h"
#include <iostream>
#include "Context.h"

// entity classes
#include "Gem.h"
#include "Drone.h"
#include "Stompy.h"

EntityManager::EntityManager(Context* context) :
	m_context(context)
{
	// factory definitions
	m_entityFactory[EntityType::Gem] = [this]() -> Entity* {
		return new Gem(this->GetContext()); };
	m_entityFactory[EntityType::Drone] = [this]() -> Entity* {
		return new Drone(this->GetContext()); };
	m_entityFactory[EntityType::Stompy] = [this]() -> Entity* {
		return new Stompy(this->GetContext()); };
}

EntityManager::~EntityManager() {
	Purge();
}

void EntityManager::Update(float dt) {
	for (int i = 0; i < m_entities.size(); ++i) {
		m_entities[i]->Update(dt);
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
			delete m_entities[i];
			m_entities.erase(m_entities.begin() + i);
		}
	}
}

void EntityManager::CheckPlayerCollision() {
	if (!m_context->m_player->IsAlive()) return;
	sf::FloatRect playerHitbox = m_context->m_player->GetHitbox();
	sf::FloatRect playerRect = m_context->m_player->GetRect();
	sf::FloatRect intersection;

	for (auto itr : m_entities) {
		if (itr->GetRect().intersects(playerRect, intersection)) {
			itr->OnPlayerCollision(intersection);
		}
	}
}

// getters
Context* EntityManager::GetContext() { return m_context; }
std::vector<Entity*>* EntityManager::GetEntities() { return &m_entities; }