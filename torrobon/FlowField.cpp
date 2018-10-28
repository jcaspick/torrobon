#include "FlowField.h"
#include "Utilities.h"
#include <queue>
#include <iostream>
#include <functional>

struct IndexValue {
	IndexValue(int i, float v) : index(i), value(v) {};
	~IndexValue() {};

	int index;
	float value;

	friend bool operator>(const IndexValue& lhs, const IndexValue& rhs) {
		return lhs.value > rhs.value;
	}
	friend bool operator<(const IndexValue& lhs, const IndexValue& rhs) {
		return lhs.value < rhs.value;
	}
};

FlowField::FlowField(const int width, const int height, const float cellSize) :
	m_width(width + 1),
	m_height(height + 1),
	m_gridSize((width + 1) * (height + 1)),
	m_cellSize(cellSize),
	m_densityField((width + 1) * (height + 1)),
	m_potentialField((width + 1) * (height + 1)),
	m_flowField((width + 1) * (height + 1)),
	maxDensity(5)
{
	debugFont.loadFromFile("fonts/arial.ttf");
}

FlowField::~FlowField() {}

void FlowField::Update() {
	BuildDensityField();
	BuildPotentialField();
	BuildFlowField();
}

float FlowField::QueryDensity(sf::Vector2f point) {
	return 0;
}

sf::Vector2f FlowField::QueryFlowField(sf::Vector2f point) {
	int a = CoordsToIndex(sf::Vector2i(
		(int)floor(point.x / m_cellSize),
		(int)floor(point.y / m_cellSize)));
	int b = CoordsToIndex(sf::Vector2i(
		(int)ceil(point.x / m_cellSize),
		(int)floor(point.y / m_cellSize)));
	int c = CoordsToIndex(sf::Vector2i(
		(int)ceil(point.x / m_cellSize),
		(int)ceil(point.y / m_cellSize)));
	int d = CoordsToIndex(sf::Vector2i(
		(int)floor(point.x / m_cellSize),
		(int)ceil(point.y / m_cellSize)));

	float u = (point.x - IndexToPosition(a).x) / m_cellSize;
	float v = (point.y - IndexToPosition(a).y) / m_cellSize;

	sf::Vector2f abu = Utils::Lerp(m_flowField[a], m_flowField[b], u);
	sf::Vector2f dcu = Utils::Lerp(m_flowField[d], m_flowField[c], u);
	return Utils::Lerp(abu, dcu, v);
}

void FlowField::BuildDensityField() {
	for (int i = 0; i < m_gridSize; i++) {
		float density = 0;
		sf::Vector2f cellCenter = IndexToPosition(i);
		for (int j = 0; j < m_data.size(); j++) {
			sf::Vector2f offset = m_data[j] - cellCenter;
			float contribution = 1 - (offset.x * offset.x + offset.y * offset.y) / 7500;
			density += std::fmaxf(0, contribution);
		}
		m_densityField[i] = std::fminf(maxDensity, density);
	}
}

void FlowField::BuildPotentialField() {
	int targetIndex = PositionToIndex(m_target);
	std::priority_queue<IndexValue, std::vector<IndexValue>, std::greater<IndexValue>> open;
	std::vector<int> seen;
	highestCost = 0;

	// reset field to some arbitrary large value
	std::fill(m_potentialField.begin(), m_potentialField.end(), 10000.0f);

	// set goal cost to 0 and add to neighbor list
	m_potentialField[targetIndex] = 0.0f;
	open.push(IndexValue(targetIndex, 0.0f));
	seen.emplace_back(targetIndex);

	int iterations = 0;
	while (open.size() > 0) {
		iterations++;
		if (iterations > 10000) {
			std::cout << "max iterations reached" << std::endl;
			break;
		}

		// choose the node with the lowest cost
		int currentIndex = open.top().index;
		open.pop();

		// look at each neighbor of the current node
		std::vector<Coords> neighbors = GetNeighbors(IndexToCoords(currentIndex));
		for (auto itr : neighbors) {
			int neighborIndex = CoordsToIndex(itr);

			// calculate the cost of each neighbor
			float neighborCost = m_potentialField[currentIndex] +
				m_densityField[neighborIndex] + 1;

			// update the field if a lower cost was found
			if (neighborCost < m_potentialField[neighborIndex]) {

				// add this node to the seen list if it isn't there already
				if (std::find(seen.begin(), seen.end(), neighborIndex) == seen.end()) {
					seen.emplace_back(neighborIndex);
					open.push(IndexValue(neighborIndex, neighborCost));
				}

				m_potentialField[neighborIndex] = neighborCost;
				if (neighborCost > highestCost) highestCost = neighborCost;
			}
		}
	}
}

