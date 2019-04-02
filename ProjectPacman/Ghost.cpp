#include "Ghost.h"



Ghost::Ghost()
{
}

Ghost::~Ghost()
{
}

void Ghost::setupSprite(int t_ghostNum)
{
	if (t_ghostNum == 0)
	{
		m_ghostTexture[t_ghostNum].loadFromFile("assets\\textures\\blueGhost32.png");
		m_aliveTimer = t_ghostNum * 90;
	}
	else if (t_ghostNum == 1)
	{
		m_ghostTexture[t_ghostNum].loadFromFile("assets\\textures\\greenGhost32.png");
		m_aliveTimer = t_ghostNum * 90;
	}
	else if (t_ghostNum == 2)
	{
		m_ghostTexture[t_ghostNum].loadFromFile("assets\\textures\\purpleGhost32.png");
		m_aliveTimer = t_ghostNum * 90;
	}
	else if (t_ghostNum == 3)
	{
		m_ghostTexture[t_ghostNum].loadFromFile("assets\\textures\\yellowGhost32.png");
		m_aliveTimer = t_ghostNum * 90;
	}
	m_scaredTexture.loadFromFile("assets\\textures\\ghosts32.png");
	m_direction = Directions::North; //set the player to move north by default

	m_ghost.setTexture(m_ghostTexture[t_ghostNum]); //give each ghost a texture
	m_ghost.setTextureRect(sf::IntRect{ 0,0,32,32 }); //set their texture rect
	m_ghost.setPosition((32 * 8) + (40 * t_ghostNum), (32 * 12)); //set their position to the box in the middle
}

/// <summary>
/// function called every frame for the ghosts to update
/// </summary>
/// <param name="t_maze">Level layout</param>
void Ghost::update(Cell t_maze[][MAX_COLS])
{
	//get the current position of the ghost
	m_row = getRow();
	m_col = getCol();

	move(t_maze); //move the player
	//decriment the ghosts freeze timer
	if (m_waitToMove > 0)
	{
		m_waitToMove--;
	}
	if (m_aliveTimer > 0)
	{
		m_aliveTimer--;
	}
	else if (m_aliveTimer <= 0)
	{
		m_alive = true;
	}
}

/// <summary>
/// function that moves the ghosts around the map until they hit a wall then they move in a random direction
/// </summary>
/// <param name="t_maze"> level layout </param>
void Ghost::move(Cell t_maze[][MAX_COLS])
{
	checkDirection(t_maze);
	if (m_alive && (m_waitToMove == 0)) //check to see if the ghost is alive before moving it
	{
		if (m_direction == Directions::North) //check what way the ghost is moving and move him by one cell in said direction
		{// decriment the row by 1
			if (m_moveNorth)
			{ //check to see if they player can move in said direction
				m_ghost.setPosition(m_col * 32, (m_row - 1) * 32); //set the player to one row above his current position
			}
			else //if the ghost cant move up make it move in a random direction
			{
				int direction = rand() % 3; //random number 0 - 2
				switch (direction)
				{
				case 0: //move right if you can
					if (m_moveEast)
					{
						m_direction = Directions::East;
						break;
					}
				case 1:
					if (m_moveSouth)
					{
						m_direction = Directions::South;
						break;
					}
				case 2:
					if (m_moveWest)
					{
						m_direction = Directions::West;
						break;
					}
				}
			}
		}
		else if (m_direction == Directions::South)
		{// incriment the row by 1
			if (m_moveSouth)
			{
				m_ghost.setPosition(m_col * 32, (m_row + 1) * 32);
			}
			else //if the ghost cant move south move random
			{
				int direction = rand() % 3; //random number 0 - 2
				switch (direction)
				{
				case 0: //move right if you can
					if (m_moveEast)
					{
						m_direction = Directions::East;
						break;
					}
				case 1:
					if ( m_moveNorth)
					{
						m_direction = Directions::North;
						break;
					}
				case 2:
					if (m_moveWest)
					{
						m_direction = Directions::West;
						break;
					}
				}
			}
		}
		else if (m_direction == Directions::East) //right
		{// decriment the col by 1
			if (m_moveEast)
			{
				m_ghost.setPosition((m_col + 1) * 32, m_row * 32);
			}
			else //if the ghost cant move East move random
			{
				int direction = rand() % 3; //random number 0 - 2
				switch (direction)
				{
				case 0: //move right if you can
					if (m_moveNorth)
					{
						m_direction = Directions::North;
						break;
					}
				case 1:
					if (m_moveSouth)
					{
						m_direction = Directions::South;
						break;
					}
				case 2:
					if (m_moveWest)
					{
						m_direction = Directions::West;
						break;
					}
				}
			}
		}
		else if (m_direction == Directions::West) //left
		{// incriment the col by 1
			if (m_moveWest)
			{
				m_ghost.setPosition((m_col - 1) * 32, m_row * 32);
			}
			else //if the ghost cant move West move random
			{
				int direction = rand() % 3; //random number 0 - 2
				switch (direction)
				{
				case 0: //move right if you can
					if (m_moveNorth)
					{
						m_direction = Directions::North;
						break;
					}
				case 1:
					if (m_moveSouth)
					{
						m_direction = Directions::South;
						break;
					}
				case 2:
					if (m_moveEast)
					{
						m_direction = Directions::East;
						break;
					}
				}
			}
		}

		m_waitToMove = 8; //stop the ghost from moving for 10 frames
		if (m_directionTimer > 0)
		{
			m_directionTimer--;
		}
	}

}

