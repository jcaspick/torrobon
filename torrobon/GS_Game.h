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
	float m_elapsed;
	float m_spawnInterval;
};

#endif // !GS_GAME;