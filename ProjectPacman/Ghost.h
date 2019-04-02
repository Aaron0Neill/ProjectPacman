//Author: Aaron O  neill

#ifndef GHOST_H
#define GHOST_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "Cell.h"

class Ghost
{
private:

	sf::Texture m_ghostTexture[MAX_ENEMIES]; //main texture
	sf::Texture m_scaredTexture;
	sf::Sprite m_ghost; //main body 
	Directions m_direction; //direction the ghost is moving

	//current position of the ghost
	int m_row;
	int m_col;

	int m_aliveTimer;
	int m_waitToMove{ 0 }; //for testing
	int m_directionTimer{ 0 };
	//bools to check if there is a wall in any direction
	bool m_moveEast;
	bool m_moveWest;
	bool m_moveSouth;
	bool m_moveNorth;

	bool m_alive{ false }; //to check if they are alive or not
	bool m_scared; //to check if pacman has eaten a power pellet or not

public:
	Ghost();
	~Ghost();

	inline int getRow() { return m_ghost.getPosition().y / 32; }
	inline int getCol() { return m_ghost.getPosition().x / 32; }
	inline bool getAlive() { return m_alive; }

	void setupSprite(int t_ghostNum); //function to load the sprites
	void update(Cell t_maze[][MAX_COLS]); //main update for the ghost
	void move(Cell t_maze[][MAX_COLS]); //function to move the ghosts
	void checkDirection(Cell t_maze[][MAX_COLS]); //function to check if the ghost can move
	void draw(sf::RenderWindow &t_window); //used to draw the ghosts
	void reset(int t_ghostNum); //reset the ghosts when pacman is eaten
	void powerup(bool, int); //check if pacman ate a powerPellet
};

#endif // !GHOST_H