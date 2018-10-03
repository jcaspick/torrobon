#include "EnemyManager.h"
#include "Context.h"

EnemyManager::EnemyManager(Context* context) :
	m_context(context),
	m_spawnInterval(0.8f),
	m_elapsed(20)
{}

EnemyManager::~EnemyManager() { Purge(); }

void EnemyManager::Update(float dt) {
	m_elapsed += dt;
	if (m_elapsed > m_spawnInterval) {
		m_elapsed -= m_spawnInterval;
		SpawnEnemy();
	}
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

void EnemyManager::SpawnEnemy() {
	Enemy* enemy = new Enemy(m_context);
	float spawnX = rand() % m_context->m_window->getSize().x;
	float spawnY = rand() % m_context->m_window->getSize().y;
	if (rand() % 2) {
		if (rand() % 2) { spawnX = 0; }
		else { spawnX = m_context->m_window->getSize().x; }
	}
	else {
		if (rand() % 2) { spawnY = 0; }
		else { spawnY = m_context->m_window->getSize().y; }
	}
	enemy->SetPosition({ spawnX, spawnY });
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