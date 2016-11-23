#include "StandardAlien.h"
#include "Constants.h"

StandardAlien::StandardAlien()
{
	move_state = Movement::RIGHT;
}

void StandardAlien::move()
{
	if (move_state == Movement::RIGHT)
	{
		actor_sprite->position[0] += move_speed;
	}
	else if (move_state == Movement::LEFT)
	{
		actor_sprite->position[0] -= move_speed;
	}
}

bool StandardAlien::hitScreenEdge()
{
	if ((actor_sprite->position[0] + actor_sprite->size[0] * actor_sprite->scale) >= WINDOW_WIDTH ||
		actor_sprite->position[0] <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}