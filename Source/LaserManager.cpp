#pragma once
#include "LaserManager.h"

LaserManager::LaserManager(GameData* _GD)
{
	game_data = _GD;
	init();
}

void LaserManager::init()
{
	//laser_list.push_back(std::move(std::make_unique<Laser>(true, 50, 500, game_data)));
}

void LaserManager::addLaser(std::unique_ptr<Laser>&& laser)
{
	laser->getSprite()->scale = 0.2;
	laser_list.push_back(std::move(laser));
}

void LaserManager::tick()
{
	for (int i = 0; i < laser_list.size(); i++)
	{
		laser_list[i]->tick();
	}
}

void LaserManager::render()
{
	for (const auto& laser : laser_list)
	{
		laser->getSprite()->render(game_data->renderer);
	}
}