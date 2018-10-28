#pragma once
#ifndef CONTEXT
#define CONTEXT
#include "World.h"
#include "TextureHolder.h"
#include "BulletManager.h"
#include "EntityManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "FlowField.h"
#include "Player.h"

struct Context {
	Context() :
		m_window(nullptr),
		m_world(nullptr),
		m_textureHolder(nullptr),
		m_bulletManager(nullptr),
		m_entityManager(nullptr),
		m_effectManager(nullptr),
		m_player(nullptr),
		m_flowField(nullptr),
		m_soundManager(nullptr)
	{}

	sf::RenderWindow* m_window;
	World* m_world;
	TextureHolder* m_textureHolder;
	BulletManager* m_bulletManager;
	EntityManager* m_entityManager;
	EffectManager* m_effectManager;
	Player* m_player;
	FlowField* m_flowField;
	SoundManager* m_soundManager;
};

#endif // !CONTEXT