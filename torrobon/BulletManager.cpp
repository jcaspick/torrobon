#include "BulletManager.h"
#include "Context.h"
#include "Utilities.h"
#include "DirectionalBullet.h"

BulletManager::BulletManager(Context* context) :
	m_context(context)
{
	m_bulletFactory[BulletType::PlayerBasic] = 
		[context](sf::Vector2f pos, sf::Vector2f rot, float speed) {
		return new DirectionalBullet(context, pos, rot, speed, "config/directionalBullet.cfg");
	};
}

BulletManager::~BulletManager() { Purge(); };

void BulletManager::Update(float dt) {
	sf::Vector2f worldSize = m_context->m_world->GetSize();
	float thickness = m_context->m_world->GetWallThickness();

	for (auto &itr : m_playerBullets) {
		itr->Update(dt);
		if (itr->GetPosition().x < thickness ||
			itr->GetPosition().x > worldSize.x - thickness ||
			itr->GetPosition().y < thickness ||
			itr->GetPosition().y > worldSize.y - thickness)
		{
			itr->SetAlive(false);
		}
	}

	CheckCollisions();
	RemoveDeadBullets();
}

void BulletManager::Draw() {
	for (auto &itr : m_playerBullets) {
		itr->Draw();
	}
	for (auto &itr : m_enemyBullets) {
		itr->Draw();
	}
}

void BulletManager::AimedBullet(
	bool player,
	BulletType type,
	sf::Vector2f pos,
	float rot,
	float speed,
	float inaccuracy)
{
	float rotOffset = inaccuracy == 0 ? 0 :
		static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / inaccuracy));
	sf::Vector2f dir = Utils::Rot2Vec(rot + rotOffset);
	Bullet* bullet = m_bulletFactory[type](pos, dir, speed);
	if (player) m_playerBullets.emplace_back(bullet);
	else m_enemyBullets.emplace_back(bullet);
}

void BulletManager::Purge() {
	for (auto &itr : m_playerBullets) {
		delete itr;
	}
	m_playerBullets.clear();
	for (auto &itr : m_enemyBullets) {
		delete itr;
	}
	m_enemyBullets.clear();
}

void BulletManager::CheckCollisions() {
	std::vector<Entity*> enemies = *m_context->m_entityManager->GetEntities();

	for (auto itr : m_playerBullets) {
		for (auto itr2 : enemies) {
			if ((itr2->GetCollisionMask() & CollisionMask::c_Bullets) == CollisionMask::c_Bullets &&
				itr->GetRect().intersects(itr2->GetRect())) {
				m_context->m_effectManager->
					CreateEffect(EffectType::SmallYellowExplosion1, itr->GetPosition());
				itr2->AddDamage(1);
				itr->SetAlive(false);
			}
		}
	}
}

void BulletManager::RemoveDeadBullets() {
	for (int i = m_playerBullets.size() - 1; i >= 0; --i) {
		if (!m_playerBullets[i]->IsAlive()) {
			delete m_playerBullets[i];
			m_playerBullets.erase(m_playerBullets.begin() + i);
		}
	}
	for (int i = m_enemyBullets.size() - 1; i >= 0; --i) {
		if (!m_enemyBullets[i]->IsAlive()) {
			delete m_enemyBullets[i];
			m_enemyBullets.erase(m_enemyBullets.begin() + i);
		}
	}
}