#pragma once
#include <Engine/OGLGame.h>
#include <string>
#include <vector>
#include <memory>

struct GameFont;
class MainMenu;
class Player;

/**
*  Invaders Game. An OpenGL Game based on ASGE.
*/

class InvadersGame:
	public ASGE::OGLGame
{
	enum class GameState
	{
		SPLASH_SCREEN,
		MAIN_MENU,
		PLAYING,
		LEADERBOARD,
		PAUSED,
		GAME_OVER,
		EXIT
	};

public:
	InvadersGame();
	~InvadersGame();

	// Inherited via Game
	virtual bool run() override;
	bool shouldExit() const;
	void render();

	// Inherited via OGLGame
	virtual bool init();
	virtual void drawFrame();

	//Gamestate methods
	void initMainMenu();
	void updateMainMenu();
	void updatePlaying();
	void updatePauseScreen();
	void updateGameOver();

private:
	void processGameActions(); 
	void processStates(int key, int action);
	void input(int key, int action) const;

	GameState game_state = GameState::SPLASH_SCREEN;

	int  callback_id = -1;                             /**< Input Callback ID. The callback ID assigned by the game engine. */
	int state_callback_id = -1;
	bool exit = false;                                 /**< Exit boolean. If true the game loop will exit. */
	std::unique_ptr<ASGE::Sprite> sprite = nullptr;    /**< Sprite Object. The space invader sprite. */
	std::unique_ptr<MainMenu> menu = nullptr;
	std::unique_ptr<Player> player_one = nullptr;
};

