#include "TextureHolder.h"
#include <fstream>
#include <sstream>
#include <iostream>

TextureHolder::TextureHolder(const std::string& config) {
	Load(config);
}

TextureHolder::~TextureHolder() {
	Purge();
}

sf::Texture* TextureHolder::GetTexture(const std::string& name) {
	auto itr = m_textureLibrary.find(name);
	if (itr == m_textureLibrary.end()) {
		std::cout << "! could not get texture: " << name << std::endl;
	}
	else {
		return itr->second;
	}
}

void TextureHolder::Load(const std::string& path) {
	std::ifstream config;
	config.open(path);
	if (!config.is_open()) {
		std::cout << "! texture holder could not open config file: " << path << std::endl;
	}
	std::string line;
	while (std::getline(config, line)) {
		std::stringstream keystream(line);
		std::string name;
		std::string path;
		keystream >> name >> path;
		sf::Texture* texture = new sf::Texture;
		if (!texture->loadFromFile(path)) {
			std::cout << "! could not load texture " << name << ": " << path << std::endl;
			delete texture;
			continue;
		}
		m_textureLibrary.emplace(name, texture);
	}
	config.close();
}

void TextureHolder::Purge() {
	while (m_textureLibrary.begin() != m_textureLibrary.end()) {
		delete m_textureLibrary.begin()->second;
		m_textureLibrary.erase(m_textureLibrary.begin());
	}
}