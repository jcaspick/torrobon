#include "World.h"

World::World(const sf::Vector2f& size, float thickness) :
	m_size(size),
	m_wallThickness(thickness)
{}

World::~World() {}

void World::Draw(sf::RenderWindow* window) {
	sf::RectangleShape wallH = sf::RectangleShape({ m_size.x, m_wallThickness });
	sf::RectangleShape wallV = sf::RectangleShape({ m_wallThickness, m_size.y });
	wallH.setFillColor(sf::Color::Magenta);
	wallV.setFillColor(sf::Color::Magenta);

	wallH.setPosition({ 0, 0 });
	window->draw(wallH);
	wallH.setPosition({ 0, m_size.y - m_wallThickness });
	window->draw(wallH);
	wallV.setPosition({ 0, 0 });
	window->draw(wallV);
	wallV.setPosition({ m_size.x - m_wallThickness, 0 });
	window->draw(wallV);
}

// getters
sf::Vector2f World::GetSize() { return m_size; }
float World::GetWallThickness() { return m_wallThickness; }