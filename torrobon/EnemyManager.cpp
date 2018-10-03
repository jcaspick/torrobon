#include "EnemyManager.h"
#include "Context.h"

EnemyManager::EnemyManager(Context* context) :
	m_context(context)
{}

EnemyManager::~EnemyManager() { Purge(); }

void EnemyManager::Update(float dt) {
	for (auto &itr : m_enemies) {
		itr->Update(dt);
	}
	RemoveDeadEnemies();
}

void EnemyManager::Draw() {
	for (auto &itr : m_enemies) {
		itr->Draw();
	}
}

Context* EnemyManager::GetContext() { return m_context; }

std::vector<Enemy*>* EnemyManager::GetEnemyList() { return &m_enemies; }

void EnemyManager::SpawnEnemy(const sf::Vector2f& pos) {
	Enemy* enemy = new Enemy(m_context);
	enemy->SetPosition(pos);
	m_enemies.emplace_back(enemy);
}

void EnemyManager::Purge() {
	for (auto &itr : m_enemies) {
		delete itr;
	}
	m_enemies.clear();
}

void EnemyManager::RemoveDeadEnemies() {
	for (int i = m_enemies.size() - 1; i >= 0; --i) {
		if (m_enemies[i]->GetHealth() <= 0) {
			m_context->m_effectManager->BigExplosion(m_enemies[i]->GetPosition());
			delete m_enemies[i];
			m_enemies.erase(m_enemies.begin() + i);
		}
	}
}