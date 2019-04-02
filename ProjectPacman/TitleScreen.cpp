#include "TitleScreen.h"
#include "Game.h"

/// <summary>
/// Default constructor
/// </summary>
TitleScreen::TitleScreen()
{
	setupFont();
	setupSprite();
}


TitleScreen::~TitleScreen()
{
}

void TitleScreen::processEvents(sf::Event & t_event , sf::RenderWindow &t_window)
{
	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		if (sf::Mouse::Left == t_event.key.code)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(t_window);
			if (mousePos.x > BUTTON_LEFT && mousePos.x < BUTTON_RIGHT)
			{
				if (mousePos.y < PLAY_BUTTON_BOTTOM && mousePos.y > PLAY_BUTTON_TOP)
				{
					Game::m_currentState = GameState::GamePlayScreen;
				}
				else if (mousePos.y < SETTINGS_BUTTON_BOTTOM && mousePos.y > SETTINGS_BUTTON_TOP)
				{
					Game::m_currentState = GameState::SettingScreen;
				}
				else if (mousePos.y < EXIT_BUTTON_BOTTOM && mousePos.y > EXIT_BUTTON_TOP)
				{
					t_window.close();
				}
			}
		}
	}

}

/// <summary>
/// function to setup the font and text for the main title screen
/// </summary>
void TitleScreen::setupFont()
{
	//setup for the font
	if (!m_font.loadFromFile("assets\\fonts\\PacmanFont.ttf"))
	{
		std::cout << "Error loading Title screen font\n";
	}
}

/// <summary>
/// function used to setup all the sprites on the main menu
/// </summary>
void TitleScreen::setupSprite()
{
	m_backgroundTexture.loadFromFile("assets\\textures\\pacmanTitle.png");
	m_background.setTexture(m_backgroundTexture);
	//setup for the button shapes
	setupButtonText(m_playText, "Play", sf::Vector2f{ 338.5, 400 });
	setupButtonText(m_settingsText, "Settings", sf::Vector2f{ 338.5,500 });
	setupButtonText(m_exitText, "Exit", sf::Vector2f{ 338.5,600 });
}


void TitleScreen::setupButtonText(sf::Text & t_text, std::string t_message, sf::Vector2f t_pos)
{
	t_text.setFont(m_font);
	t_text.setCharacterSize(32);
	t_text.setString(t_message);
	t_text.setOrigin(t_text.getGlobalBounds().width / 2.0, t_text.getGlobalBounds().height / 2.0);
	t_text.setPosition(t_pos);
	t_text.setFillColor(sf::Color::Yellow);

}

/// <summary>
/// 
/// </summary>
/// <param name="t_window"></param>
void TitleScreen::update(sf::RenderWindow & t_window)
{
}

/// <summary>
/// function to draw the title screen
/// </summary>
void TitleScreen::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_background);
	t_window.draw(m_playText);
	t_window.draw(m_settingsText);
	t_window.draw(m_exitText);
	t_window.draw(m_text);
}
