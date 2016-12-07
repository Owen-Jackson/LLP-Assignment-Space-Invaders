#include "StandardAlien.h"
#include "Laser.h"

StandardAlien::StandardAlien(GameData* _GD) : Alien::Alien(_GD)
{
	game_data = _GD;
	move_state = RIGHT;
	move_speed = 10;
	type = ALIEN;
	laser = std::make_unique<Laser>(false, _GD);
	laser->setIsAlive(false);
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

//Check if alien is at edge of game screen
bool StandardAlien::hitScreenEdge()
{
	if (move_state == RIGHT)
	{
		if ((actor_sprite->position[0] + actor_sprite->size[0] * actor_sprite->scale) >= WINDOW_WIDTH - 20)
		{
			return true;
		}
	}
	else if (move_state == LEFT)
	{
		if(actor_sprite->position[0] <= 20)
		{
			return true;
		}
	}
	else if (move_state == DOWN)
	{
		return true;
	}
	return false;
}

//Set the move direction back after moving down one tick
void StandardAlien::changeDirection()
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

void StandardAlien::attack()
{
	laser->spawn(actor_sprite->position[0] + (actor_sprite->size[0] * actor_sprite->scale)/2, actor_sprite->position[1] + actor_sprite->size[1] * actor_sprite->scale);
}

void StandardAlien::tick()
{
	if (alive)
	{
		if (game_data->frame_count >= game_data->max_count)
		{
			move();
			if (move_state == DOWN)
			{
				changeDirection();
			}
		}
	}
	laser->tick();
}

Laser* StandardAlien::getLaser()
{ 
	return laser.get(); 
}