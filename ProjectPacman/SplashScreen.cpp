#include "SplashScreen.h"
#include "Game.h"


SplashScreen::SplashScreen()
{
	setupText();
	setupSprite();
}

//
SplashScreen::~SplashScreen()
{
}

/// <summary>
/// function to setup the text for the splash screen
/// </summary>
void SplashScreen::setupText()
{
	//setup for the font
	if (!m_font.loadFromFile("assets\\fonts\\ariblk.ttf"))
	{
		std::cout << "Error loading Splash screen font";
	}
	//setup for default text
	m_text.setFont(m_font);
	m_text.setString("Splash Screen\nPress any to continue");
	m_text.setFillColor(sf::Color::Black);
	m_splashman.setupSplash();
}

/// <summary>
/// function to setup sprites for the splash screen
/// </summary>
void SplashScreen::setupSprite()
{
	if (!m_backgroundTexture.loadFromFile("assets\\textures\\pacmanWallpaper.jpg"))
	{
		std::cout << "Error loading splash screen picture\n";
	}
	m_backgroud.setTexture(m_backgroundTexture);
	m_backgroud.setOrigin(m_backgroud.getGlobalBounds().width / 2.0, 0);
	m_backgroud.setPosition(338.5, 0);

}

/// <summary>
/// process input from the user
/// </summary>
/// <param name="t_event"></param>
void SplashScreen::processEvents(sf::Event & t_event)
{
	if (t_event.type == sf::Event::KeyPressed)
	{
		Game::m_currentState = GameState::TitleScreen;
	}
}

/// <summary>
/// update the game 
/// </summary>
void SplashScreen::update()
{
	m_splashman.moveSplash();
}

void SplashScreen::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_backgroud);
	t_window.draw(m_text);
	m_splashman.draw(t_window);
}
