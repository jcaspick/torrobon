#pragma once
#ifndef SPRITESHEET
#define SPRITESHEET
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <unordered_map>

class SpriteSheet {
	using Frame = unsigned int;
	using Clip = std::vector<Frame>;
	using Animations = std::unordered_map<std::string, std::pair<bool, Clip>>;

public:
	SpriteSheet(const std::string& config);
	~SpriteSheet();

	void Update(float dt);
	void Draw(sf::RenderWindow* window);
	void Play();
	void Pause();

	void SetAnimation(const std::string& clip);
	void SetPosition(const sf::Vector2f& pos);
	void SetRotation(const float& degrees);
	void SetScale(const sf::Vector2f& scale);
	void SetLooped(const bool& setting);
	sf::Vector2i GetSize();
	bool IsPaused();
	bool IsLooped();

private:
	void LoadConfig(const std::string& path);
	void SetFrame(int frame);

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	Frame m_currentFrame;
	std::string m_currentAnimation;
	Animations m_animations;
	sf::Vector2i m_frameSize;
	sf::Vector2i m_frames;
	float m_elapsed;
	float m_frameTime;
	bool m_isPaused;
	bool m_looped;
};

#endif // !SPRITESHEET