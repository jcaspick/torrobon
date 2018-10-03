#include "SpriteSheet.h"
#include <fstream>
#include <sstream>
#include <iostream>

SpriteSheet::SpriteSheet(const std::string& config) :
	m_currentFrame(0),
	m_elapsed(0.0f),
	m_isPaused(false),
	m_looped(true)
{
	LoadConfig(config);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_frameSize.x / 2, m_frameSize.y / 2);
	SetFrame(0);
}

SpriteSheet::~SpriteSheet() {}

void SpriteSheet::Update(float dt) {
	if (m_isPaused) { return; }
	m_elapsed += dt;
	while (m_elapsed > m_frameTime) {
		m_currentFrame++;
		Clip clip = m_animations[m_currentAnimation].second;
		if (m_currentFrame >= clip.size()) { 
			if (m_looped) { m_currentFrame = 0; }
			else { m_currentFrame = clip.size() - 1; Pause(); }
		}
		SetFrame(clip[m_currentFrame]);
		//SetFrame(clip[m_currentFrame % (clip.size() - 1)]);
		m_elapsed -= m_frameTime;
	}
}

void SpriteSheet::Draw(sf::RenderWindow* window) {
	window->draw(m_sprite);
}

void SpriteSheet::SetAnimation(const std::string& clip) {
	if (m_animations.find(clip) != m_animations.end()) {
		m_currentAnimation = clip;
		if (m_animations[clip].first) {
			m_sprite.setScale({
				-(abs(m_sprite.getScale().x)),
				m_sprite.getScale().y
			});
		}
		else {
			m_sprite.setScale({
				abs(m_sprite.getScale().x),
				m_sprite.getScale().y
			});
		}
	}
	SetFrame(m_animations[m_currentAnimation].second[0]);
}

void SpriteSheet::SetPosition(const sf::Vector2f& pos) {
	m_sprite.setPosition(pos);
}

void SpriteSheet::SetRotation(const float& degrees) {
	m_sprite.setRotation(degrees);
}

void SpriteSheet::SetScale(const sf::Vector2f& scale) {
	m_sprite.setScale(scale);
}

void SpriteSheet::SetLooped(const bool& setting) {
	m_looped = setting;
}

sf::Vector2i SpriteSheet::GetSize() { return m_frameSize; }

void SpriteSheet::Play() { m_isPaused = false; }

void SpriteSheet::Pause() { m_isPaused = true; }

bool SpriteSheet::IsPaused() { return m_isPaused; }

bool SpriteSheet::IsLooped() { return m_looped; }

void SpriteSheet::SetFrame(int frame) {
	m_sprite.setTextureRect({
		frame % m_frames.x * m_frameSize.x,
		frame / m_frames.x * m_frameSize.y,
		m_frameSize.x,
		m_frameSize.y
	});
}

void SpriteSheet::LoadConfig(const std::string& path) {
	std::ifstream config;
	config.open(path);
	if (!config.is_open()) {
		std::cout << "! could not load sprite sheet config file: " << path << std::endl;
		return;
	}
	std::string line;
	while (std::getline(config, line)) {
		std::stringstream keystream(line);
		std::string type;
		keystream >> type;
		if (type == "TEXTURE") {
			std::string texturePath;
			keystream >> texturePath;
			m_texture.loadFromFile(texturePath);
		}
		else if (type == "FRAMESIZE") {
			keystream >> m_frameSize.x >> m_frameSize.y;
		}
		else if (type == "FRAMES") {
			keystream >> m_frames.x >> m_frames.y;
		}
		else if (type == "FRAMERATE") {
			float framerate;
			keystream >> framerate;
			m_frameTime = 1 / framerate;
		}
		else if (type == "CLIP") {
			std::pair<bool, Clip> clip;
			std::string name;
			keystream >> clip.first;
			keystream >> name;
			Frame frame;
			while (keystream >> frame) {
				clip.second.emplace_back(frame);
			}
			m_animations.insert({ name, clip });
			if (m_currentAnimation == "") { m_currentAnimation = name; }
		}
	}
	config.close();
	return;
}