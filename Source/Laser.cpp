#include "Laser.h"
#include <Engine/Renderer.h>

Laser::Laser(bool player_laser, int pos_x, int pos_y, GameData* _GD) : GameActor::GameActor(_GD)
{
	game_data = _GD;
	is_player_laser = player_laser;
	init(pos_x, pos_y);
}

void Laser::move()
{
	if (is_player_laser)
	{
		actor_sprite->position[1] -= 5;
	}
	else
	{
		actor_sprite->position[1] += 5;
	}
}

void Laser::init(int spawn_x, int spawn_y)
{
	actor_sprite = game_data->renderer->createSprite();
	actor_sprite->position[0] = spawn_x;
	actor_sprite->position[1] = spawn_y;
	if (is_player_laser)
	{
		if (!actor_sprite->loadTexture("..\\..\\Resources\\Textures\\Player Laser.png"))
		{
			game_data->renderer->renderText("NOPE", 0, 0, ASGE::COLOURS::WHITE);
		}
	}
	else
	{
		if (!actor_sprite->loadTexture("..\\..\\Resources\\Textures\\Alien Laser.png"))
		{
			game_data->renderer->renderText("NOPE", 200, 0, ASGE::COLOURS::WHITE);
		}
	}
}

void Laser::tick()
{
	if (alive)
	{
		game_data->renderer->renderText("DO A SHOOT", 400, 400, ASGE::COLOURS::WHITE);
		move();
		render();
	}
}

bool Laser::checkCollisions()
{
	if (actor_sprite->position[1] == 0 || actor_sprite->position[1] + actor_sprite->size[1] == WINDOW_HEIGHT)
	{
		alive = false;
		game_data->player_can_shoot = true;
		return true;
	}
	else
	{
		return false;
	}
}

void Laser::render()
{
	actor_sprite->render(game_data->renderer);
}