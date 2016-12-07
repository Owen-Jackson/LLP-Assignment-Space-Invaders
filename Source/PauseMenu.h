#pragma once
#include "Menu.h"

enum class GameAction;

class PauseMenu : public Menu
{
public:
	enum MenuState 
	{
		RESUME,
		MAIN_MENU,
		QUIT
	};

	PauseMenu(GameData* _GD);
	~PauseMenu() = default;

	void init() override;
	void changeSelection(int new_position) override;
	void processMenuStates(GameAction action);

	//Accessors
	MenuState getMenuState();
	void setMenuState(MenuState new_state);

private:
	MenuState menu_state = MenuState::RESUME;
};