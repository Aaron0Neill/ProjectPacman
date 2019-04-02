//Author: Aaron O Neill
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class SettingsScreen
{
private:

	sf::Font m_font;
	sf::Text m_text;

public:
	SettingsScreen();
	~SettingsScreen();

	void setup(); //setup for font and text
	void update(); //main update for the screen
	void render(sf::RenderWindow & t_window); //renders the screen
};

