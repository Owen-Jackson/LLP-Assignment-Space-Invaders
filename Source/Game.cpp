#include "Game.h"
#include "Actions.h"
#include "Constants.h"
#include "GameFont.h"
#include "Menu.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Player.h"
#include "GameActor.h"
#include "StandardAlien.h"
#include "BonusAlien.h"
#include "GameData.h"
#include "AlienManager.h"
#include "LaserManager.h"

#include <time.h>

#include <Engine/Input.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>

/**
*   @brief   Default Constructor.
*/
InvadersGame::InvadersGame()
{
	srand(time(NULL));
}


/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
InvadersGame::~InvadersGame()
{
	this->inputs->unregisterCallback(callback_id);
	this->inputs->unregisterCallback(state_callback_id);
}


/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
			 run the game are loaded. The input callback should also
			 be set in the initialise function. 
*   @return  True if the game initialised correctly.
*/
bool InvadersGame::init()
{
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	if (!initAPI())
	{
		return false;
	}

	renderer->setWindowTitle("Invaders - Exercise 1");
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	toggleFPS();

	// input callback function
	state_callback_id = this->inputs->addCallbackFnc(&InvadersGame::processStates, this);
	callback_id = this->inputs->addCallbackFnc(&InvadersGame::input, this);
	
	// load fonts we need
	GameFont::fonts[0] = new GameFont(
		renderer->loadFont("..\\..\\Resources\\Fonts\\Comic.ttf", 42), "default", 42);
	
	if (GameFont::fonts[0]->id == -1)
	{
		return false;
	}

	//Initialise game data
	game_data = std::make_unique<GameData>();
	game_data->renderer = renderer;

	//Initialise managers
	alien_manager = std::make_unique<AlienManager>(game_data.get());

	//Create menus
	menu = std::make_unique<MainMenu>(game_data.get());
	pause = std::make_unique<PauseMenu>(game_data.get());

	//Create player
	player_one = std::make_unique<Player>(game_data.get());
	player_one->loadSprite(renderer);
	player_one->getSprite()->scale = 0.5;
	player_one->getSprite()->position[0] = 640;
	player_one->getSprite()->position[1] = 600;
	if (!player_one->getSprite()->loadTexture("..\\..\\Resources\\Textures\\Player.png"))
	{
		renderer->renderText("The sprite didn't load", 400, 400, ASGE::COLOURS::WHITE);
	}

	return true;
}

/**
*   @brief   The main game loop. 
*   @details The main loop should be responsible for updating the game
			 and rendering the current scene. Runs until the shouldExit
			 signal is received.
*   @return  True if the game ran correctly. 
*/
bool InvadersGame::run()
{
	while (!shouldExit())
	{
		if (game_data->game_state == GameData::GameState::MAIN_MENU)
		{
			updateMainMenu();
			processGameActions();
		}
		else if (game_data->game_state == GameData::GameState::PLAYING)
		{
			updatePlaying();
			processGameActions();
		}
		else if (game_data->game_state == GameData::GameState::PAUSED)
		{
			updatePauseScreen();
			processGameActions();
		}
		else if (game_data->game_state == GameData::GameState::GAME_OVER)
		{
			updateGameOver();
			processGameActions();
		}
	}

	return true;
}

/**
*   @brief   Should the game exit?
*   @details Has the renderer terminated or the game requesting to exit?
*   @return  True if the game should exit
*/
bool InvadersGame::shouldExit() const
{
	return (renderer->exit() || this->exit);
}

//Displays main menu options
void InvadersGame::updateMainMenu()
{
	beginFrame();
	renderer->renderText("New Game", 475, 325, ASGE::COLOURS::FORESTGREEN);
	renderer->renderText("High Scores - Coming Soon!", 475, 375, ASGE::COLOURS::FORESTGREEN);
	renderer->renderText("Exit", 475, 425, ASGE::COLOURS::FORESTGREEN);	
	menu->getSelectionSprite()->render(renderer);
	endFrame();
}

