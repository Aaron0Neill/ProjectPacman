#include "SettingsScreen.h"
#include "Game.h"


SettingsScreen::SettingsScreen()
{
	setup();
}


SettingsScreen::~SettingsScreen()
{
}

void SettingsScreen::setup()
{
	//setup for the font
	if (!m_font.loadFromFile("assets\\fonts\\ariblk.ttf"))
	{
		std::cout << "Error loading Setting screen font";
	}
	//setup for default text
	m_text.setFont(m_font);
	m_text.setString("Settings Screen\nPress escape to go back");
}

void SettingsScreen::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		Game::m_currentState = GameState::TitleScreen;
	}
}

void SettingsScreen::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_text);
}
