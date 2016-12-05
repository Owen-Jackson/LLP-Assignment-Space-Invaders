#pragma once
#include "LaserManager.h"

LaserManager::LaserManager(GameData* _GD)
{
	game_data = _GD;
	init();
}

void LaserManager::init()
{
	;
}

void LaserManager::addLaser(std::unique_ptr<Laser>&& laser)
{
	laser->getSprite()->scale = 0.2;
	laser_list.push_back(std::move(laser));
}

void LaserManager::tick()
{
	for (auto& laser : laser_list)
	{
		laser->tick();
		if (!laser->getIsAlive())
		{
			laser.reset();
		}
	}
	number_of_bullets = laser_list.size();
}

void LaserManager::render()
{
	for (const auto& laser : laser_list)
	{
		laser->getSprite()->render(game_data->renderer);
	}
}