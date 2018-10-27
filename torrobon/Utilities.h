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

	inline float Lerp(float a, float b, float t) {
		return (a * (1.0f - t)) + (b * t);
	}

	inline sf::Vector2f Lerp(sf::Vector2f a, sf::Vector2f b, float t) {
		return sf::Vector2f(
			(a.x * (1.0f - t)) + (b.x * t),
			(a.y * (1.0f - t)) + (b.y * t));
	}
}

#endif // !UTILITIES