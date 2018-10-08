#pragma once
#ifndef UTILITIES
#define UTILITIES
#include <SFML\System\Vector2.hpp>
#include <cmath>
#define DEG2RAD 0.0174533f
#define RAD2DEG 57.2958f

namespace Utils {
	// values are converted to match the conventions of SFML
	// clockwise with 0 degrees facing up
	inline sf::Vector2f Rot2Vec(float degrees) {
		return{ sinf(DEG2RAD * degrees), -cosf(DEG2RAD * degrees) };
	}

	inline float Vec2Rot(sf::Vector2f vector) {
		return atan2f(vector.x, -vector.y) * RAD2DEG;
	}

	inline sf::Vector2f Normalize(sf::Vector2f vector) {
		float length = std::hypotf(vector.x, vector.y);
		if (length != 0) vector /= length;
		return vector;
	}
}

#endif // !UTILITIES