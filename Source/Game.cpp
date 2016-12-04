#include "Game.h"
#include "Actions.h"
#include "Constants.h"
#include "GameFont.h"
#include "MainMenu.h"
#include "Player.h"
#include "GameActor.h"
#include "StandardAlien.h"
#include "BonusAlien.h"
#include "GameData.h"
#include "AlienManager.h"
#include "LaserManager.h"

#include <vector>
#include <memory>

#include <Engine/Input.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>

/**
*   @brief   Default Constructor.
*/
InvadersGame::InvadersGame()
{

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
	laser_manager = std::make_unique<LaserManager>(game_data.get());

	// load space invader sprite
	sprite = renderer->createSprite();
	sprite->position[0] = 700;
	sprite->position[1] = 250;
	
	if (!sprite->loadTexture("..\\..\\Resources\\Textures\\Invader.jpg"))
	{
		return false;
	}

	//Create main menu
	menu = std::make_unique<MainMenu>();

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

	initMainMenu();

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
		}
		else if (game_data->game_state == GameData::GameState::GAME_OVER)
		{
			updateGameOver();
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

/**
*   @brief   Renders the scene
*   @details Prepares the renderer subsystem before drawing the 
			 current frame. Once the current frame is has finished
			 the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void InvadersGame::render()
{
	beginFrame();
	drawFrame();
	endFrame();
}

/**
*   @brief   Renderers the contents for this frame 
*   @details All game objects that need rendering should be done
			 in this function, as it ensures they are completed
			 before the buffers are swapped.
*   @return  void
*/
void InvadersGame::drawFrame()
{
	renderer->setFont(GameFont::fonts[0]->id);
	renderer->renderText("Space Invaders\nSTART", 375, 325, 1.0, ASGE::COLOURS::DARKORANGE);
	sprite->render(renderer);
}

void InvadersGame::initMainMenu()
{
	menu->selection_arrow = renderer->createSprite();
	menu->selection_arrow->position[0] = 330;
	menu->selection_arrow->position[1] = 300;
	menu->selection_arrow->scale = 0.3;
	if (!menu->selection_arrow->loadTexture("..\\..\\Resources\\Textures\\Large Alien 1.png"))
	{
		renderer->renderText("The sprite didn't load", 400, 400, ASGE::COLOURS::WHITE);
	}
	menu->selection_arrow->render(renderer);
}

void InvadersGame::updateMainMenu()
{
	beginFrame();
	renderer->renderText("New Game", 375, 325, ASGE::COLOURS::FORESTGREEN);
	renderer->renderText("High Scores", 375, 375, ASGE::COLOURS::FORESTGREEN);
	renderer->renderText("Exit", 375, 425, ASGE::COLOURS::FORESTGREEN);	
	menu->selection_arrow->render(renderer);
	endFrame();
}

void InvadersGame::updatePlaying()
{
	beginFrame();
	player_one->move();
	player_one->getSprite()->render(renderer);
	
	game_data->frame_count++;
	if (game_data->frame_count == game_data->max_count)
	{
		alien_manager->tick();
		game_data->frame_count = 0;
	}
	alien_manager->render();
	laser_manager->tick();
	endFrame();
}

void InvadersGame::updatePauseScreen()
{
	;
}

void InvadersGame::updateGameOver()
{
	;
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
			game_action = GameAction::EXIT;
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
	case(GameAction::EXIT) :
	{
		this->exit = true;
		break;
	}
	case(GameAction::DOWN) :
	{
		menu->processMenuStates(game_action);
		break;
	}
	case(GameAction::UP) :
	{
		menu->processMenuStates(game_action);
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
		laser_manager->addLaser(std::make_unique<Laser>(true, player_one->getSprite()->position[0] + (player_one->getSprite()->size[0] / 4), player_one->getSprite()->position[1], game_data.get()));
		if (game_data->player_can_shoot)
		{
			player_one->attack();
		}
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
		if (game_action == GameAction::SELECT)
		{
			switch (menu->menu_state)
			{
			case MainMenu::MenuState::PLAY:
				game_data->game_state = GameData::GameState::PLAYING;
				break;
			case MainMenu::MenuState::HIGHSCORES:
				game_data->game_state = GameData::GameState::LEADERBOARD;
				break;
			case MainMenu::MenuState::QUIT:
				this->exit = true;
				break;
			default:
				renderer->renderText("NOT WORKING", 50, 50, ASGE::COLOURS::WHITE);
			}
		}
		break;
		/*
	case GameData::GameState::PLAYING:
		switch (game_action)
		{
		case GameAction::LEFT:
			player_one->setMoveState(Player::Movement::LEFT);
			break;
		case GameAction::RIGHT:
			player_one->setMoveState(Player::Movement::RIGHT);
			break;
		case GameAction::NONE:
			player_one->setMoveState(Player::Movement::NONE);
			break;
		}
		*/
	}
}