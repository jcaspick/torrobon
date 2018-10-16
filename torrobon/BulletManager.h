#pragma once
#ifndef BULLETMANAGER
#define BULLETMANAGER
#include "Bullet.h"
#include <unordered_map>
#include <functional>

enum class BulletType {
	PlayerBasic,
	PlayerSuper,
	StaticRed
};

using BulletFactory = std::unordered_map<
	BulletType, std::function<Bullet*(sf::Vector2f pos, sf::Vector2f dir, float speed)>>;

struct Context;
class BulletManager {

public:
	BulletManager(Context* context);
	~BulletManager();

	void Update(float dt);
	void Draw();
	void AimedBullet(
		bool player, 
		BulletType type, 
		sf::Vector2f pos, 
		float rot, 
		float speed,
		float inaccuracy = 0);
	//void BulletCircle(bool player, BulletType type, sf::Vector2f pos, int num, float rotOffset, float fOffset = 0);
	//void BulletArc(bool player, BulletType type, sf::Vector2f pos, float rot, int num, float angle, float fOffset = 0);

private:
	void Purge();
	void CheckCollisions();
	void RemoveDeadBullets();

	Context* m_context;
	std::vector<Bullet*> m_playerBullets;
	std::vector<Bullet*> m_enemyBullets;
	BulletFactory m_bulletFactory;
};

#endif // BULLETMANAGER