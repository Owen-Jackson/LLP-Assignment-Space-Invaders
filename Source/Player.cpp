#include "Player.h"

Player::Player(GameData* _GD) : GameActor::GameActor(_GD)
{
	game_data = _GD;
	move_speed = 4;
	type = PLAYER;
	laser = std::make_unique<Laser>(true, _GD);
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
		laser->spawn(actor_sprite->position[0] + (actor_sprite->size[0] * actor_sprite->scale) / 2, actor_sprite->position[1]);	//set laser position to where the player is
		game_data->player_can_shoot = false;
	}
}

//Check if player is at edge of the screen
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

void Player::tick()
{
	if (alive)
	{
		move();
		actor_sprite->render(game_data->renderer);
		laser->tick();
	}
	else
	{
		//delayed respawn
		respawn_timer--;
		if (respawn_timer == 0)
		{
			alive = true;
			respawn_timer = 50;
		}
	}
}

Laser* Player::getLaser()
{
	return laser.get();
}