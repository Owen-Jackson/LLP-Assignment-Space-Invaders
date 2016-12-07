#pragma once
#include "GameData.h"
#include <Engine/Sprite.h>
#include <Engine/Renderer.h>
#include <memory>

enum class GameAction;

class Menu
{
public:
	Menu() = default;
	virtual ~Menu() = default;

	virtual void init() = 0;
	virtual void changeSelection(int new_position);
	ASGE::Sprite* getSelectionSprite();

protected:
	std::unique_ptr<ASGE::Sprite> selection_arrow;
	GameData* game_data;
};