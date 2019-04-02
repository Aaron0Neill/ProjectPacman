#include "Cell.h"

/// <summary>
/// Default constructor
/// </summary>
Cell::Cell()
{
	m_cell.setOrigin(16, 16);
}


Cell::~Cell()
{
}


void Cell::update()
{
	//loading different textures
	switch (m_cellType)
	{
	case empty:
		m_cellTexture.loadFromFile("assets\\textures\\emptyCell.png");
		break;
	case pellet:
		m_cellTexture.loadFromFile("assets\\textures\\smallpill.png");
		break;
	case powerPellet:
		m_cellTexture.loadFromFile("assets\\textures\\pelletTexture.png");
		break;
	case verticalWall:
		m_cellTexture.loadFromFile("assets\\textures\\VerticalWall.png");
		break;
	case horizontalWall:
		m_cellTexture.loadFromFile("assets\\textures\\HorizontalWall.png");
		break;
	case topLeftCorner:
		m_cellTexture.loadFromFile("assets\\textures\\TopLeftCorner.png");
		break;
	case topRightCorner:
		m_cellTexture.loadFromFile("assets\\textures\\TopRightCorner.png");
		break;
	case bottomRightCorner:
		m_cellTexture.loadFromFile("assets\\textures\\BottomRightCorner.png");
		break;
	case bottomLeftCorner:
		m_cellTexture.loadFromFile("assets\\textures\\BottomLeftCorner.png");
		break;
	case intersectionWallRight:
		m_cellTexture.loadFromFile("assets\\textures\\intersectionWallRight.png");
		break;
	case intersectionWallLeft:
		m_cellTexture.loadFromFile("assets\\textures\\intersectionWallLeft.png");
		break;
	case intersectionWallDown:
		m_cellTexture.loadFromFile("assets\\textures\\intersectionWallDown.png");
		break;
	case intersectionWallUp:
		m_cellTexture.loadFromFile("assets\\textures\\intersectionWallUp.png");
		break;
	case wallEndLeft:
		m_cellTexture.loadFromFile("assets\\textures\\wallEndLeft.png");
		break;
	case wallEndRight:
		m_cellTexture.loadFromFile("assets\\textures\\wallEndRight.png");
		break;
	case wallEndUp:
		m_cellTexture.loadFromFile("assets\\textures\\wallEndUp.png");
		break;
	case wallEndDown:
		m_cellTexture.loadFromFile("assets\\textures\\wallEndDown.png");
		break;
	}
	//assign correct texture
	m_cell.setTexture(m_cellTexture);
}

/// <summary>
/// draw the cell using the render window
/// </summary>
/// <param name="t_window"> main render window </param>
void Cell::draw(sf::RenderWindow & t_window)
{
	t_window.draw(m_cell);
}