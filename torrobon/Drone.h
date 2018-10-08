#pragma once
#ifndef DRONE
#define DRONE
#include "Entity.h"
#include "SpriteSheet.h"

class Drone : public Entity {

public:
	Drone(Context* context);
	~Drone();

	void Update(float dt);
	void Draw();
	void OnDeath();

private:
	void ChooseDirection();

	SpriteSheet m_spriteSheet;
	float m_speed;
	sf::Vector2f m_direction;
	float m_elapsed;
	float m_directionInterval;
};

#endif // !DRONE
