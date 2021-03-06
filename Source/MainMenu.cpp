#include "MainMenu.h"
#include "Actions.h"

MainMenu::MainMenu(GameData* _GD)
{
	game_data = _GD;
	init();
}

void MainMenu::init()
{
	selection_arrow = game_data->renderer->createSprite();
	selection_arrow->position[0] = 430;
	selection_arrow->position[1] = 300;
	selection_arrow->scale = 0.3;
	if (!selection_arrow->loadTexture("..\\..\\Resources\\Textures\\Large Alien 1.png"))
	{
		game_data->renderer->renderText("The sprite didn't load", 400, 400, ASGE::COLOURS::WHITE);
	}
	selection_arrow->render(game_data->renderer);
}

void MainMenu::processMenuStates(GameAction action)
{
	if (action == GameAction::UP)
	{
		switch (menu_state)
		{
		case MenuState::PLAY:
			menu_state = MenuState::QUIT;
			changeSelection(2);	//loop to bottom
			break;
		case MenuState::HIGHSCORES:
			menu_state = MenuState::PLAY;
			changeSelection(-1);
			break;
		case MenuState::QUIT:
			menu_state = MenuState::HIGHSCORES;
			changeSelection(-1);
			break;
		}
	}
	if (action == GameAction::DOWN)
	{
		switch (menu_state)
		{
		case MenuState::PLAY:
			menu_state = MenuState::HIGHSCORES;
			changeSelection(1);
			break;
		case MenuState::HIGHSCORES:
			menu_state = MenuState::QUIT;
			changeSelection(1);
			break;
		case MenuState::QUIT:
			menu_state = MenuState::PLAY;
			changeSelection(-2);	//loop to top
			break;
		}
	}
	game_action = GameAction::NONE;
}

MainMenu::MenuState MainMenu::getMenuState()
{
	return menu_state;
}

void MainMenu::setMenuState(MainMenu::MenuState new_state)
{
	menu_state = new_state;
}
