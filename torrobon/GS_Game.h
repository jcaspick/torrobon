#pragma once
#ifndef GS_GAME
#define GS_GAME
#include "GameState.h"
#include "Player.h"
#include "World.h"
#include "BulletManager.h"
#include "EntityManager.h"
#include "EffectManager.h"
#include "EntityDebugView.h"

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
	World m_world;
	BulletManager m_bulletManager;
	EntityManager m_entityManager;
	EffectManager m_effectManager;
	float m_spawnTimer;
	float m_spawnInterval;
	float m_difficultyTimer;
	float m_difficultyInterval;
	float m_gameOverTimer;
	sf::Text m_scoreText;
	sf::Font m_font;
	sf::RectangleShape m_bg;

	EntityDebugView m_debugView;
};

#endif // !GS_GAME;