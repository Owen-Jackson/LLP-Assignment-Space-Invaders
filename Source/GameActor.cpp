#include <Engine/Sprite.h>
#include <Engine/Renderer.h>
#include "GameActor.h"


//Accessors
int GameActor::getXPosition() const
{
	return actor_sprite->position[0];
}

int GameActor::getYPosition() const
{
	return actor_sprite->position[1];
}

void GameActor::setXPosition(int new_x)
{
	actor_sprite->position[0] = new_x;
}

void GameActor::setYPosition(int new_y)
{
	actor_sprite->position[1] = new_y;
}

void GameActor::loadSprite(std::shared_ptr<ASGE::Renderer> renderer)
{
	actor_sprite = renderer->createSprite();
}

ASGE::Sprite* GameActor::getSprite()
{
	return actor_sprite.get();
}