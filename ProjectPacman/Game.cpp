#include "Game.h"

GameState Game::m_currentState{ GameState::GamePlayScreen };

Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32u }, "Project Pacman" },
	m_exitGame{ false }
{
}


Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float FPS = 60.0f;
	sf::Time timePerFrame = sf::seconds(1.0f / FPS); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // Run as many times as possible
		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // Run at a minimum of 60 fps
			update(timePerFrame); // 60 fps
		}
		render(); // Run as many times as possible
	}
}


void Game::processEvents()
{
	sf::Event nextEvent;
	while (m_window.pollEvent(nextEvent))
	{
		if (sf::Event::Closed == nextEvent.type) // check if the close window button is clicked on.
		{
			m_window.close();
		}
		switch (m_currentState)
		{
		case GameState::SplashScreen:
			m_splashScreen.processEvents(nextEvent);
			break;
		case GameState::TitleScreen:
			m_titleScreen.processEvents(nextEvent, m_window);
			break;
		case GameState::GamePlayScreen:
			m_gamePlay.processEvents(nextEvent);
			break;
		case GameState::SettingScreen:
			break;
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	switch (m_currentState)
	{
	case GameState::SplashScreen:
		m_splashScreen.update();
		break;
	case GameState::TitleScreen:
		m_titleScreen.update(m_window);
		break;
	case GameState::GamePlayScreen:
		m_gamePlay.update(t_deltaTime);
		break;
	case GameState::SettingScreen:
		m_settingsScreen.update();
		break;
	}
}

void Game::render()
{
	m_window.clear();

	switch (m_currentState)
	{
	case GameState::SplashScreen:
		m_splashScreen.render(m_window);
		break;
	case GameState::TitleScreen:
		m_titleScreen.render(m_window);
		break;
	case GameState::GamePlayScreen:
		m_gamePlay.render(m_window);
		break;
	case GameState::SettingScreen:
		m_settingsScreen.render(m_window);
		break;
	}

	m_window.display();
}
