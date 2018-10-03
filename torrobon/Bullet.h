#pragma once
#ifndef BULLET
#define BULLET
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics.hpp>
#include "DirectionalSprite.h"
struct Context;

class BulletManager;
class Bullet {
	friend class BulletManager;

public:
	Bullet(BulletManager* bulletMgr);
	~Bullet();

	void Update(float dt);
	void Draw(sf::RenderWindow* window);
	void SetDirection(float degrees);
	void SetPosition(sf::Vector2f pos);

private:
	void UpdateAABB();

	BulletManager* m_bulletMgr;
	sf::Vector2f m_position;
	float m_speed;
	float m_hitRadius;
	sf::Vector2f m_direction;
	DirectionalSprite m_sprite;
	sf::FloatRect m_AABB;
	bool m_deleteFlag;
};

#endif // !BULLET