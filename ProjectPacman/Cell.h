//Author: Aaron O Neill
#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include <iostream>

class Cell
{
private:

	int m_cellType;
	sf::Texture m_cellTexture;
	sf::Sprite m_cell;

public:
	//get and set functions
	inline sf::Vector2f getPos() { return m_cell.getPosition(); }
	inline int getCell() { return m_cellType; }
	inline void setCell(int t_type) { m_cellType = t_type; }
	inline void setPosition(sf::Vector2f t_pos) { m_cell.setPosition(t_pos); } 
		
	//main setup
	void update(); //keep track of what type of cell is containes
	void draw(sf::RenderWindow &t_window); //draw each cell in the maze

	Cell();
	~Cell();
};

