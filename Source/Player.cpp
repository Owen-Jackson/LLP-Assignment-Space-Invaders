#include "Player.h"

Player::Player()
{
	move_speed = 2;
}

void Player::move()
{
	if (move_state == Movement::LEFT)
	{
		actor_sprite->position[0] -= move_speed;
	}
	else if (move_state == Movement::RIGHT)
	{
		actor_sprite->position[0] += move_speed;
	}
}

void Player::attack()
{
	;
}