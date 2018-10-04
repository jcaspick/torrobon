#pragma once
#ifndef PLAYER
#define PLAYER
#include "Context.h"
#include "SpriteSheet.h"

class Player {
	
public:
	Player(Context* context);
	~Player();

	void Update(float dt);
	void Draw();

	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition();

private:
	void HandleInput();
	void EnforceWorldBoundary();

	float m_speed;
	float m_elapsed;
	float m_shotInterval;
	bool m_shooting;
	sf::Vector2f m_position;
	sf::Vector2f m_deltaPos;
	sf::Vector2f m_mousePos;
	sf::Sprite m_sprite;
	std::string m_texture;
	Context* m_context;
};

#endif // !PLAYER