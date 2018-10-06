#include "Game.h"

Game::Game() :
	m_clock(),
	m_dt(),
	m_textures("config/textures.cfg"),
	m_stateMgr(&m_context)
{
	m_window.create(sf::VideoMode(800, 800, 32), "torrobon", sf::Style::Default);
	m_clock.restart();
	srand(time(nullptr));

	m_context.m_window = &m_window;
	m_context.m_textureHolder = &m_textures;

	m_stateMgr.SetState(StateType::Menu);
}

Game::~Game() {};

void Game::Update() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) { m_window.close(); }
	}

	m_stateMgr.Update(m_dt);
	m_stateMgr.ProcessRemovals();
	m_dt = m_clock.restart().asSeconds();
}

void Game::Draw() {
	m_window.clear(sf::Color::Black);
	m_stateMgr.Draw();
	m_window.display();
}

sf::RenderWindow* Game::GetWindow() { return &m_window; }