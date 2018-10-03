#pragma once
#ifndef WINDOW
#define WINDOW

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window {

public:
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void Clear();
	void Draw();
	void Update();
	void Close();

	bool hasFocus();
	bool isDone();
	sf::Vector2u 
};

#endif