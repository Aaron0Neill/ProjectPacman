#pragma once
//dimensions of the screen
static const unsigned SCREEN_WIDTH{ 672 };
static const unsigned SCREEN_HEIGHT{ 800 };

static const int MAX_ROWS{ 25 }; //max amount of rows in the 2D array
static const int MAX_COLS{ 21 }; //max amount of colums in the 2D array

static const int MAX_ENEMIES{ 4 };

static const sf::Vector2f PACMAN_START{ 560,688	};
static const sf::Vector2f GHOST_START[MAX_ENEMIES] =
{	{ 300,500 },
	{ 200,400 },
	{ 100,300 },
	{ 400,600 }, };

static const int BUTTON_LEFT{ 233 };
static const int BUTTON_RIGHT{ 442 };
static const int PLAY_BUTTON_TOP{ 375 };
static const int PLAY_BUTTON_BOTTOM{ 425 };

static const int SETTINGS_BUTTON_TOP{ 475 };
static const int SETTINGS_BUTTON_BOTTOM{ 525 };

static const int EXIT_BUTTON_TOP{ 575 };
static const int EXIT_BUTTON_BOTTOM{ 625 };

//enum for what is in each cell
enum cellContains
{
	empty,
	pellet,
	powerPellet,
	verticalWall,
	horizontalWall,
	topLeftCorner,
	topRightCorner,
	bottomRightCorner,
	bottomLeftCorner,
	intersectionWallRight,
	intersectionWallLeft,
	intersectionWallDown,
	intersectionWallUp,
	wallEndLeft,
	wallEndRight,
	wallEndUp,
	wallEndDown,
};

enum class Directions
{
	North,
	South,
	East,
	West
};