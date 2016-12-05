#pragma once
#include "Laser.h"
#include "GameData.h"
#include <memory>
#include <vector>

class LaserManager
{
public:
	LaserManager(GameData* _GD);
	~LaserManager() = default;

	void init();
	void addLaser(std::unique_ptr<Laser>&& laser);
	void tick();
	void render();
	int number_of_bullets;
private:
	std::vector<std::unique_ptr<Laser>> laser_list;
	GameData* game_data = nullptr;
};