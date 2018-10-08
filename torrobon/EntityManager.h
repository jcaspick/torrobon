#pragma once
#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER
#include "Entity.h"
#include <unordered_map>
#include <functional>

enum class EntityType {
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

	Context* GetContext();
	std::vector<Entity*>* GetEntities();

private:
	void Purge();
	void RemoveDead();
	void CheckPlayerCollision();

	Context* m_context;
	std::vector<Entity*> m_entities;
	EntityFactory m_entityFactory;
};

#endif // !ENTITY_MANAGER
