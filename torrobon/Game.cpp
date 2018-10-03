#include "Game.h"

Game::Game() :
	m_clock(),
	m_dt(),
	m_textures("config/textures.cfg"),
	m_bulletManager(&m_context),
	m_enemyManager(&m_context),
	m_effectManager(&m_context),
	m_player(nullptr)
{
	m_window.create(sf::VideoMode(800, 600, 32), "torrobon", sf::Style::Default);
	m_clock.restart();
	srand(time(nullptr));

	m_context.m_window = &m_window;
	m_context.m_textureHolder = &m_textures;
	m_context.m_bulletManager = &m_bulletManager;
	m_context.m_enemyManager = &m_enemyManager;
	m_context.m_effectManager = &m_effectManager;
	m_context.m_playerPos = &m_playerPos;

	m_player = new Player(&m_context);
	m_player->SetPosition({ 200, 200 });
}

Game::~Game() {};

void Game::Update() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) { m_window.close(); }
	}

	m_player->Update(m_dt);
	m_bulletManager.Update(m_dt);
	m_effectManager.Update(m_dt);
	m_enemyManager.Update(m_dt);
	m_playerPos = m_player->GetPosition();

	m_dt = m_clock.restart().asSeconds();
}

void Game::Draw() {
	m_window.clear(sf::Color::Black);
	m_player->Draw();
	m_enemyManager.Draw();
	m_bulletManager.Draw();
	m_effectManager.Draw();
	m_window.display();
}

sf::RenderWindow* Game::GetWindow() { return &m_window; }