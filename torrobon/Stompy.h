#pragma once
#ifndef STOMPY
#define STOMPY
#include "Entity.h"
#include "SpriteSheet.h"

class Stompy : public Entity {

	enum class Mode {
		Waiting,
		Chasing,
		Shooting
	};

public:
	Stompy(Context* context);
	~Stompy();

	void Update(float dt);
	void Draw();
	void OnDeath();
	void OnPlayerCollision(sf::FloatRect intersection);

private:
	void ChooseDirection();

	Mode m_mode;
	SpriteSheet m_spriteSheet;
	sf::Vector2f m_direction;
	float m_elapsed;
	float m_shotTimer;
	float m_shotInterval;
	int m_pauses;
};

#endif // !STOMPY