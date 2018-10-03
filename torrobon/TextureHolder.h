#pragma once
#ifndef TEXTUREHOLDER
#define TEXTUREHOLDER
#include <SFML/Graphics.hpp>
#include <unordered_map>

class TextureHolder {

public:
	TextureHolder(const std::string& config);
	~TextureHolder();

	sf::Texture* GetTexture(const std::string& name);

private:
	void Load(const std::string& path);
	void Purge();
	std::unordered_map<std::string, sf::Texture*> m_textureLibrary;

};

#endif // !TEXTUREHOLDER