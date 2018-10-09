#pragma once
#ifndef ENEMY_BULLET
#define ENEMY_BULLET
#include <SFML\Graphics.hpp>

struct Context;
class EnemyBullet {

public:
	EnemyBullet(Context* context);
	~EnemyBullet();

	void Update(float dt);
	void Draw();
	void OnDeath();

	void SetSpeed(float speed);
	void SetPosition(const sf::Vector2f& pos);
	void SetDirection(const sf::Vector2f& dir);
	float GetSpeed();
	bool IsActive();
	sf::Vector2f GetPosition();
	sf::Vector2f GetDirection();
	sf::FloatRect GetRect();

private:
	void Move(const sf::Vector2f& delta);
	void UpdateRect();

	Context* m_context;
	bool m_active;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	sf::Vector2f m_direction;
	sf::Vector2f m_rectSize;
	sf::FloatRect m_rect;
	float m_speed;
};

#endif // !ENEMY_BULLET