void FlowField::BuildFlowField() {
	for (int i = 0; i < m_gridSize; i++) {
		Coords coord = IndexToCoords(i);
		float costLeft = IsValid(Left(coord)) ? 
			m_potentialField[CoordsToIndex(Left(coord))] : 10000.0f;
		float costRight = IsValid(Right(coord)) ?
			m_potentialField[CoordsToIndex(Right(coord))] : 10000.0f;
		float costUp = IsValid(Up(coord)) ?
			m_potentialField[CoordsToIndex(Up(coord))] : 10000.0f;
		float costDown = IsValid(Down(coord)) ?
			m_potentialField[CoordsToIndex(Down(coord))] : 10000.0f;

		m_flowField[i] = Utils::Normalize(sf::Vector2f(
			costLeft - costRight, costUp - costDown));
	}
}

void FlowField::DebugDraw(sf::RenderWindow* window) {
	sf::RectangleShape overlay;
	overlay.setSize({ m_cellSize - 2, m_cellSize - 2 });
	overlay.setOrigin({ (m_cellSize - 2) * 0.5f, (m_cellSize - 2) * 0.5f });

	for (int i = 0; i < m_gridSize; i++) {
		Coords coords = IndexToCoords(i);
		overlay.setFillColor(sf::Color(255, 0, 0, (m_densityField[i] / maxDensity) * 120));
		overlay.setPosition(sf::Vector2f(coords.x * m_cellSize, coords.y * m_cellSize));
		window->draw(overlay);
	}

	for (int i = 0; i < m_gridSize; i++) {
		Coords coords = IndexToCoords(i);
		overlay.setFillColor(sf::Color(0, 255, 0, (m_potentialField[i] / highestCost) * 120));
		overlay.setPosition(sf::Vector2f(coords.x * m_cellSize, coords.y * m_cellSize));
		window->draw(overlay);
	}

	overlay.setSize({ 2, m_cellSize * 0.5f });
	overlay.setOrigin({ 1, m_cellSize * 0.5f });
	overlay.setFillColor(sf::Color::Blue);
	for (int i = 0; i < m_gridSize; i++) {
		sf::Vector2f pos = IndexToPosition(i);
		overlay.setPosition(pos);
		overlay.setRotation(Utils::Vec2Rot(m_flowField[i]));
		window->draw(overlay);
	}

	overlay.setPosition((sf::Vector2f)sf::Mouse::getPosition(*window));
	overlay.setRotation(Utils::Vec2Rot(QueryFlowField((sf::Vector2f)sf::Mouse::getPosition(*window))));
	window->draw(overlay);
}

Coords FlowField::IndexToCoords(int i) {
	return sf::Vector2i(i % m_width, i / m_width);
}

sf::Vector2f FlowField::IndexToPosition(int i) {
	return sf::Vector2f(
		(i % m_width) * m_cellSize,
		(i / m_width) * m_cellSize);
}

int FlowField::CoordsToIndex(Coords coords) {
	return coords.y * m_width + coords.x;
}

sf::Vector2f FlowField::CoordsToPosition(Coords coords) {
	return sf::Vector2f(coords.x * m_cellSize, coords.y * m_cellSize);
}

Coords FlowField::PositionToCoords(sf::Vector2f pos) {
	return sf::Vector2i(
		(int)ceil((pos.x - m_cellSize * 0.5f) / m_cellSize),
		(int)ceil((pos.y - m_cellSize * 0.5f) / m_cellSize));
}

int FlowField::PositionToIndex(sf::Vector2f pos) {
	return CoordsToIndex(PositionToCoords(pos));
}

Coords FlowField::Left(Coords coords) {
	return sf::Vector2i(coords.x - 1, coords.y);
}

Coords FlowField::Right(Coords coords) {
	return sf::Vector2i(coords.x + 1, coords.y);
}

Coords FlowField::Up(Coords coords) {
	return sf::Vector2i(coords.x, coords.y - 1);
}

Coords FlowField::Down(Coords coords) {
	return sf::Vector2i(coords.x, coords.y + 1);
}

bool FlowField::IsValid(Coords coords) {
	return (
		coords.x >= 0 &&
		coords.x < m_width &&
		coords.y >= 0 &&
		coords.y < m_height);
}

std::vector<Coords> FlowField::GetNeighbors(Coords coords) {
	std::vector<Coords> neighbors;
	if (IsValid(Left(coords))) neighbors.emplace_back(Left(coords));
	if (IsValid(Right(coords))) neighbors.emplace_back(Right(coords));
	if (IsValid(Up(coords))) neighbors.emplace_back(Up(coords));
	if (IsValid(Down(coords))) neighbors.emplace_back(Down(coords));
	return neighbors;
}

// setters
void FlowField::SetData(std::vector<sf::Vector2f> data) {
	m_data = data;
}

void FlowField::SetTarget(sf::Vector2f target) {
	m_target = target;
}