/// <summary>
/// function that checks the cell that the ghost is about to move into
/// and if its a wall it needs to stop the ghost
/// it also allows the ghost to change direction randomly
/// </summary>
void Ghost::checkDirection(Cell t_maze[][MAX_COLS])
{
	m_moveSouth = (t_maze[m_row + 1][m_col].getCell() > 2) ? false : true; //check below
	m_moveNorth = (t_maze[m_row - 1][m_col].getCell() > 2) ? false : true; //check above
	m_moveEast = (t_maze[m_row][m_col + 1].getCell() > 2) ? false : true; //check right
	m_moveWest = (t_maze[m_row][m_col - 1].getCell() > 2) ? false : true; //check left

	//broken movement
	if (m_direction == Directions::North) //ghost is moving north
	{
		if (m_moveEast && m_directionTimer <= 0)
		{
			m_direction = (rand() % 4 == 0) ? Directions::East : Directions::North;
			m_directionTimer = 5;
		}
		if (m_moveWest && m_directionTimer <= 0)
		{
			m_direction = (rand() % 4 == 0) ? Directions::West : Directions::North;
			m_directionTimer = 5;
		}
	}
	else if (m_direction == Directions::South) //ghost is moving South
	{
		if (m_moveEast && m_directionTimer <= 0)
		{
			m_direction = (rand() % 4 == 0) ? Directions::East : Directions::South;
			m_directionTimer = 5;
		}
		if (m_moveWest && m_directionTimer <= 0)
		{
			m_direction = (rand() % 4 == 0) ? Directions::West : Directions::South;
			m_directionTimer = 5;
		}
	}
	else if (m_direction == Directions::East) //ghost is moving East
	{
		if (m_moveNorth && m_directionTimer <= 0)
		{
			m_direction = (rand() % 4 == 0) ? Directions::North : Directions::East;
			m_directionTimer = 5;
		}
		if (m_moveSouth && m_directionTimer <= 0)
		{
			m_direction = (rand() % 4 == 0) ? Directions::South : Directions::East;
			m_directionTimer = 5;
		}
	}
	else if (m_direction == Directions::West) //ghost is moving West
	{
		if (m_moveNorth && m_directionTimer <= 0)
		{
			m_direction = (rand() % 4 == 0) ? Directions::North : Directions::West;
			m_directionTimer = 5;
		}
		if (m_moveSouth && m_directionTimer <= 0)
		{
			m_direction = (rand() % 4 == 0) ? Directions::South : Directions::West;
			m_directionTimer = 5;
		}
	}
}

/// <summary>
/// draw the ghost using the render window
/// </summary>
/// <param name="t_window">main render window</param>
void Ghost::draw(sf::RenderWindow & t_window)
{
	t_window.draw(m_ghost);
}

/// <summary>
/// function that moves the ghosts back to their start position if the player is hit
/// </summary>
void Ghost::reset(int t_ghostNum)
{
	m_ghost.setPosition((32 * 8) + (40 * t_ghostNum), (32 * 12)); //set their position to the box in the middle
	m_alive = (t_ghostNum == 0) ? true : false;
	m_aliveTimer = t_ghostNum * 90;
	m_scared = false;
}

void Ghost::powerup(bool t_powerUp, int t_ghostNum)
{
	if (t_powerUp)
	{
		m_ghost.setTexture(m_scaredTexture);
	}
	else
	{
		switch (t_ghostNum)
		{
		case 0:
			m_ghost.setTexture(m_ghostTexture[t_ghostNum]);
			break;
		case 1:
			m_ghost.setTexture(m_ghostTexture[t_ghostNum]);
			break;
		case 2:
			m_ghost.setTexture(m_ghostTexture[t_ghostNum]);
			break;
		case 3:
			m_ghost.setTexture(m_ghostTexture[t_ghostNum]);
			break;
		}
	}
}
