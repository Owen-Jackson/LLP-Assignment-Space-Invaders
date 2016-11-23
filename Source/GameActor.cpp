#include <Engine/Sprite.h>
#include <Engine/Renderer.h>
#include "GameActor.h"

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

void GameActor::setMoveState(Movement new_state)
{
	move_state = new_state;
}