#include "GameActor.h"
#include <Engine/Renderer.h>

GameActor::GameActor(GameData* _GD)
{
	game_data = _GD;
}

void GameActor::loadSprite(std::shared_ptr<ASGE::Renderer> renderer)
{
	actor_sprite = renderer->createSprite();
}

ASGE::Sprite* GameActor::getSprite()
{
	return actor_sprite.get();
}

GameActor::Movement GameActor::getMoveState()
{
	return move_state;
}

GameActor::Movement GameActor::getPreviousMoveState()
{
	return previous_move_state;
}

bool GameActor::getIsAlive()
{
	return alive;
}

void GameActor::setMoveState(Movement new_state)
{
	move_state = new_state;
}

void GameActor::setPreviousMoveState(Movement last_state)
{
	previous_move_state = last_state;
}

void GameActor::setIsAlive(bool setting)
{
	alive = setting;
}