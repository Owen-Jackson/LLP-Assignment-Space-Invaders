#include "PauseMenu.h"
#include "Actions.h"
#include <Engine/Sprite.h>

PauseMenu::PauseMenu(GameData* _GD)
{
	game_data = _GD;
	init();
}

void PauseMenu::init()
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

void PauseMenu::changeSelection(int position_multiplier)
{
	selection_arrow->position[1] += 50 * position_multiplier;
}

void PauseMenu::processMenuStates(GameAction action)
{
	if (action == GameAction::UP)
	{
		switch (menu_state)
		{
		case MenuState::RESUME:
			menu_state = MenuState::QUIT;
			changeSelection(2);	//loop to bottom
			break;
		case MenuState::MAIN_MENU:
			menu_state = MenuState::RESUME;
			changeSelection(-1);
			break;
		case MenuState::QUIT:
			menu_state = MenuState::MAIN_MENU;
			changeSelection(-1);
			break;
		}
	}
	if (action == GameAction::DOWN)
	{
		switch (menu_state)
		{
		case MenuState::RESUME:
			menu_state = MenuState::MAIN_MENU;
			changeSelection(1);
			break;
		case MenuState::MAIN_MENU:
			menu_state = MenuState::QUIT;
			changeSelection(1);
			break;
		case MenuState::QUIT:
			menu_state = MenuState::RESUME;
			changeSelection(-2);	//loop to top
			break;
		}
	}
	game_action = GameAction::NONE;
}

PauseMenu::MenuState PauseMenu::getMenuState()
{
	return menu_state;
}

void PauseMenu::setMenuState(PauseMenu::MenuState new_state)
{
	menu_state = new_state;
}