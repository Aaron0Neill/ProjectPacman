#include "GamePlay.h"
#include "Game.h"

inGameState GamePlay::m_gameState = { inGameState::takeName };

GamePlay::GamePlay()
{
	setupFontandText();
	setupMaze();
}


GamePlay::~GamePlay()
{
}

/// <summary>
/// function to process events
/// </summary>
/// <param name="t_event">Event to be processed</param>
void GamePlay::processEvents(sf::Event &t_event)
{
	if (t_event.type == sf::Event::KeyPressed)
	{
		if (t_event.key.code == sf::Keyboard::Escape)
		{
			m_gameState = inGameState::pauseGame;
		}
	}
	switch (m_gameState)
	{
	case inGameState::takeName:
		enterName(t_event);
		break;
	case inGameState::inGame:
		m_player.processEvents(t_event);
		break;
	case inGameState::pauseGame:
		if (t_event.type == sf::Event::KeyPressed)
			if (t_event.key.code == sf::Keyboard::Space)
				m_gameState = inGameState::inGame;
		break;
	case inGameState::endGame:
		restart(t_event);
		break;
	default:
		break;
	}
}

/// <summary>
/// function to setup main game
/// </summary>
void GamePlay::setupFontandText()
{
	//setup image blur
	if (!m_blurryTexture.loadFromFile("assets\\textures\\ImageBlur.jpg"))
	{
		std::cout << "Error loading image blur";
	}
	m_imageBlur.setTexture(m_blurryTexture);
	m_imageBlur.setColor(sf::Color(100, 100, 100, 155));
	//setup for the font
	if (!m_font.loadFromFile("assets\\fonts\\ariblk.ttf"))
	{
		std::cout << "Error loading Gameplay screen font";
	}
	//setup for default text
	m_enterNameText.setFont(m_font);
	m_enterNameText.setString("Please enter your name: ");
	m_enterNameText.setCharacterSize(24);
	m_enterNameText.setFillColor(sf::Color::White);

	m_nameText.setFont(m_font);
	m_nameText.setCharacterSize(24);
	m_nameText.setPosition(m_enterNameText.getPosition().x + m_enterNameText.getGlobalBounds().width, m_enterNameText.getPosition().y);
	m_nameText.setFillColor(sf::Color::White);
	
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(24);
	m_scoreText.setPosition(0, 750);
	m_scoreText.setFillColor(sf::Color::White);

	m_livesText.setFont(m_font);
	m_livesText.setCharacterSize(24);
	m_livesText.setString("Lives:   ");
	m_livesText.setPosition(SCREEN_WIDTH - m_livesText.getGlobalBounds().width, 750);
	m_livesText.setFillColor(sf::Color::White);

	m_gameOverText.setFont(m_font);
	m_gameOverText.setCharacterSize(48);
	m_gameOverText.setOrigin(m_gameOverText.getGlobalBounds().width / 2.0, m_gameOverText.getGlobalBounds().height / 2.0);
	m_gameOverText.setPosition(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0);
	m_gameOverText.setFillColor(sf::Color::Red);

	m_highScore.setFont(m_font);
	m_highScore.setCharacterSize(40);
	m_highScore.setString("ScoreBoard");
	m_highScore.setOrigin(m_highScore.getGlobalBounds().width / 2.0, 0);
	m_highScore.setPosition(SCREEN_WIDTH / 2.0, 0);
	m_highScore.setFillColor(sf::Color::Yellow);

	m_scoreBoard.setFont(m_font);
	m_scoreBoard.setCharacterSize(24);
	m_scoreBoard.setFillColor(sf::Color::White);
	m_scoreBoard.setPosition(0, 50);

	m_restartText.setFont(m_font);
	m_restartText.setCharacterSize(24);
	m_restartText.setFillColor(sf::Color::White);
	m_restartText.setString("Press any key to continue");
	m_restartText.setOrigin(m_restartText.getGlobalBounds().width / 2.0, 0);
	m_restartText.setPosition(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - m_restartText.getGlobalBounds().height - 10);

	m_pauseText.setFont(m_font);
	m_pauseText.setCharacterSize(48);
	m_pauseText.setFillColor(sf::Color::Green);
	m_pauseText.setString("\t\t\tPaused\nPress space to contine");
	m_pauseText.setOrigin(m_pauseText.getGlobalBounds().width / 2.0, m_pauseText.getGlobalBounds().height / 2.0);
	m_pauseText.setPosition(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0);
}

