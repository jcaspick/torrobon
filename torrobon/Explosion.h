#pragma once
#ifndef EXPLOSION
#define EXPLOSION
#include "SpriteSheet.h"

class EffectManager;
class Explosion {
	friend class EffectManager;

public:
	Explosion(EffectManager* effectMgr, const std::string& config);
	~Explosion();

	void Update(float dt);
	void Draw(sf::RenderWindow* window);
	void SetAnimation(const std::string& name);
	void SetPosition(const sf::Vector2f& pos);

private:
	EffectManager* m_effectMgr;
	SpriteSheet m_sprite;
};

#endif // !EXPLOSION
