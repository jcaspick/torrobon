#pragma once
#ifndef BULLET
#define BULLET
#include <SFML\Graphics.hpp>

struct Context;
class Bullet {

public:
	Bullet(Context* context, sf::Vector2f pos, sf::Vector2f dir, float speed);
	~Bullet();

	virtual void Update(float dt);
	virtual void Draw() = 0;
	virtual void OnDeath();
	void Move(sf::Vector2f delta);

	void SetPosition(sf::Vector2f pos);
	void SetDirection(sf::Vector2f dir);
	void SetAlive(bool alive);
	void SetSpeed(float speed);

	sf::Vector2f GetPosition();
	sf::Vector2f GetDirection();
	sf::FloatRect GetRect();
	bool IsAlive();

protected:
	void UpdateRect();

	Context* m_context;
	sf::Vector2f m_position;
	sf::Vector2f m_rectSize;
	sf::Vector2f m_direction;
	float m_speed;
	sf::FloatRect m_rect;
	bool m_alive;
};

#endif // !BULLET