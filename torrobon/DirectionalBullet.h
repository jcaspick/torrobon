#pragma once
#ifndef DIRECTIONAL_BULLET
#define DIRECTIONAL_BULLET
#include "Bullet.h"
#include "DirectionalSprite.h"

struct Context;
class DirectionalBullet : public Bullet {

public:
	DirectionalBullet(Context* context, sf::Vector2f pos, 
		sf::Vector2f dir, float speed, const std::string& config);
	~DirectionalBullet();

	void Update(float dt);
	void Draw();

private:
	DirectionalSprite m_sprite;

};

#endif // !DIRECTIONAL_BULLET;