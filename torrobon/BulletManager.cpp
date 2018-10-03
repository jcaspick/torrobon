#include "BulletManager.h"
#include "Context.h"
#include <cassert>
#include <iostream>

BulletManager::BulletManager(Context* context) :
	m_context(context)
{}

BulletManager::~BulletManager() { Purge(); };

void BulletManager::Update(float dt) {
	for (auto &itr : m_bullets) {
		itr->Update(dt);
		if (itr->m_position.x < 0 ||
			itr->m_position.x > m_context->m_window->getSize().x ||
			itr->m_position.y < 0 ||
			itr->m_position.y > m_context->m_window->getSize().y)
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
	std::vector<Enemy*> enemies = *m_context->m_enemyManager->GetEnemyList();

	for (auto itr : m_bullets) {
		for (auto itr2 : enemies) {
			if (itr->m_AABB.intersects(itr2->GetAABB())) {
				m_context->m_effectManager->
					CreateEffect(EffectType::SmallYellowExplosion1, itr->m_position);
				itr2->Damage(1);
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