#include "Pacman.h"


//default constructor
Pacman::Pacman()
{
}


Pacman::~Pacman()
{
}

/// <summary>
/// function to setup all the variables of pacman
/// </summary>
void Pacman::setup()
{
	loadImage();
	m_xpos = 0;
	m_rectWidth = 32;
	m_speed = 5 * 0.9;
	m_pacman.setPosition(PACMAN_START);
	m_lives = 1;
	m_moveDown = false;
	m_moveUp = false;
	m_moveRight = false;
	m_moveLeft = false;
}

/// <summary>
/// function to reset pacman when he gets killed by the ghost
/// </summary>
void Pacman::reset()
{
	m_xpos = 0;
	m_rectWidth = 32;
	m_pacman.setPosition(PACMAN_START);
	m_lives--;
	m_moveDown = false;
	m_moveUp = false;
	m_moveRight = false;
	m_moveLeft = false;
	m_velocity = sf::Vector2f{};
}

/// <summary>
/// function to load the pacman sprite
/// </summary>
void Pacman::loadImage()
{
	m_pacmanTexture.loadFromFile("assets\\textures\\PacmanTexture.png");
	m_pacman.setTexture(m_pacmanTexture);
	m_pacman.setOrigin(16, 16);
	m_pacman.setTextureRect(sf::IntRect{ 0, 0, 32, 32 });
}

void Pacman::update()
{
	if (m_pacman.getPosition().x < 33)
	{
		m_pacman.setPosition(SCREEN_WIDTH - 33, m_pacman.getPosition().y);
	}
	else if (m_pacman.getPosition().x > SCREEN_WIDTH -33)
	{
		m_pacman.setPosition(33, m_pacman.getPosition().y);
	}
	m_munchingTime++;
	m_row = getRow();
	m_col = getCol();
	m_pacman.move(m_velocity);
	if (m_velocity.x != 0 || m_velocity.y != 0)
	{
		if ((m_munchingTime % 4) == 0)
			m_munch++;
		if (m_munch > 2)
			m_munch = 0;
		m_pacman.setTextureRect(sf::IntRect{ (32 * m_munch) + m_xpos, 0 , m_rectWidth , 32 });
	}
}

/// <summary>
/// function for when pacman eats a power pellet
/// </summary>
/// <param name="t_powerUp"></param>
void Pacman::powerup(bool t_powerUp)
{
	if (t_powerUp)
	{
		m_speed = 5 * 1.1;

	}
	else
	{
		m_speed = 5 * .9;
	}
}


void Pacman::processEvents(sf::Event &t_Event)
{
	if (t_Event.type == sf::Event::KeyPressed)
	{
		switch (t_Event.key.code)
		{ //switch to make sure there is no wall ahead of the player and the player isnt already moving in that direction
		case sf::Keyboard::W:
			if (m_moveUp && !(m_velocity.y < 0))
			{
				m_pacman.setPosition(m_col * 32 + 16, m_row * 32 + 16);
				m_velocity = { 0 , -m_speed };
				if (m_xpos != 0)
					m_pacman.setRotation(90);
				else
					m_pacman.setRotation(-90);
			}
			break;
		case sf::Keyboard::S:
		
			if (m_moveDown && !(m_velocity.y > 0))
			{
				m_pacman.setPosition(m_col * 32 + 16, m_row * 32 + 16);
				m_velocity = { 0, m_speed };
				if (m_xpos != 0)	
					m_pacman.setRotation(-90);
				else
					m_pacman.setRotation(90);
			}
			break;
		case sf::Keyboard::D:
			if (m_moveRight && !(m_velocity.x > 0))
			{
				m_pacman.setPosition(m_col * 32 + 16, m_row * 32 + 16);
				m_velocity = { m_speed,0 };
				m_pacman.setRotation(0);
				m_xpos = 0;
				m_rectWidth = 32;
			}
			break;
		case sf::Keyboard::A:
			if (m_moveLeft && !(m_velocity.x < 0)) 
			{
				m_pacman.setPosition(m_col * 32 + 16, m_row * 32 + 16);
				m_velocity = { -m_speed, 0 };
				m_pacman.setRotation(0);
				m_xpos = 32;
				m_rectWidth = -32;
			}
			break;
		}
	}
}

/// <summary>
/// function to check if the player hits any walls
/// </summary>
/// <param name="t_maze">map design</param>
void Pacman::collision(Cell t_maze[][MAX_COLS])
{

	if (m_velocity.x > 0) //moving right
	{
		if (t_maze[m_row][m_col + 1].getCell() > powerPellet) //meaning it contains a wall
		{
			m_velocity = { 0,0 };
			m_pacman.setPosition(m_col * 32 + 16, m_row * 32 + 16);
		}
	}
	else if (m_velocity.x < 0) //moving left
	{
		if (t_maze[m_row][m_col - 1].getCell() > powerPellet)
		{
			m_velocity = { 0,0 };
			m_pacman.setPosition(m_col * 32 + 16, m_row * 32 + 16);
		}
	}
	else if (m_velocity.y > 0) //moving down
	{
		if (t_maze[m_row + 1][m_col].getCell() > powerPellet)
		{
			m_velocity = { 0,0, };
			m_pacman.setPosition(m_col * 32 + 16, m_row * 32 + 16);
		}
	}
	else if (m_velocity.y < 0) //moving up
	{
		if (t_maze[m_row - 1][m_col].getCell() > powerPellet)
		{
			m_velocity = { 0, 0 };
			m_pacman.setPosition(m_col * 32 + 16, m_row * 32 + 16);
		}
	}
	checkDirection(t_maze);
}

/// <summary>
/// check if pacman can move in a given direction
/// </summary>
void Pacman::checkDirection(Cell t_maze[][MAX_COLS])
{

	//check to the left of pacman
	if (t_maze[m_row][m_col - 1].getCell() > powerPellet)
	{
		m_moveLeft = false;
	}
	else
	{
		m_moveLeft = true;
	}

	// check to the right of pacman
	if (t_maze[m_row][m_col + 1].getCell() > powerPellet)
	{
		m_moveRight = false;
	}
	else
	{
		m_moveRight = true;
	}

	//check above pacman
	if (t_maze[m_row - 1][m_col].getCell() > powerPellet)
	{
		m_moveUp = false;
	}
	else
	{
		m_moveUp = true;
	}

	//check below pacman
	if (t_maze[m_row + 1][m_col].getCell() > powerPellet)
		m_moveDown = false;
	else
		m_moveDown = true;
}

/// <summary>
/// draw pacman using the render window
/// </summary>
/// <param name="t_window"> main render window </param>
void Pacman::draw(sf::RenderWindow &t_window)
{
	t_window.draw(m_pacman); 
}

//-------------------------------------------------------------------
//SPLASH SCREEN FUNCTIONS

/// <summary>
/// special movement function only used on the splash screen
/// </summary>
void Pacman::moveSplash()
{
	m_munchingTime++;
	if ((m_munchingTime % 4) == 0)
		m_munch++;
	if (m_munch > 2)
		m_munch = 0;
	m_pacman.setTextureRect(sf::IntRect{ (32 * m_munch) + m_xpos, 0 , m_rectWidth , 32 });
}

/// <summary>
/// set pacman up in a position that is preferable for the splash screen
/// </summary>
void Pacman::setupSplash()
{
	m_pacman.setPosition(-32, 500);
}
