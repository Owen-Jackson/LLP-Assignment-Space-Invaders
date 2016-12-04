#include "StandardAlien.h"
#include "Laser.h"

StandardAlien::StandardAlien(GameData* _GD) : Alien::Alien(_GD)
{
	game_data = _GD;
	move_state = RIGHT;
	move_speed = 10;
}

void StandardAlien::move()
{
	if (move_state == RIGHT)
	{
		actor_sprite->position[0] += move_speed;
		previous_move_state = RIGHT;
	}
	else if (move_state == LEFT)
	{
		actor_sprite->position[0] -= move_speed;
		previous_move_state = LEFT;
	}
	else if (move_state == DOWN)
	{
		actor_sprite->position[1] += actor_sprite->size[1] * actor_sprite->scale;
	}
}

bool StandardAlien::checkCollisions()
{
	if (hitScreenEdge())
	{
		return true;
	}
	return false;
}

bool StandardAlien::hitScreenEdge()
{
	if ((actor_sprite->position[0] + actor_sprite->size[0] * actor_sprite->scale) >= WINDOW_WIDTH - 20 ||
		actor_sprite->position[0] <= 20)
	{
		if (move_state != DOWN)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void StandardAlien::changeDirection()
{
	if (move_state == RIGHT)
	{
		move_state = LEFT;
	}
	else if (move_state == LEFT)
	{
		move_state = RIGHT;
	}
	else if (move_state == DOWN)
	{
		if (previous_move_state == RIGHT)
		{
			move_state = LEFT;
		}
		else if (previous_move_state == LEFT)
		{
			move_state = RIGHT;
		}
	}
}

void StandardAlien::attack()
{
	if (canAttack)
	{
		//std::unique_ptr<Laser> laser = std::make_unique<Laser>();
	}
}