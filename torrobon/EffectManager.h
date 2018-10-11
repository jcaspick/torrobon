#pragma once
#ifndef EFFECT_MANAGER
#define EFFECT_MANAGER
#include "Explosion.h"
#include <unordered_map>
#include <functional>

enum class EffectType {
	BigExplosion,
	SmallYellowExplosion1,
	SmallYellowExplosion2,
	SmallBlueExplosion1,
	SmallBlueExplosion2,
	SmallRedExplosion1,
	SmallRedExplosion2
};

using EffectFactory = std::unordered_map<EffectType, std::function<Explosion*(void)>>;

struct Context;
class EffectManager {

public:
	EffectManager(Context* context);
	~EffectManager();

	void Update(float dt);
	void Draw();
	void CreateEffect(EffectType type, sf::Vector2f pos);

private:
	void Purge();
	void RemoveFinishedEffects();

	Context* m_context;
	std::vector<Explosion*> m_explosions;
	EffectFactory m_effectFactory;
};

#endif // !EFFECT_MANAGER;