void InvadersGame::updatePlaying()
{
	beginFrame();
	
	game_data->frame_count++;
	alien_manager->tick();	//tick all alive aliens (based on frame_count >= max_count)
	if (game_data->frame_count >= game_data->max_count)
	{
		game_data->frame_count = 0;	//reset count for next alien tick
	}
	alien_manager->render();	//render all alive aliens
	player_one->tick();	//move the player one tick
	checkCollisions();	//check any possible collisions in the frame

	score_string = "SCORE\n" + std::to_string(game_data->player_score);
	renderer->renderText(score_string.c_str(), 100, 50, ASGE::COLOURS::YELLOW);

	lives_string = "LIVES: " + std::to_string(game_data->player_lives);
	renderer->renderText(lives_string.c_str(), WINDOW_WIDTH - 200, 50, ASGE::COLOURS::GREENYELLOW);

	if (game_data->player_lives == 0)
	{
		game_data->game_state = GameData::GameState::GAME_OVER;
	}
	if (game_data->number_of_alive_aliens == 0)
	{
		alien_manager->reset();
	}
	endFrame();
}

//Displays pause menu options
void InvadersGame::updatePauseScreen()
{
	beginFrame();
	renderer->renderText("PAUSED", 475, 200, ASGE::COLOURS::FORESTGREEN);
	renderer->renderText("Resume", 475, 325, ASGE::COLOURS::FORESTGREEN);
	renderer->renderText("Main Menu", 475, 375, ASGE::COLOURS::FORESTGREEN);
	renderer->renderText("Exit", 475, 425, ASGE::COLOURS::FORESTGREEN);
	pause->getSelectionSprite()->render(renderer);
	endFrame();
}

//Shows final score when no lives left, takes player back to main menu afterwards
void InvadersGame::updateGameOver()
{
	beginFrame();
	renderer->renderText("GAME OVER", 475, 200, ASGE::COLOURS::RED);
	renderer->renderText(score_string.c_str(), 475, 325, ASGE::COLOURS::YELLOW);
	renderer->renderText("Press any key to return to main menu", 200, 475, ASGE::COLOURS::GREEN);

	endFrame();
}

/**
*   @brief   Processes any key inputs and translates them to a GameAction
*   @details This function is added as a callback to handle the game's 
			 input. Key presseses are translated in to GameActions which 
			 are then processed by the main game loop.
*   @param   key is the key the action relates to
*   @param   action whether the key was released or pressed
*   @return  void
*/
void InvadersGame::input(int key, int action) const
{
	if (action == ASGE::KEYS::KEY_PRESSED)
	{
		if (key == ASGE::KEYS::KEY_ESCAPE)
		{
			game_action = GameAction::PAUSE;
		}
		if (key == ASGE::KEYS::KEY_W || key == ASGE::KEYS::KEY_UP)
		{
			game_action = GameAction::UP;
		}
		if (key == ASGE::KEYS::KEY_A || key == ASGE::KEYS::KEY_LEFT)
		{
			game_action = GameAction::LEFT;
		}
		if (key == ASGE::KEYS::KEY_S || key == ASGE::KEYS::KEY_DOWN)
		{
			game_action = GameAction::DOWN;
		}
		if (key == ASGE::KEYS::KEY_D || key == ASGE::KEYS::KEY_RIGHT)
		{
			game_action = GameAction::RIGHT;
		}
		if (key == ASGE::KEYS::KEY_ENTER)
		{
			game_action = GameAction::SELECT;
		}
		if (key == ASGE::KEYS::KEY_SPACE)
		{
			game_action = GameAction::SHOOT;
		}
	}
	if (action == ASGE::KEYS::KEY_RELEASED)
	{
		if (key == ASGE::KEYS::KEY_A || key == ASGE::KEYS::KEY_LEFT)
		{
			if (player_one->getPreviousMoveState() == Player::Movement::LEFT)
			{
				player_one->setMoveState(Player::Movement::NONE);
			}
		}
		if (key == ASGE::KEYS::KEY_D || key == ASGE::KEYS::KEY_RIGHT)
		{
			if (player_one->getPreviousMoveState() == Player::Movement::RIGHT)
			{
				player_one->setMoveState(Player::Movement::NONE);
			}
		}
	}
	if (action == ASGE::KEYS::KEY_REPEATED)
	{
		if (key == ASGE::KEYS::KEY_SPACE)
		{
			game_action = GameAction::SHOOT;
		}
	}
}

