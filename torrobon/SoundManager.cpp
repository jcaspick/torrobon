#include "SoundManager.h"

SoundManager::SoundManager() {
	soundLibrary[SoundEffect::Blip1] = MakeSoundBuffer("sounds/beep1.wav");
	soundLibrary[SoundEffect::Explosion1] = MakeSoundBuffer("sounds/explosion1.wav");
	soundLibrary[SoundEffect::Explosion2] = MakeSoundBuffer("sounds/explosion2.wav");
	soundLibrary[SoundEffect::Explosion3] = MakeSoundBuffer("sounds/explosion3.wav");
	soundLibrary[SoundEffect::Shot1] = MakeSoundBuffer("sounds/shot1.wav");
}

SoundManager::~SoundManager() {}

void SoundManager::PlaySound(SoundEffect effect) {
	for (int i = 0; i < sounds.size(); i++) {
		if (sounds[i].getStatus() == sf::Sound::Stopped) {
			sounds[i].setBuffer(*soundLibrary[effect]);
			sounds[i].play();
			break;
		}
	}
}

void SoundManager::RandomExplosion() {
	switch ((int)rand() % 3)
	{
	case 0:
		PlaySound(SoundEffect::Explosion1);
		break;
	case 1:
		PlaySound(SoundEffect::Explosion2);
		break;
	case 2:
		PlaySound(SoundEffect::Explosion3);
		break;
	}
}

sf::SoundBuffer* SoundManager::MakeSoundBuffer(const std::string& filename) {
	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
	soundBuffer->loadFromFile(filename);
	return soundBuffer;
}