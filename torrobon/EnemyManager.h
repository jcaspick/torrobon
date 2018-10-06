#pragma once
#ifndef ENEMY_MANAGER
#define ENEMY_MANAGER
#include "Enemy.h"

struct Context;
class EnemyManager {

public:
	EnemyManager(Context* context);
	~EnemyManager();

	void Update(float dt);
	void Draw();
	void SpawnEnemy(const sf::Vector2f& pos);
	Context* GetContext();
	std::vector<Enemy*>* GetEnemyList();
		
private:
	void Purge();
	void RemoveDeadEnemies();
	void CheckPlayerCollision();

	Context* m_context;
	std::vector<Enemy*> m_enemies;
};

#endif // !ENEMY_MANAGER