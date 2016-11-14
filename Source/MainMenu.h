#pragma once
#include <Engine/OGLGame.h>
#include <memory>

enum class GameAction;

class MainMenu
{
	friend class InvadersGame;
	enum MenuState
	{
		PLAY,
		HIGHSCORES,
		QUIT
	};

public:
	MainMenu() = default;
	~MainMenu() = default;

	void changeSelection(int new_position);
	void processMenuStates(GameAction action);
	ASGE::Sprite* getSprite();

private:
	std::unique_ptr<ASGE::Sprite> selection_arrow;
	MenuState menu_state = MenuState::PLAY;

};