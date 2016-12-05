#include "AlienManager.h"
#include <Engine/Colours.h>
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>

AlienManager::AlienManager(GameData* _GD)
{
	game_data = _GD;
	initManager();
}

void AlienManager::initManager()
{
	aliens.reserve(55);
	int column_count = 0, row_count = 0;
	for (int i = 0; i < aliens.capacity(); i++)
	{
		aliens.push_back(std::move(std::make_unique<StandardAlien>(game_data)));
		aliens[i]->loadSprite(game_data->renderer);
		aliens[i]->getSprite()->position[0] = column_count * 50 + 300;
		aliens[i]->getSprite()->position[1] = row_count * 50 + 100;
		aliens[i]->getSprite()->scale = 0.3;
		aliens[i]->setColumnPosition(column_count);
		game_data->number_of_alive_aliens++;
		if (i > 32)
		{
			if (!aliens[i]->getSprite()->loadTexture("..\\..\\Resources\\Textures\\Large Alien 1.png"))
			{
				game_data->renderer->renderText("The sprite didn't load", 400, 400, ASGE::COLOURS::WHITE);
			}
			if (i > 43)
			{
				aliens[i]->setBottomOfColumn(true);
			}
		}
		else if (i > 10)
		{
			if (!aliens[i]->getSprite()->loadTexture("..\\..\\Resources\\Textures\\Standard Alien 1.png"))
			{
				game_data->renderer->renderText("The sprite didn't load", 400, 400, ASGE::COLOURS::WHITE);
			}
		}
		else
		{
			if (!aliens[i]->getSprite()->loadTexture("..\\..\\Resources\\Textures\\Small Alien 1.png"))
			{
				game_data->renderer->renderText("The sprite didn't load", 400, 400, ASGE::COLOURS::WHITE);
			}
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
	if (checkEdgeCollisions() > 0)
	{
		for (const auto& alien : aliens)
		{
			if (alien->getMoveState() != GameActor::Movement::DOWN)
			{
				alien->setMoveState(GameActor::Movement::DOWN);
			}
			else
			{
				alien->changeDirection();
			}
		}
	}
	if (game_data->aliens_can_shoot)
	{
		bool found_alien = false;
		float r1 = rand() % 100;
		if (r1 < 0.5)
		{
			while (found_alien == false)
			{
				int r2 = rand() % 55;
				if (aliens[r2]->getBottomOfColumn())
				{
					aliens[r2].get()->attack();
					found_alien = true;
				}
			}
			game_data->aliens_can_shoot = false;
		}
	}
	for (const auto& alien : aliens)
	{
		alien->tick();
	}
	//setBottomRowAliens();
}

void AlienManager::render()
{
	for (const auto& alien : aliens)
	{
		alien->getSprite()->render(game_data->renderer);
	}
}

void AlienManager::setBottomRowAliens()
{
	int column_count = 0, row_count = 0;
	for (int i = 0; i < aliens.size(); i++)
	{
		if (aliens[i]->getIsAlive())
		{
			if (i > 43 && aliens[i]->getIsAlive())
			{
				aliens[i]->setBottomOfColumn(true);
			}
			else if (aliens[i + 11]->getIsAlive())
			{
				aliens[i]->setBottomOfColumn(true);
			}
			else
			{
				aliens[i]->setBottomOfColumn(false);
			}
		}
	}
}