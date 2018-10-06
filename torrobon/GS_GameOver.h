#pragma once
#ifndef GS_GAME_OVER
#define GS_GAME_OVER
#include "GameState.h"
#include <SFML\Graphics.hpp>

class GS_GameOver : public GameState {

public:
	GS_GameOver(StateManager* stateMgr);
	~GS_GameOver();

	void OnCreate();
	void OnDestroy();
	void OnEnable();
	void OnDisable();
	void Update(float dt);
	void Draw();

private:
	sf::Sprite m_sprite;
};

#endif // !GS_GAME_OVER