/**
*   @brief   Processes the next game action
*   @details Uses the game action that was a direct result of 
*            user input. It allows input to processed in a different
             thread and the game actions performed in the main thread. 
*   @return  void
*/
void InvadersGame::processGameActions()
{
	switch (game_action)
	{
	case(GameAction::DOWN) :
	{
		if (game_data->game_state == GameData::GameState::MAIN_MENU)
		{
			menu->processMenuStates(game_action);
		}
		else if (game_data->game_state == GameData::GameState::PAUSED)
		{
			pause->processMenuStates(game_action);
		}
		break;
	}
	case(GameAction::UP) :
	{
		if (game_data->game_state == GameData::GameState::MAIN_MENU)
		{
			menu->processMenuStates(game_action);
		}
		else if (game_data->game_state == GameData::GameState::PAUSED)
		{
			pause->processMenuStates(game_action);
		}
		break;
	}
	case(GameAction::LEFT) :
	{
		player_one->setMoveState(Player::Movement::LEFT);
		break;
	}
	case(GameAction::RIGHT) :
	{
		player_one->setMoveState(Player::Movement::RIGHT);
		break;
	}
	case (GameAction::SHOOT) :
	{
		player_one->attack();
		break;
	}
	}
	this->inputs->addCallbackFnc(&InvadersGame::processStates, this);
	game_action = GameAction::NONE;
}

void InvadersGame::processStates(int key, int action)
{
	switch (game_data->game_state)
	{
	case GameData::GameState::MAIN_MENU:
		if (game_action == GameAction::PAUSE)
		{
			this->exit = true;
		}
		if (game_action == GameAction::SELECT)
		{
			switch (menu->getMenuState())
			{
			case MainMenu::MenuState::PLAY:
				game_data->game_state = GameData::GameState::PLAYING;
				break;
			case MainMenu::MenuState::HIGHSCORES:
				//NOT IMPLEMENTED
				//game_data->game_state = GameData::GameState::LEADERBOARD;
				break;
			case MainMenu::MenuState::QUIT:
				this->exit = true;
				break;
			default:
				renderer->renderText("NOT WORKING", 50, 50, ASGE::COLOURS::WHITE);
			}
		}
	case GameData::GameState::PLAYING:
		if (game_action == GameAction::PAUSE)
		{
			game_data->game_state = GameData::GameState::PAUSED;
		}
		break;
	case GameData::GameState::PAUSED:
		if (game_action == GameAction::PAUSE)
		{
			game_data->game_state = GameData::GameState::PLAYING;
		}
		if (game_action == GameAction::SELECT)
		{
			switch (pause->getMenuState())
			{
			case PauseMenu::MenuState::RESUME:
				game_data->game_state = GameData::GameState::PLAYING;
				break;
			case PauseMenu::MenuState::MAIN_MENU:
				game_action = GameAction::NONE;
				game_data->game_state = GameData::GameState::MAIN_MENU;
				break;
			case PauseMenu::MenuState::QUIT:
				this->exit = true;
				break;
			default:
				renderer->renderText("NOT WORKING", 50, 50, ASGE::COLOURS::WHITE);
			}
		}
		break;
	case GameData::GameState::GAME_OVER:
		if (action == ASGE::KEYS::KEY_PRESSED)
		{
			//reset game values
			game_action = GameAction::NONE;
			alien_manager->reset();
			game_data->player_lives = 3;
			player_one->setIsAlive(true);
			player_one->getSprite()->position[0] = 640;
			player_one->setMoveState(GameActor::Movement::NONE);	//stop the player from moving if the game is restarted
			game_data->player_score = 0;
			game_data->game_state = GameData::GameState::MAIN_MENU;	//send player back to main menu
		}
	}
}

void InvadersGame::checkCollisions()
{
	alien_manager->checkObjectCollisions(player_one->getLaser(), player_one->getLaser()->getActorType());
	alien_manager->checkObjectCollisions(player_one.get(), player_one->getActorType());
	alien_manager->checkLaserCollisions(player_one.get(), player_one->getActorType());
}