#include "Laser.h"
#include <Engine/Renderer.h>

Laser::Laser(bool player_laser, GameData* _GD) : GameActor::GameActor(_GD)
{
	game_data = _GD;
	is_player_laser = player_laser;
	init();
}

void Laser::move()
{
	if (is_player_laser)
	{
		actor_sprite->position[1] -= 2;
	}
	else
	{
		actor_sprite->position[1] += 2;
	}
}

void Laser::init()
{
	actor_sprite = game_data->renderer->createSprite();
	actor_sprite->scale = 0.2;
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
	tick();
}

void Laser::tick()
{
	if (alive)
	{
		move();
		checkCollisions();
		render();
	}
}

bool Laser::checkCollisions()
{
	if (actor_sprite->position[1] == 0 || actor_sprite->position[1] + actor_sprite->size[1]* actor_sprite->scale >= WINDOW_HEIGHT)
	{
		alive = false;
		if (is_player_laser)
		{
			game_data->player_can_shoot = true;
		}
		else
		{
			game_data->aliens_can_shoot = true;
		}
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

void Laser::spawn(int spawn_x, int spawn_y)
{
	alive = true;
	actor_sprite->position[0] = spawn_x;
	actor_sprite->position[1] = spawn_y;
}