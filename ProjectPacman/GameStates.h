//Aaron O Neill
#pragma once

// state used to decide what screen to show
enum class GameState
{
	SplashScreen,
	TitleScreen,
	GamePlayScreen,
	SettingScreen
};

//state the game is in
enum class inGameState
{
	takeName,
	inGame,
	pauseGame,
	endGame
};
