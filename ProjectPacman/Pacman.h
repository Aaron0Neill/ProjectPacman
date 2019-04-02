//Author: Aaron O Neill
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "Cell.h"


class Pacman
{
private:

	sf::Texture m_pacmanTexture; //main body
	sf::Sprite m_pacman;
	sf::Vector2f m_velocity;

	float m_speed;
	int m_row;
	int m_col;
	int m_munchingTime{ 0 };
	int m_munch{ 0 };
	int m_xpos;
	int m_rectWidth;
	int m_lives;

	//bools to check if pacman can move in a certain direction
	bool m_moveUp; 
	bool m_moveDown;
	bool m_moveLeft;
	bool m_moveRight;

	void loadImage();

public:
	Pacman();
	~Pacman();

	inline int getRow() { return m_pacman.getPosition().y / 32; }
	inline int getCol() { return m_pacman.getPosition().x / 32; }
	inline int getLives() { return m_lives; }

	//main game functions
	void setup(); //main setup for pacman character
	void reset(); //resets pacman to his original position
	void update(); //updates all the information about the player
	void powerup(bool );
	void processEvents(sf::Event &t_Event); //take user input and move pacman accoridingly
	void collision(Cell t_maze[][MAX_COLS]); //stop pacman when he hits a wall
	void checkDirection(Cell t_maze[][MAX_COLS]);  //use the maze data to determine which direction pacman can move
	void draw(sf::RenderWindow & t_window); //draw pacman
	//seperate functions
	void moveSplash();
	void setupSplash();
};

