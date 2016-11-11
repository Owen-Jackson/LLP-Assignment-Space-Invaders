#include <Engine/Sprite.h>
#include <Engine/Renderer.h>
#include "GameActor.h"


//Accessors
int GameActor::getXPosition() const
{
	return x_pos;
}

int GameActor::getYPosition() const
{
	return y_pos;
}

void GameActor::setXPosition(int new_x)
{
	x_pos = new_x;
}

void GameActor::setYPosition(int new_y)
{
	y_pos = new_y;
}

void GameActor::loadSprite(std::shared_ptr<ASGE::Renderer> renderer)
{
	actor_sprite = renderer->createSprite();
	//actor_sprite->loadTexture("Resources\\Textures\\avatar");
	//actor_sprite->size[0] = 92;
	//actor_sprite->size[1] = 92;
}

ASGE::Sprite* GameActor::getSprite()
{
	return actor_sprite.get();
}