#pragma once
#include <Engine/OGLGame.h>
#include <string>
#include <vector>
#include <memory>

struct GameFont;
struct GameData;
class MainMenu;
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

	float frame_count = 0;
	float count_limit = 40;

	int  callback_id = -1;                             /**< Input Callback ID. The callback ID assigned by the game engine. */
	int state_callback_id = -1;
	bool exit = false;                                 /**< Exit boolean. If true the game loop will exit. */
	std::unique_ptr<ASGE::Sprite> sprite = nullptr;    /**< Sprite Object. The space invader sprite. */
	std::unique_ptr<MainMenu> menu = nullptr;
	std::unique_ptr<Player> player_one = nullptr;
	std::unique_ptr<GameData> game_data = nullptr;
	std::unique_ptr<AlienManager> alien_manager = nullptr;
};

