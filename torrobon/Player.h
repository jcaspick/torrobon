#pragma once
#ifndef PLAYER
#define PLAYER
#include "SpriteSheet.h"

struct Context;

class Player {
	
public:
	Player(Context* context);
	~Player();

	void Update(float dt);
	void Draw();
	void Kill();

	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition();
	sf::FloatRect GetAABB();
	bool IsAlive();

private:
	void UpdateAABB();
	void HandleInput();
	void EnforceWorldBoundary();

	float m_speed;
	float m_elapsed;
	float m_shotInterval;
	bool m_shooting;
	bool m_alive;
	sf::Vector2f m_position;
	sf::Vector2f m_deltaPos;
	sf::Vector2f m_mousePos;
	sf::Sprite m_sprite;
	std::string m_texture;
	sf::FloatRect m_AABB;
	Context* m_context;
};

#endif // !PLAYER