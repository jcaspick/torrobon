#include "BulletManager.h"
#include "Context.h"
#include "Utilities.h"
#include "DirectionalBullet.h"
#include "StaticBullet.h"

BulletManager::BulletManager(Context* context) :
	m_context(context)
{
	m_bulletFactory[BulletType::PlayerBasic] = 
		[context](sf::Vector2f pos, sf::Vector2f dir, float speed) {
		return new DirectionalBullet(context, pos, dir, speed, "config/directionalBullet.cfg");
	};
	m_bulletFactory[BulletType::PlayerSuper] =
		[context](sf::Vector2f pos, sf::Vector2f dir, float speed) {
		return new DirectionalBullet(context, pos, dir, speed, "config/directionalBlue.cfg");
	};
	m_bulletFactory[BulletType::StaticRed] =
		[context](sf::Vector2f pos, sf::Vector2f dir, float speed) {
		return new StaticBullet(context, pos, dir, speed, "redBullet");
	};
}

BulletManager::~BulletManager() { Purge(); };

void BulletManager::Update(float dt) {
	sf::Vector2f worldSize = m_context->m_world->GetSize();
	float thickness = m_context->m_world->GetWallThickness();

	for (auto &itr : m_playerBullets) {
		itr->Update(dt);
		if (!m_context->m_world->IsInBounds(itr->GetPosition())) {
			itr->SetAlive(false);
		}
	}

	for (auto &itr : m_enemyBullets) {
		itr->Update(dt);
		if (!m_context->m_world->IsInBounds(itr->GetPosition())) {
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

void BulletManager::BulletCircle(
	bool player,
	BulletType type,
	sf::Vector2f pos,
	float speed,
	int num,
	float rotOffset,
	float fOffset)
{
	float angleIncrement = 360 / static_cast<float>(num);
	for (int i = 0; i < num; i++) {
		sf::Vector2f dir = Utils::Rot2Vec(i * angleIncrement + rotOffset);
		Bullet* bullet = m_bulletFactory[type](pos + dir * fOffset, dir, speed);
		if (player) m_playerBullets.emplace_back(bullet);
		else m_enemyBullets.emplace_back(bullet);
	}
}

void BulletManager::BulletArc(
	bool player,
	BulletType type,
	sf::Vector2f pos,
	float rot,
	float speed,
	int num,
	float angle,
	float fOffset)
{
	float angleIncrement = angle / static_cast<float>(num);
	for (int i = 0; i < num; i++) {
		sf::Vector2f dir = Utils::Rot2Vec(rot + angleIncrement * i - (angle * 0.5f));
		Bullet* bullet = m_bulletFactory[type](pos + dir * fOffset, dir, speed);
		if (player) m_playerBullets.emplace_back(bullet);
		else m_enemyBullets.emplace_back(bullet);
	}
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
				itr2->AddDamage(1);
				itr->SetAlive(false);
			}
		}
	}

	sf::FloatRect playerHitbox = m_context->m_player->GetHitbox();
	for (auto itr : m_enemyBullets) {
		if (itr->GetRect().intersects(playerHitbox)) {
			m_context->m_effectManager->CreateEffect(
				EffectType::BigExplosion, m_context->m_player->GetPosition());
			m_context->m_player->Kill();
		}
	}
}

void BulletManager::RemoveDeadBullets() {
	for (int i = m_playerBullets.size() - 1; i >= 0; --i) {
		if (!m_playerBullets[i]->IsAlive()) {
			m_playerBullets[i]->OnDeath();
			delete m_playerBullets[i];
			m_playerBullets.erase(m_playerBullets.begin() + i);
		}
	}
	for (int i = m_enemyBullets.size() - 1; i >= 0; --i) {
		if (!m_enemyBullets[i]->IsAlive()) {
			m_enemyBullets[i]->OnDeath();
			delete m_enemyBullets[i];
			m_enemyBullets.erase(m_enemyBullets.begin() + i);
		}
	}
}