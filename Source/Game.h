#pragma once
#include <Engine/OGLGame.h>
#include <string>
#include <vector>
#include <memory>

struct GameFont;
struct GameData;
class MainMenu;
class PauseMenu;
class Player;
class StandardAlien;
class AlienManager;

/**
*  Invaders Game. An OpenGL Game based on ASGE.
*/

class InvadersGame:
	public ASGE::OGLGame
{

public:
	InvadersGame();
	~InvadersGame();

	// Inherited via Game
	virtual bool run() override;
	bool shouldExit() const;

	// Inherited via OGLGame
	virtual bool init();
	virtual void drawFrame() = 0;	//Removed the definition for this function since was not used in game

	//Gamestate methods
	void updateMainMenu();
	void updatePlaying();
	void updatePauseScreen();
	void updateGameOver();

	//Check collisions
	void checkCollisions();

private:
	void processGameActions(); 
	void processStates(int key, int action);
	void input(int key, int action) const;

	int  callback_id = -1;                             /**< Input Callback ID. The callback ID assigned by the game engine. */
	int state_callback_id = -1;
	bool exit = false;                                 /**< Exit boolean. If true the game loop will exit. */
	std::unique_ptr<MainMenu> menu = nullptr;
	std::unique_ptr<PauseMenu> pause = nullptr;
	std::unique_ptr<Player> player_one = nullptr;
	std::unique_ptr<GameData> game_data = nullptr;
	std::unique_ptr<AlienManager> alien_manager = nullptr;
	std::string score_string;	//displays score in-game
	std::string lives_string;	//displays lives in-game
};

