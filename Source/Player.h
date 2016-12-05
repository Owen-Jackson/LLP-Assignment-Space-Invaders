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
	bool checkCollisions() override;
	void tick() override;

private:
	std::unique_ptr<Laser> laser = nullptr;
};