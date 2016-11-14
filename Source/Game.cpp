#include "Game.h"
#include "Actions.h"
#include "Constants.h"
#include "GameFont.h"
#include "MainMenu.h"
#include "Player.h"

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
	player_one = std::make_unique<Player>();
	player_one->loadSprite(renderer);
	player_one->getSprite()->position[0] = 310;
	player_one->getSprite()->position[1] = 280;
	if (!player_one->getSprite()->loadTexture("..\\..\\Resources\\Textures\\Player.jpg"))
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
		if (game_state == GameState::SPLASH_SCREEN)
		{
			render();
		}
		else if (game_state == GameState::MAIN_MENU)
		{
			processGameActions();
			updateMainMenu();
		}
		else if (game_state == GameState::PLAYING)
		{
			updatePlaying();
		}
		else if (game_state == GameState::PAUSED)
		{
			updatePauseScreen();
		}
		else if (game_state == GameState::GAME_OVER)
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
	menu->selection_arrow->position[0] = 310;
	menu->selection_arrow->position[1] = 280;
	menu->selection_arrow->scale = 0.1;
	if (!menu->selection_arrow->loadTexture("..\\..\\Resources\\Textures\\Alien Large.png"))
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
	player_one->getSprite()->render(renderer);
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
		if (key == ASGE::KEYS::KEY_ENTER || key == ASGE::KEYS::KEY_SPACE)
		{
			game_action = GameAction::SELECT;
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
	if (game_action == GameAction::EXIT)
	{
		this->exit = true;
	}
	else if (game_action == GameAction::DOWN)
	{
		menu->processMenuStates(game_action);
	}
	else if (game_action == GameAction::UP)
	{
		menu->processMenuStates(game_action);
	}
	else if (game_action == GameAction::SELECT)
	{
		this->inputs->addCallbackFnc(&InvadersGame::processStates, this);
	}
	game_action = GameAction::NONE;
}

void InvadersGame::processStates(int key, int action)
{
	if (action == ASGE::KEYS::KEY_PRESSED && game_state == GameState::SPLASH_SCREEN)
	{
		game_state = GameState::MAIN_MENU;
		callback_id = this->inputs->addCallbackFnc(&InvadersGame::input, this);
	}
	if (game_state == GameState::MAIN_MENU && game_action == GameAction::SELECT)
	{
		switch (menu->menu_state)
		{
		case MainMenu::MenuState::PLAY:
			game_state = GameState::PLAYING;
			break;
		case MainMenu::MenuState::HIGHSCORES:
			game_state = GameState::LEADERBOARD;
			break;
		case MainMenu::MenuState::QUIT:
			this->exit = true;
			break;
		default:
			renderer->renderText("NOT WORKING", 50, 50, ASGE::COLOURS::WHITE);
		}
		//callback_id = this->inputs->addCallbackFnc(&InvadersGame::input, this);
	}
}