#pragma once
#ifndef FLOWFIELD
#define FLOWFIELD
#include <SFML\Graphics.hpp>

class Entity;

using FloatField = std::vector<float>;
using VectorField = std::vector<sf::Vector2f>;
using Coords = sf::Vector2i;

class FlowField {

public:
	FlowField(const int width, const int height, const float cellSize);
	~FlowField();

	void Update();
	void DebugDraw(sf::RenderWindow*);
	void SetData(std::vector<Entity*>);
	void SetTarget(sf::Vector2f);

	float QueryDensity(sf::Vector2f);
	sf::Vector2f QueryFlowField(sf::Vector2f);

private:
	void BuildDensityField();
	void BuildPotentialField();
	void BuildFlowField();

	Coords IndexToCoords(int);
	sf::Vector2f IndexToPosition(int);
	int CoordsToIndex(Coords);
	sf::Vector2f CoordsToPosition(Coords);
	Coords PositionToCoords(sf::Vector2f);
	int PositionToIndex(sf::Vector2f);

	Coords Left(Coords);
	Coords Right(Coords);
	Coords Up(Coords);
	Coords Down(Coords);

	bool IsValid(Coords);
	std::vector<Coords> GetNeighbors(Coords);

	const int m_width;
	const int m_height;
	const int m_gridSize;
	const float m_cellSize;
	const float maxDensity;

	FloatField m_densityField;
	FloatField m_potentialField;
	VectorField m_flowField;

	std::vector<Entity*> m_data;
	sf::Vector2f m_target;

	float highestCost;
	sf::Font debugFont;
};

#endif // !FLOWFIELD