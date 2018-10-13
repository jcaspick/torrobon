#pragma once
#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER
#include "Entity.h"
#include "EnemyBullet.h"
#include <unordered_map>
#include <functional>

enum class EntityType {
	Gem,
	Drone,
	Stompy
};

using EntityFactory = std::unordered_map<EntityType, std::function<Entity*(void)>>;

struct Context;
class EntityManager {

public:
	EntityManager(Context* context);
	~EntityManager();

	void Update(float dt);
	void Draw();
	void Spawn(EntityType type, const sf::Vector2f& pos);
	void SpawnBullet(sf::Vector2f pos, sf::Vector2f dir, float speed);

	Context* GetContext();
	std::vector<Entity*>* GetEntities();

private:
	void Purge();
	void RemoveDead();
	void CheckPlayerCollision();

	Context* m_context;
	std::vector<Entity*> m_entities;
	std::vector<EnemyBullet*> m_bullets;
	EntityFactory m_entityFactory;
};

#endif // !ENTITY_MANAGER
