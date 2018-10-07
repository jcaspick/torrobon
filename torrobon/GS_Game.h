#pragma once
#ifndef GS_GAME
#define GS_GAME
#include "GameState.h"
#include "Player.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "EffectManager.h"

class GS_Game : public GameState {
	
public:
	GS_Game(StateManager* stateMgr);
	~GS_Game();

	void OnCreate();
	void OnDestroy();
	void OnEnable();
	void OnDisable();
	void Update(float dt);
	void Draw();

private:
	Player* m_player;
	BulletManager m_bulletManager;
	EnemyManager m_enemyManager;
	EffectManager m_effectManager;
	float m_spawnTimer;
	float m_spawnInterval;
	float m_difficultyTimer;
	float m_difficultyInterval;
	float m_gameOverTimer;
	sf::Text m_scoreText;
	sf::Font m_font;
	SpriteSheet m_test;
	sf::RectangleShape m_bg;
};

#endif // !GS_GAME;