#pragma once
#include "GameActor.h"
#include "Laser.h"
#include <memory>

class Player : public GameActor
{
public:
	Player(GameData* _GD);
	~Player() = default;

	void attack();
	void move() override;
	bool checkCollisions();
	void tick() override;

	Laser* getLaser();

private:
	std::unique_ptr<Laser> laser = nullptr;
	int respawn_timer = 50;
};