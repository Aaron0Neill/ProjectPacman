//Author: Aaron O Neill
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include "Globals.h"
#include "GameStates.h"
#include "Cell.h"
#include "Pacman.h"
#include "Ghost.h"


class GamePlay
{
private:

	sf::Font m_font;
	sf::Text m_enterNameText;
	sf::Text m_nameText;
	sf::Text m_scoreText;
	sf::Text m_scoreBoard;
	sf::Text m_livesText;
	sf::Text m_gameOverText;
	sf::Text m_highScore;
	sf::Text m_restartText;
	sf::Text m_pauseText;
	std::string m_name;
	sf::Texture m_blurryTexture;
	sf::Sprite m_imageBlur;

	int m_score{ 0 };  //main game score
	int m_powerTimer{ 0 };
	int m_multiplier{ 1 };
	bool m_caps{ false };
	bool m_addScore{ true };
	bool m_poweredUp{ false };
	Cell m_maze[MAX_ROWS][MAX_COLS]; //2D array of whats in each cell

	Pacman m_player; // main player
	Ghost m_ghost[MAX_ENEMIES]; //main Enemy array
	static inGameState m_gameState; //state that the game is in

public:
	GamePlay();
	~GamePlay();

	void processEvents(sf::Event &t_event); //function to process events
	void setupFontandText(); //setup for font and text
	void setupMaze(); //function to setup the maze
	void update(sf::Time dt); //main update for the screen
	void render(sf::RenderWindow & t_window); //renders the screen
	void enterName(sf::Event &t_event); //function that allows the player to enter their name
	void eat(); //get pacman to eat the pellets when he goes into the same column as them
	void collision(); //function that checks if pacman interacts with any of the ghosts
	void updateScoreboard(); //function to update the scoreBoard
	void restart(sf::Event &);

};