/// <summary>
/// function to setup the maze
/// </summary>
void GamePlay::setupMaze()
{
	//***************************************
	//Maze cheat sheet
	//0 empty cell
	//1 pellet
	//2 power pellet
	//3 Vertical wall
	//4 horizontal wall
	//5 top left corner
	//6 top right corner
	//7 bottom right corner
	//8 bottom left corner
	//9 intersection Right
	//10 intersection left
	//11 intersection down
	//12 intersection up
	//13 wall end left
	//14 wall end right
	//15 wall end up
	//16 wall end down
	// 4-way Split
	//***************************************
	//create new 2D array to design the map
	int setupData[MAX_ROWS][MAX_COLS] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 5, 4, 4, 4, 4, 4, 4, 4, 4, 4,11, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6 },
	{ 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3 },
	{ 3, 1, 5, 4, 6, 1,15, 1,15, 1, 3, 1,15, 1,15, 1, 5, 4, 6, 1, 3 },
	{ 3, 1, 8, 4, 7, 1,16, 1,16, 1,16, 1,16, 1,16, 1, 8, 4, 7, 1, 3 },
	{ 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3 },
	{ 3, 1, 5, 6, 1,15, 1,13, 4, 4,11, 4, 4,14, 1,15, 1, 5, 6, 1, 3 },
	{ 3, 1, 8, 7, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 8, 7, 1, 3 },
	{ 3, 1, 1, 1, 1, 9, 4, 4,14, 1,16, 1,13, 4, 4,10, 1, 1, 1, 1, 3 },
	{ 8, 4, 4, 6, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 5, 4, 4, 7 },
	{ 4, 4, 4, 7, 1,16, 1, 5, 0, 0, 0, 0, 0, 6, 1, 3, 1, 8, 4, 4, 4 },
	{ 0, 0, 0, 0, 1, 1, 1, 3, 0, 0, 0, 0, 0, 3, 1, 1, 1, 0, 0, 0, 0 },
	{ 4, 4, 4, 6, 1,15, 1, 8, 4, 4, 4, 4, 4, 7, 1,15, 1, 5, 4, 4, 4 },
	{ 5, 4, 4, 7, 1,16, 1, 1, 1, 1, 1, 1, 1, 1, 1,16, 1, 8, 4, 4, 6 },
	{ 3, 1, 1, 1, 1, 1, 1, 5, 6, 1,15, 1, 5, 6, 1, 1, 1, 1, 1, 1, 3 },
	{ 3, 1,15, 1,15, 1,13,12, 7, 1, 3, 1, 8,12, 14, 1,15, 1, 3, 1, 3 },
	{ 3, 2, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 2, 3 },
	{ 9, 4, 7, 1, 3, 1,13, 4, 4, 4,12, 4, 4, 4,14, 1, 3, 1, 8, 4,10 },
	{ 3, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3 },
	{ 3, 1,13, 4,12, 4, 4,14, 1, 5, 4, 6, 1,13, 4, 4,12, 4,14, 1, 3 },
	{ 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3 },
	{ 8, 4, 4, 4, 4, 4, 4, 4, 4, 7, 0, 8, 4, 4, 4, 4, 4, 4, 4, 4, 7 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{ //nested for loop to go through the level data and assign the corrisponding cells
			switch (setupData[row][col])
			{
			case 0:
				m_maze[row][col].setCell(empty);
				break;
			case 1:
				m_maze[row][col].setCell(pellet);
				break;
			case 2:
				m_maze[row][col].setCell(powerPellet);
				break;
			case 3:
				m_maze[row][col].setCell(verticalWall);
				break;
			case 4:
				m_maze[row][col].setCell(horizontalWall);
				break;
			case 5:
				m_maze[row][col].setCell(topLeftCorner);
				break;
			case 6:
				m_maze[row][col].setCell(topRightCorner);
				break;
			case 7:
				m_maze[row][col].setCell(bottomRightCorner);
				break;
			case 8:
				m_maze[row][col].setCell(bottomLeftCorner);
				break;
			case 9:
				m_maze[row][col].setCell(intersectionWallRight);
				break;
			case 10:
				m_maze[row][col].setCell(intersectionWallLeft);
				break;
			case 11:
				m_maze[row][col].setCell(intersectionWallDown);
				break;
			case 12:
				m_maze[row][col].setCell(intersectionWallUp);
				break;
			case 13:
				m_maze[row][col].setCell(wallEndLeft);
				break;
			case 14:
				m_maze[row][col].setCell(wallEndRight);
				break;
			case 15:
				m_maze[row][col].setCell(wallEndUp);
				break;
			case 16:
				m_maze[row][col].setCell(wallEndDown);
				break;
			default:
				break;
			}			
			m_maze[row][col].setPosition(sf::Vector2f{ static_cast<float>(col * 32 + 16), static_cast<float>(row * 32 + 16)});
			m_maze[row][col].update();
		}
	}
	m_player.setup();
	m_name = "";
	m_score = 0;
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		m_ghost[i].setupSprite(i);
	}
}

