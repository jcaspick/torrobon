#pragma once
#ifndef GS_GAME
#define GS_GAME
#include "GameState.h"
#include "Player.h"

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
	sf::Vector2f m_playerPos;
	float m_spawnTimer;
	float m_spawnInterval;
	float m_difficultyTimer;
	float m_difficultyInterval;
};

#endif // !GS_GAME;