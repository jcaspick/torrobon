#pragma once
#ifndef STOMPY
#define STOMPY
#include "Entity.h"
#include "SpriteSheet.h"

class Stompy : public Entity {

	enum class Mode {
		Waiting,
		Chasing
	};

public:
	Stompy(Context* context);
	~Stompy();

	void Update(float dt);
	void Draw();
	void OnDeath();

private:
	void ChooseDirection();

	Mode m_mode;
	SpriteSheet m_spriteSheet;
	sf::Vector2f m_direction;
	float m_elapsed;
};

#endif // !STOMPY