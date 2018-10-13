#include "BulletManager.h"
#include "Context.h"
#include <cassert>
#include <iostream>

BulletManager::BulletManager(Context* context) :
	m_context(context)
{}

BulletManager::~BulletManager() { Purge(); };

void BulletManager::Update(float dt) {
	sf::Vector2f worldSize = m_context->m_world->GetSize();
	float thickness = m_context->m_world->GetWallThickness();

	for (auto &itr : m_bullets) {
		itr->Update(dt);
		if (itr->m_position.x < thickness ||
			itr->m_position.x > worldSize.x - thickness ||
			itr->m_position.y < thickness ||
			itr->m_position.y > worldSize.y - thickness)
		{
			m_context->m_effectManager->
				CreateEffect(EffectType::SmallYellowExplosion1, itr->m_position);
			itr->m_deleteFlag = true;
		}
	}
	CheckCollisions();
	RemoveDeadBullets();
}

void BulletManager::Draw() {
	for (auto &itr : m_bullets) {
		itr->Draw(m_context->m_window);
	}
}

Bullet* BulletManager::CreateBullet(sf::Vector2f pos, float rot) {
	Bullet* bullet = new Bullet(this);
	bullet->SetPosition(pos);
	bullet->SetDirection(rot);
	m_bullets.emplace_back(bullet);
	return bullet;
}

Context* BulletManager::GetContext() {
	return m_context;
}

void BulletManager::Purge() {
	for (auto &itr : m_bullets) {
		delete itr;
	}
	m_bullets.clear();
}

void BulletManager::CheckCollisions() {
	std::vector<Entity*> enemies = *m_context->m_entityManager->GetEntities();

	for (auto itr : m_bullets) {
		for (auto itr2 : enemies) {
			if ((itr2->GetCollisionMask() & CollisionMask::c_Bullets) == CollisionMask::c_Bullets && 
				itr->m_AABB.intersects(itr2->GetRect())) {
				m_context->m_effectManager->
					CreateEffect(EffectType::SmallYellowExplosion1, itr->m_position);
				itr2->AddDamage(1);
				itr->m_deleteFlag = true;
			}
		}
	}
}

void BulletManager::RemoveDeadBullets() {
	for (int i = m_bullets.size() - 1; i >= 0; --i) {
		if (m_bullets[i]->m_deleteFlag) {
			delete m_bullets[i];
			m_bullets.erase(m_bullets.begin() + i);
		}
	}
}