/// <summary>
/// main game update
/// </summary>
void GamePlay::update(sf::Time dt)
{
	if (m_gameState == inGameState::inGame)
	{ // all updates for ingame
		m_player.update(); //update pacman
		m_player.collision(m_maze); //check for collisions between walls
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			m_ghost[i].update(m_maze);
		}
		eat(); //get pacman to eat the pellets and increase his score
		collision(); //check for collision between the player and the ghost
		m_scoreText.setString(m_name + "'s Score: " + std::to_string(m_score));
		m_livesText.setString("Lives: " + std::to_string(m_player.getLives()));
		if (m_powerTimer >= 0)
			m_powerTimer--;
		else
		{
			m_poweredUp = false;
			m_player.powerup(m_poweredUp);
			for (int i = 0; i < MAX_ENEMIES; i++)
				m_ghost[i].powerup(m_poweredUp, i);
			m_multiplier = 1;
		}
	}
	else if (m_gameState == inGameState::endGame)
	{
		if (m_addScore)
		{
			updateScoreboard();
			m_addScore = false;
		}
	}
}


/// <summary>
/// function to draw the game
/// </summary>
void GamePlay::render(sf::RenderWindow & t_window)
{
	if (m_gameState == inGameState::takeName)
	{
		t_window.draw(m_enterNameText);
		t_window.draw(m_nameText);
	}
	else if (m_gameState == inGameState::inGame || m_gameState == inGameState::pauseGame)
	{
		for (int row = 0; row < MAX_ROWS; row++)
		{
			for (int col = 0; col < MAX_COLS; col++)
			{
				m_maze[row][col].draw(t_window);
			}
		}
		m_player.draw(t_window);
		t_window.draw(m_scoreText);
		t_window.draw(m_livesText);
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			m_ghost[i].draw(t_window);
		}
	}
	else if (m_gameState == inGameState::endGame)
	{
		t_window.draw(m_gameOverText);
		t_window.draw(m_highScore);
		t_window.draw(m_scoreBoard);
		t_window.draw(m_restartText);
	}
	if (m_gameState == inGameState::pauseGame)
	{
		t_window.draw(m_imageBlur);
		t_window.draw(m_pauseText);
	}
}

/// <summary>
/// function that allows the player to enter their name
/// </summary>
void GamePlay::enterName(sf::Event &t_event)
{
	if (t_event.type == sf::Event::KeyPressed)
	{
		if (m_name.length() < 20) //make sure it fits on the screen
		{
			if (sf::Keyboard::LShift == t_event.key.code)
			{
				m_caps = true;
			}
			if ((t_event.key.code >= 0 && t_event.key.code <= 25)) //check between a-z
			{
				char m_letter;
				if (m_caps)
					m_letter = (t_event.key.code + 65);
				else
					m_letter = (t_event.key.code + 97);
				m_name += m_letter;
			}
			else if (t_event.key.code == 57) //space
			{
				m_name += " ";
			}
		}
		if (t_event.key.code == 58) //enter
		{
			m_gameState = inGameState::inGame;
		}
		else if (t_event.key.code == 59) //backspace
		{
			unsigned length = m_name.length();
			if (length > 0)
				m_name.erase(length - 1, length);
		}
		m_nameText.setString(m_name);
	}
	if (sf::Event::KeyReleased == t_event.type)
	{
		if (sf::Keyboard::LShift == t_event.key.code)
		{
			m_caps = false;
		}
	}
}

