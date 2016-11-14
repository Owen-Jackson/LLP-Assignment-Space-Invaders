#include "MainMenu.h"
#include "Actions.h"
#include <Engine/Sprite.h>

void MainMenu::changeSelection(int position_multiplier)
{
	selection_arrow->position[1] += 50 * position_multiplier;
}

void MainMenu::processMenuStates(GameAction action)
{
	if (action == GameAction::UP)
	{
		switch (menu_state)
		{
		case MenuState::PLAY:
			menu_state = MenuState::QUIT;
			changeSelection(2);
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
			changeSelection(-2);
			break;
		}
	}
	game_action = GameAction::NONE;
}