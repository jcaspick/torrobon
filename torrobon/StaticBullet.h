#pragma once
#ifndef STATIC_BULLET
#define STATIC_BULLET
#include "Bullet.h"

class StaticBullet : public Bullet {

public:
	StaticBullet(Context* context, sf::Vector2f pos, sf::Vector2f dir, float speed, std::string& texture);
	~StaticBullet();

	void Update(float dt);
	void Draw();

private:
	sf::Sprite m_sprite;

};

#endif // !STATIC_BULLET