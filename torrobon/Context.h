#pragma once
#ifndef CONTEXT
#define CONTEXT
#include "TextureHolder.h"
#include "BulletManager.h"
#include "EntityManager.h"
#include "EffectManager.h"
#include "Player.h"

struct Context {
	Context() :
		m_window(nullptr),
		m_textureHolder(nullptr),
		m_bulletManager(nullptr),
		m_entityManager(nullptr),
		m_effectManager(nullptr),
		m_player(nullptr)
	{}

	sf::RenderWindow* m_window;
	TextureHolder* m_textureHolder;
	BulletManager* m_bulletManager;
	EntityManager* m_entityManager;
	EffectManager* m_effectManager;
	Player* m_player;
};

#endif // !CONTEXT