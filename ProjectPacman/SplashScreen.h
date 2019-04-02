//Author: Aaron O Neill
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Pacman.h"

class SplashScreen
{
private:

	sf::Font m_font;
	sf::Text m_text;
	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroud;
	Pacman m_splashman;
//	Ghost m_splashGhost[MAX_ENEMIES];

public:
	SplashScreen();
	~SplashScreen();

	void setupText(); //setup for font and text
	void setupSprite(); //setup the sprites
	void processEvents(sf::Event &t_event);
	void update(); //main update for the screen
	void render(sf::RenderWindow & t_window); //renders the screen
};

