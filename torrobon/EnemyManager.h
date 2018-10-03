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
	Context* GetContext();
	std::vector<Enemy*>* GetEnemyList();
		
private:
	void SpawnEnemy();
	void Purge();
	void RemoveDeadEnemies();

	Context* m_context;
	float m_spawnInterval;
	float m_elapsed;
	std::vector<Enemy*> m_enemies;
};

#endif // !ENEMY_MANAGER