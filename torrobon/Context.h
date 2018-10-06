#pragma once
#ifndef CONTEXT
#define CONTEXT
#include "TextureHolder.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "Player.h"

struct Context {
	Context() :
		m_window(nullptr),
		m_textureHolder(nullptr),
		m_bulletManager(nullptr),
		m_enemyManager(nullptr),
		m_effectManager(nullptr),
		m_player(nullptr)
	{}

	sf::RenderWindow* m_window;
	TextureHolder* m_textureHolder;
	BulletManager* m_bulletManager;
	EnemyManager* m_enemyManager;
	EffectManager* m_effectManager;
	Player* m_player;
};

#endif // !CONTEXT