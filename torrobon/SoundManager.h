#pragma once
#ifndef SOUND_MANAGER
#define SOUND_MANAGER
#include <SFML\Audio.hpp>
#include <unordered_map>
#include <array>

enum class SoundEffect {
	Blip1,
	Explosion1,
	Explosion2,
	Explosion3,
	Shot1
};

class SoundManager {

public:
	SoundManager();
	~SoundManager();

	void PlaySound(SoundEffect);
	void RandomExplosion();

private:
	sf::SoundBuffer* MakeSoundBuffer(const std::string& filename);

	std::unordered_map<SoundEffect, sf::SoundBuffer*> soundLibrary;
	std::array<sf::Sound, 128> sounds;
};

#endif // !SOUND_MANAGER