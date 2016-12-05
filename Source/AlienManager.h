#pragma once
#include "StandardAlien.h"
#include "BonusAlien.h"
#include "GameData.h"
#include <vector>

class StandardAlien;

class AlienManager
{
public:
	AlienManager(GameData* _GD);
	~AlienManager() = default;

	void initManager();
	int checkEdgeCollisions();
	void tick();
	void render();
	void setBottomRowAliens();

	//Add aliens to vector
	void addAlien(std::unique_ptr<StandardAlien>&&);

private:
	std::vector<std::unique_ptr<StandardAlien>> aliens;
	GameData* game_data = nullptr;
};