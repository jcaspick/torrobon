#pragma once
#ifndef DIRECTIONAL_SPRITE
#define DIRECTIONAL_SPRITE
#include <SFML\Graphics.hpp>
#include "TextureHolder.h"

class DirectionalSprite {

public:
	DirectionalSprite(TextureHolder* texHolder);
	~DirectionalSprite();

	void LoadConfig(const std::string& path);
	void Draw(sf::RenderWindow* window);
	void SetDirection(float degrees);
	void SetPosition(sf::Vector2f pos);

	sf::Vector2i GetFrameSize();

private:
	std::string m_texture;
	sf::Sprite m_sprite;
	sf::Vector2i m_frameSize;
	sf::Vector2i m_frames;
	TextureHolder* m_textureHolder;
	sf::Texture m_actualTexture;
};

#endif // !DIRECTIONAL_SPRITE