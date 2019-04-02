/// Author: Aaron O Neill
/// Login : C00241596
/// Date : 14-3-19
/// Estimated time Taken: 12 hours
/// Acutal time taken: 
/// 
//------------------------------------------
// Pacman game
// objective is to eat all the pellets in the map before the ghosts
// manage to catch you
//------------------------------------------

#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include "Game.h"
#include <stdlib.h>
#include <time.h>

/// <summary>
/// Main entry point
/// </summary>
int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	Game game;
	game.run();
	return 0;
}