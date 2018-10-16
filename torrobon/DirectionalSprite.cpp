#include "DirectionalSprite.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

DirectionalSprite::DirectionalSprite(TextureHolder* texHolder) :
	m_textureHolder(texHolder)
{}

DirectionalSprite::~DirectionalSprite() {};

void DirectionalSprite::Draw(sf::RenderWindow* window) {
	window->draw(m_sprite);
}

void DirectionalSprite::SetDirection(float degrees) {
	if (degrees < 0) { degrees += 360; }
	int frame = (int(degrees + 0.5) / (360 / (m_frames.x * m_frames.y))) % 16;

	m_sprite.setTextureRect({
		frame % m_frames.x * m_frameSize.x,
		frame / m_frames.x * m_frameSize.y,
		m_frameSize.x,
		m_frameSize.y
	});
}

void DirectionalSprite::SetPosition(sf::Vector2f pos) {
	m_sprite.setPosition(pos);
};

void DirectionalSprite::LoadConfig(const std::string& path) {
	std::ifstream config;
	config.open(path);
	if (!config.is_open()) {
		std::cout << "! directional sprite could not load config file: " << path << std::endl;
	}
	std::string line;
	while (std::getline(config, line)) {
		std::stringstream keystream(line);
		std::string type;
		keystream >> type;
		if (type == "TEXTURE") {
			keystream >> m_texture;
			m_sprite.setTexture(*m_textureHolder->GetTexture(m_texture));
		}
		else if (type == "FRAMESIZE") {
			keystream >> m_frameSize.x >> m_frameSize.y;
			m_sprite.setOrigin(m_frameSize.x / 2, m_frameSize.y / 2);
		}
		else if (type == "FRAMES") {
			keystream >> m_frames.x >> m_frames.y;
		}
	}
	config.close();
}

// setters

// getters
sf::Vector2i DirectionalSprite::GetFrameSize() { return m_frameSize; }