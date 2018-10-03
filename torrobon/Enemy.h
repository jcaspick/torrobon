#pragma once
#ifndef ENEMY
#define ENEMY
#include "SpriteSheet.h"

struct Context;
class Enemy {

public:
	Enemy(Context* context);
	~Enemy();

	void Update(float dt);
	void Draw();
	void SetPosition(const sf::Vector2f& pos);
	void Damage(int damage);
	int GetHealth();
	sf::Vector2f GetPosition();
	sf::FloatRect GetAABB();

private:
	void ChooseDirection();
	void UpdateAABB();

	SpriteSheet m_spriteSheet;
	sf::Vector2f m_position;
	Context* m_context;
	float m_speed;
	sf::Vector2f m_direction;
	float m_directionInterval;
	float m_elapsed;
	sf::FloatRect m_AABB;
	int m_health;
};

#endif // !ENEMY