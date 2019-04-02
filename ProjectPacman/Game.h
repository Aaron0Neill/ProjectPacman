//Author Aaron O Neill
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameStates.h"

#include "GamePlay.h"
#include "SettingsScreen.h"
#include "SplashScreen.h"
#include "TitleScreen.h"


class Game
{
public:
	Game();
	~Game();
	
	void run();
	static GameState m_currentState;
private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	GamePlay m_gamePlay;
	SettingsScreen m_settingsScreen;
	SplashScreen m_splashScreen;
	TitleScreen m_titleScreen;

	sf::RenderWindow m_window;
	bool m_exitGame;
};

