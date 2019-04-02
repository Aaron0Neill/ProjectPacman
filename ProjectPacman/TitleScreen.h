//Author: Aaron O Neill
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


class TitleScreen
{
private:

	sf::Font m_font;
	sf::Text m_text;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_background;

	sf::RectangleShape m_playButton;
	sf::RectangleShape m_settingsButton;
	sf::RectangleShape m_exitButton;

	sf::Text m_playText;
	sf::Text m_settingsText;
	sf::Text m_exitText;

public:
	TitleScreen();
	~TitleScreen();

	void processEvents(sf::Event &t_event, sf::RenderWindow &); //function to check for mouse click
	void setupFont(); //setup for font and text
	void setupSprite(); //setup for the sprites
	void setupButtonText(sf::Text &t_shape, std::string t_message, sf::Vector2f t_pos); //function to setup all the text objects
	void update(sf::RenderWindow & t_window); //main update for the screen
	void render(sf::RenderWindow & t_window); //renders the screen
};

