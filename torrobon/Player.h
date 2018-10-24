#pragma once
#ifndef PLAYER
#define PLAYER
#include "SpriteSheet.h"
#include "Repeater.h"

struct Context;

class Player {
	
public:
	Player(Context* context);
	~Player();

	void Update(float dt);
	void Draw();
	void AddEnergy(float energy);
	void Kill();

	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition();
	sf::FloatRect GetRect();
	sf::FloatRect GetHitbox();
	float GetCollectionRadius();
	float GetEnergy();
	bool IsAlive();

private:
	void UpdateAABB();
	void HandleInput();
	void ShootBasic();
	void ShootSuper();
	void EnforceWorldBoundary();

	Context* m_context;
	float m_speed;
	float m_elapsed;
	float m_shotInterval;
	bool m_shooting;
	sf::Vector2f m_position;
	sf::Vector2f m_deltaPos;
	sf::Vector2f m_mousePos;
	sf::Sprite m_sprite;
	std::string m_texture;
	sf::FloatRect m_rect;
	sf::FloatRect m_hitbox;
	sf::Vector2f m_rectSize;
	sf::Vector2f m_hitboxSize;
	float m_energy;
	float m_collectionRadius;
	sf::CircleShape m_radius;
	bool m_super;
	float m_energyDrainRate;
};

#endif // !PLAYER