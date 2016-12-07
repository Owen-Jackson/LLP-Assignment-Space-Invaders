#include "AlienManager.h"
#include <Engine/Renderer.h>

AlienManager::AlienManager(GameData* _GD)
{
	game_data = _GD;
	initManager();
}

//initialise aliens and add them to the vector on startup
void AlienManager::initManager()
{
	aliens.reserve(55);
	int column_count = 0, row_count = 0;
	for (int i = 0; i < aliens.capacity(); i++)
	{
		aliens.push_back(std::move(std::make_unique<StandardAlien>(game_data)));
		aliens[i]->loadSprite(game_data->renderer);
		aliens[i]->getSprite()->position[0] = column_count * 50 + 350;
		aliens[i]->getSprite()->position[1] = row_count * 50 + 100;
		aliens[i]->getSprite()->scale = 0.35;
		game_data->number_of_alive_aliens++;
		if (i > 32)
		{
			if (!aliens[i]->getSprite()->loadTexture("..\\..\\Resources\\Textures\\Large Alien 1.png"))
			{
				game_data->renderer->renderText("The sprite didn't load", 400, 400, ASGE::COLOURS::WHITE);
			}
			aliens[i]->setScoreToAdd(10);
		}
		else if (i > 10)
		{
			if (!aliens[i]->getSprite()->loadTexture("..\\..\\Resources\\Textures\\Standard Alien 1.png"))
			{
				game_data->renderer->renderText("The sprite didn't load", 400, 400, ASGE::COLOURS::WHITE);
			}
			aliens[i]->setScoreToAdd(20);
		}
		else
		{
			if (!aliens[i]->getSprite()->loadTexture("..\\..\\Resources\\Textures\\Small Alien 1.png"))
			{
				game_data->renderer->renderText("The sprite didn't load", 400, 400, ASGE::COLOURS::WHITE);
			}
			aliens[i]->setScoreToAdd(30);
		}
		column_count++;
		if (column_count % 11 == 0)
		{
			column_count = 0;
			row_count++;
		}
	}
}

void AlienManager::addAlien(std::unique_ptr<StandardAlien>&& obj)
{
	aliens.push_back(std::move(obj));
}

int AlienManager::checkEdgeCollisions()
{
	int hit_count = 0;
	for (const auto& alien : aliens)
	{
		if (alien->hitScreenEdge())
		{
			hit_count++;
		}
	}
	return hit_count;
}

void AlienManager::tick()
{
	//Make sure the aliens can shoot before checking if they are alive to
	if (game_data->aliens_can_shoot)
	{
		bool found_alien = false;
		float r1 = rand() % 100;
		if (r1 < 0.5)
		{
			while (found_alien == false)
			{
				int r2 = rand() % 55;
				if (aliens[r2]->getIsAlive())
				{
					aliens[r2].get()->attack();
					found_alien = true;
				}
			}
			game_data->aliens_can_shoot = false;
		}
	}

	//Check if an alien has hit the edge of the screen
	if (checkEdgeCollisions() > 0)
	{
		if (moving_down == false)
		{
			for (const auto& alien : aliens)
			{
				if (alien->getIsAlive())
				{
					alien->setMoveState(GameActor::Movement::DOWN);
				}
			}
			moving_down = true;
		}
		else
		{
			moving_down = false;
		}
	}

	//Tick each alien in the vector
	for (const auto& alien : aliens)
	{
		alien->tick();
	}
}

//Only renders aliens that are still alive
void AlienManager::render()
{
	for (const auto& alien : aliens)
	{
		if (alien->getIsAlive())
		{
			alien->getSprite()->render(game_data->renderer);
		}
	}
}

//Checks if aliens are hit
void AlienManager::checkObjectCollisions(GameActor* obj, GameActor::ActorType obj_type)
{
	for (const auto& alien : aliens)
	{
		//If bounding boxes of the sprites are touching
		if (obj->getSprite()->position[0] + obj->getSprite()->size[0] * obj->getSprite()->scale >= alien->getSprite()->position[0]
			&& obj->getSprite()->position[0] <= alien->getSprite()->position[0] + alien->getSprite()->size[0] * alien->getSprite()->scale
			&& obj->getSprite()->position[1] + obj->getSprite()->size[1] * obj->getSprite()->scale >= alien->getSprite()->position[1]
			&& obj->getSprite()->position[1] <= alien->getSprite()->position[1] + alien->getSprite()->size[1] * alien->getSprite()->scale)
		{
			if (alien->getIsAlive())
			{
				//Kill the hit alien
				if (obj_type == GameActor::ActorType::PLAYER_LASER && obj->getIsAlive())
				{
					obj->setIsAlive(false);
					game_data->player_can_shoot = true;
					game_data->player_score += alien->getScoreToAdd();
					alien->setIsAlive(false);
					game_data->number_of_alive_aliens--;
					game_data->max_count -= 0.4;
				}
				//Kill the player - Game over
				if (obj_type == GameActor::ActorType::PLAYER && obj->getIsAlive())
				{
					game_data->player_lives = 0;
				}
			}
		}
	}
}

//Checks if player is hit by alien lasers
void AlienManager::checkLaserCollisions(GameActor* obj, GameActor::ActorType obj_type)
{
	for (const auto& alien : aliens)
	{
		if (obj->getSprite()->position[0] + obj->getSprite()->size[0] * obj->getSprite()->scale >= alien->getLaser()->getSprite()->position[0]
			&& obj->getSprite()->position[0] <= alien->getLaser()->getSprite()->position[0] + alien->getLaser()->getSprite()->size[0] * alien->getLaser()->getSprite()->scale
			&& obj->getSprite()->position[1] + obj->getSprite()->size[1] * obj->getSprite()->scale >= alien->getLaser()->getSprite()->position[1]
			&& obj->getSprite()->position[1] <= alien->getLaser()->getSprite()->position[1] + alien->getLaser()->getSprite()->size[1] * alien->getLaser()->getSprite()->scale)
		{
			if (obj->getIsAlive() && obj_type == GameActor::ActorType::PLAYER)
			{
				//Player loses life
				if (alien->getLaser()->getIsAlive())
				{
					alien->getLaser()->setIsAlive(false);
					obj->setIsAlive(false);
					game_data->player_lives--;
					obj->getSprite()->position[0] = WINDOW_WIDTH / 2;
					game_data->aliens_can_shoot = true;
				}
			}
		}
	}
}

//Used when a wave is cleared or after game over
void AlienManager::reset()
{
	game_data->number_of_alive_aliens = 0;
	game_data->max_count = 40;
	int row_count = 0, column_count = 0;
	for (int i = 0; i < aliens.capacity(); i++)
	{
		aliens[i]->getSprite()->position[0] = column_count * 50 + 350;
		aliens[i]->getSprite()->position[1] = row_count * 50 + 100;
		aliens[i]->setIsAlive(true);
		aliens[i]->setMoveState(GameActor::Movement::RIGHT);
		game_data->number_of_alive_aliens++;
		column_count++;
		if (column_count % 11 == 0)
		{
			column_count = 0;
			row_count++;
		}
	}
}