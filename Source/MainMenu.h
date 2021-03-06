#pragma once
#include "Menu.h"

enum class GameAction;

class MainMenu : public Menu
{
public:
	enum MenuState
	{
		PLAY,
		HIGHSCORES,
		QUIT
	};

	MainMenu(GameData* _GD);
	~MainMenu() = default;

	void init() override;
	void processMenuStates(GameAction action);

	//Accessors
	MenuState getMenuState();
	void setMenuState(MenuState new_state);

private:
	MenuState menu_state = MenuState::PLAY;
};