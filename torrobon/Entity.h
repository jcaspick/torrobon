#pragma once
#ifndef ENTITY
#define ENTITY
#include <SFML\Graphics.hpp>

enum class Anchor {
	Center,
	Bottom
};

struct Context;
class Entity {

public:
	Entity(Context* context);
	~Entity();

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	void AddDamage(const float& damage);
	void Move(const sf::Vector2f& delta);

	void SetPosition(const sf::Vector2f& pos);
	void SetCollisionSize(const sf::Vector2f& size);
	void SetCollisionOffset(const sf::Vector2f& offset);

	sf::Vector2f GetPosition();
	sf::Vector2f GetCollisionSize();
	sf::Vector2f GetCollisionOffset();
	sf::FloatRect GetRect();
	float GetHealth();

protected:
	void UpdateRect();

	Context* m_context;
	sf::Vector2f m_position;
	sf::Vector2f m_rectSize;
	sf::Vector2f m_rectOffset;
	Anchor m_rectAnchor;
	sf::FloatRect m_rect;
	float m_health;
};

#endif // !ENTITY
