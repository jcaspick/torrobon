#include "EffectManager.h"
#include "Context.h"

EffectManager::EffectManager(Context* context) :
	m_context(context)
{
	// factory definitions
	m_effectFactory[EffectType::BigExplosion] = [this]() {
		Explosion* explosion = new Explosion(this, "config/bigExplosion.cfg");
		explosion->SetAnimation("explode");
		return explosion; };
	m_effectFactory[EffectType::SmallBlueExplosion1] = [this]() {
		Explosion* explosion = new Explosion(this, "config/smallExplosions.cfg");
		explosion->SetAnimation("blue1");
		return explosion; };
	m_effectFactory[EffectType::SmallBlueExplosion2] = [this]() {
		Explosion* explosion = new Explosion(this, "config/smallExplosions.cfg");
		explosion->SetAnimation("blue2");
		return explosion; };
	m_effectFactory[EffectType::SmallRedExplosion1] = [this]() {
		Explosion* explosion = new Explosion(this, "config/smallExplosions.cfg");
		explosion->SetAnimation("red1");
		return explosion; };
	m_effectFactory[EffectType::SmallRedExplosion2] = [this]() {
		Explosion* explosion = new Explosion(this, "config/smallExplosions.cfg");
		explosion->SetAnimation("red2");
		return explosion; };
	m_effectFactory[EffectType::SmallYellowExplosion1] = [this]() {
		Explosion* explosion = new Explosion(this, "config/smallExplosions.cfg");
		explosion->SetAnimation("orange1");
		return explosion; };
	m_effectFactory[EffectType::SmallYellowExplosion2] = [this]() {
		Explosion* explosion = new Explosion(this, "config/smallExplosions.cfg");
		explosion->SetAnimation("orange2");
		return explosion; };
}

EffectManager::~EffectManager() { Purge(); }

void EffectManager::Update(float dt) {
	for (auto &itr : m_explosions) {
		itr->Update(dt);
	}
	RemoveFinishedEffects();
}

void EffectManager::Draw() {
	for (auto &itr : m_explosions) {
		itr->Draw(m_context->m_window);
	}
}

void EffectManager::CreateEffect(EffectType type, sf::Vector2f pos) {
	Explosion* explosion = m_effectFactory[type]();
	explosion->SetPosition(pos);
	m_explosions.emplace_back(explosion);
}

void EffectManager::Purge() {
	for (auto &itr : m_explosions) {
		delete itr;
	}
	m_explosions.clear();
}

void EffectManager::RemoveFinishedEffects() {
	for (int i = m_explosions.size() - 1; i >= 0; --i) {
		if (m_explosions[i]->m_sprite.IsPaused()) {
			delete m_explosions[i];
			m_explosions.erase(m_explosions.begin() + i);
		}
	}
}