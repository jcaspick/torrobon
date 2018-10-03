#pragma once
#ifndef BULLETMANAGER
#define BULLETMANAGER
#include "Bullet.h"

struct Context;
class BulletManager {

public:
	BulletManager(Context* context);
	~BulletManager();

	void Update(float dt);
	void Draw();
	Bullet* CreateBullet(sf::Vector2f pos, float rot);
	Context* GetContext();

private:
	void Purge();
	void CheckCollisions();
	void RemoveDeadBullets();

	Context* m_context;
	std::vector<Bullet*> m_bullets;
};

#endif // BULLETMANAGER