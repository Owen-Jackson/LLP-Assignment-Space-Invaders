#include "Player.h"
#include <memory>
#include <vector>

Player::Player(GameData* _GD) : GameActor::GameActor(_GD)
{
	game_data = _GD;
	move_speed = 2;
}

void Player::move()
{
	if (move_state == LEFT)
	{
		if (!checkCollisions())
		{
			actor_sprite->position[0] -= move_speed;
			previous_move_state = LEFT;
		}
	}
	else if (move_state == RIGHT)
	{
		if (!checkCollisions())
		{
			actor_sprite->position[0] += move_speed;
			previous_move_state = RIGHT;
		}
	}
}

void Player::attack()
{
	if (game_data->player_can_shoot)
	{
		game_data->player_can_shoot = false;
	}
}

bool Player::checkCollisions()
{
	if (move_state == RIGHT && (actor_sprite->position[0] + actor_sprite->size[0] * actor_sprite->scale) >= WINDOW_WIDTH - 20)
	{
		return true;
	}
	else if (move_state == LEFT && actor_sprite->position[0] <= 20)
	{
		return true;
	}
	return false;

}