#pragma once
#ifndef GEM
#define GEM
#include "Entity.h"
#include "SpriteSheet.h"

class Gem : public Entity {

public:
	Gem(Context* context);
	~Gem();
	void Update(float dt);
	void Draw();
	void OnPlayerCollision(sf::FloatRect intersection);

private:
	SpriteSheet m_sprite;
};

#endif // !GEM
