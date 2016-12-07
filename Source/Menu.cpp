#include "Menu.h"
#include "Actions.h"
#include <Engine/Sprite.h>

void Menu::changeSelection(int position_multiplier)
{
	selection_arrow->position[1] += 50 * position_multiplier;
}

ASGE::Sprite* Menu::getSelectionSprite()
{
	return selection_arrow.get();
}