/// <summary>
/// function that checks what is in the cell pacman is in and sets it to empty if its a pellet
/// </summary>
void GamePlay::eat()
{
	int row = m_player.getRow();
	int col = m_player.getCol();
	if (m_maze[row][col].getCell() == pellet)
	{
		m_score += 5;
		m_maze[row][col].setCell(empty);
		m_maze[row][col].update();
	}
	else if (m_maze[row][col].getCell() == powerPellet)
	{
		m_poweredUp = true;
		m_powerTimer = 180;
		m_maze[row][col].setCell(empty);
		m_maze[row][col].update();
	}
	m_player.powerup(m_poweredUp);
	for(int i =0; i < MAX_ENEMIES; i++)
		m_ghost[i].powerup(m_poweredUp, i);
}

/// <summary>
/// Function that checks the row and colum of each ghost against pacman and if any of the are equal pacman is dead
/// </summary>
void GamePlay::collision()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (!m_poweredUp)
		{
			if (m_ghost[i].getAlive())
			{
				if ((m_player.getRow() == m_ghost[i].getRow()) && (m_player.getCol() == m_ghost[i].getCol()))
				{
					m_player.reset();
					for (int j = 0; j < MAX_ENEMIES; j++) //for loop to reset all the ghost if one hits the player
					{
						m_ghost[j].reset(j);
					}
					if (m_player.getLives() <= 0)
					{
						m_gameState = inGameState::endGame;
					}
				}
			}
		}
		else
		{
			if (m_ghost[i].getAlive())
			{
				if ((m_player.getRow() == m_ghost[i].getRow()) && (m_player.getCol() == m_ghost[i].getCol()))
				{
					m_score += 50 * m_multiplier;
					std::cout << 50 * m_multiplier << std::endl;
					m_ghost[i].reset(i);
					m_multiplier *= 2;
				}
			}
		}
	}
}

/// <summary>
/// function to take the players name and score
/// and append them onto the scoreboard
/// and then take he whole scoreboard and put it into a text object
/// </summary>
void GamePlay::updateScoreboard()
{
	//input the scores on the leader board into an array
	const int MAX_PLAYERS = 10;

	int scores[MAX_PLAYERS];
	std::string names[MAX_PLAYERS];
	std::string line;
	std::string message;
	bool scoreAdded{ false };

	std::ifstream inputScores;
	inputScores.open("assets\\scoreboard\\score.txt");

	//input player scores from file----------------------------
	if (inputScores.is_open())
	{
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			std::getline(inputScores, line); //get a line and put it into the scores array 
			if (line.length() > 0)
			{
				std::stringstream line_ss(line);
				line_ss >> scores[i];
			}
			else
			{
				scores[i] = 0;
			}
		}
		inputScores.close();
	}
	//input player names from file----------------------
	inputScores.open("assets\\scoreboard\\scoreNames.txt");
	
	if (inputScores.is_open())
	{
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			std::getline(inputScores, names[i]); //get a line and put it into the names array 
		}
		inputScores.close();
	}

	//create the scoreboard - adding the new players score if it is higher than another
	for (int j = 0; j < MAX_PLAYERS; j++)
	{
		if (m_score >= scores[j] && !(scoreAdded))
		{
			for (int k = MAX_PLAYERS - 1; k >= j; k--)
			{
				names[k] = (k == j) ? m_name : names[k - 1];
				scores[k] = (k == j) ? m_score : scores[k - 1];
			}
			scoreAdded = true; //stop if overwriting multiple times
		}
		if (names[j].length() > 0 && std::to_string(scores[j]).length() > 0)
		{
			message += names[j] + ": " + std::to_string(scores[j]) + "\n";
		}

	}
	//save the new scoreboard to the file
	std::ofstream newNames;
	newNames.open("Assets\\scoreboard\\ScoreNames.txt");

	if (newNames.is_open())
	{
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			newNames << names[i] << "\n";
		}
		newNames.close();
	}

	std::ofstream newScores;
	newScores.open("assets\\scoreboard\\Score.txt");
	if (newScores.is_open())
	{
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			if (scores[i] > 0)
				newScores << std::to_string(scores[i]) << "\n";
			else
				newScores << 0 << "\n";
		}
		newScores.close();
	}
	m_scoreBoard.setString(message);
}

/// <summary>
/// function to reset the game
/// </summary>
/// <param name=""></param>
void GamePlay::restart(sf::Event &t_event)
{
	if (sf::Event::KeyPressed == t_event.type)
	{
		setupMaze();
		m_addScore = true;
		m_player.setup();
		m_gameState = inGameState::takeName;
		Game::m_currentState = GameState::TitleScreen;
	}
}