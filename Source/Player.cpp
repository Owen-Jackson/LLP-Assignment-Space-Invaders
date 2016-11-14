#include "Player.h"

Player::Movement Player::getMoveState()
{
	return move_state;
}

void Player::setMoveState(Movement new_state)
{
	move_state = new_state;
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