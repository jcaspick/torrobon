#pragma once
#ifndef GAME
#define GAME
#include "SpriteSheet.h"
#include "TextureHolder.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "StateManager.h"

class Game {

public:
	Game();
	~Game();

	void Update();
	void Draw();

	sf::RenderWindow* GetWindow();

private:
	sf::Clock m_clock;
	float m_dt;
	Context m_context;
	StateManager m_stateMgr;
	sf::RenderWindow m_window;
	TextureHolder m_textures;
	BulletManager m_bulletManager;
	EnemyManager m_enemyManager;
	EffectManager m_effectManager;
	sf::Vector2f m_playerPos;
};

#endif // !GAME