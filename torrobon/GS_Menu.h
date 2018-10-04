#pragma once
#ifndef GS_MENU
#define GS_MENU
#include "GameState.h"
#include <SFML\Graphics.hpp>

class GS_Menu : public GameState {

public:
	GS_Menu(StateManager* stateMgr);
	~GS_Menu();

	void OnEnable();
	void OnDisable();
	void OnCreate();
	void OnDestroy();
	void Update(float dt);
	void Draw();

private:
	sf::Sprite m_sprite;
};

#endif // !GS_MENU
