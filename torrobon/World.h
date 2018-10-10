#pragma once
#ifndef WORLD
#define WORLD
#include <SFML\Graphics.hpp>

class World {

public:
	World(const sf::Vector2f& size, float thickness);
	~World();

	void Draw(sf::RenderWindow* window);
	sf::Vector2f GetSize();
	float GetWallThickness();
	
private:
	sf::Vector2f m_size;
	float m_wallThickness;
};

#endif // !WORLD
