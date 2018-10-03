#include "EffectManager.h"
#include "Context.h"

EffectManager::EffectManager(Context* context) :
	m_context(context)
{}

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
	/*switch (type)
	{
	case EffectType::BigExplosion:
		break;
	case EffectType::SmallYellowExplosion1:
		Explosion* explosion = new Explosion(this, "config/bigExposion.cfg");
		explosion->m_sprite.SetPosition(pos);
		explosion->SetAnimation("orange1");
		m_explosions.emplace_back(explosion);
		break;
	case EffectType::SmallYellowExplosion2:
		break;
	case EffectType::SmallBlueExplosion1:
		break;
	case EffectType::SmallBlueExplosion2:
		break;
	case EffectType::SmallRedExplosion1:
		break;
	case EffectType::SmallRedExplosion2:
		break;
	default:
		break;
	}*/

	Explosion* explosion = new Explosion(this, "config/smallExplosions.cfg");
	explosion->m_sprite.SetPosition(pos);
	explosion->SetAnimation("orange1");
	m_explosions.emplace_back(explosion);
}

void EffectManager::BigExplosion(sf::Vector2f pos) {
	Explosion* explosion = new Explosion(this, "config/bigExplosion.cfg");
	explosion->m_sprite.SetPosition(pos);
	explosion->SetAnimation("explode");
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