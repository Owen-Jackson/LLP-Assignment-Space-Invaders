#pragma once
#include "GameActor.h"
#include "Laser.h"

class Player : public GameActor
{
public:
	Player(GameData* _GD);
	~Player() = default;

	void attack();
	void move() override;
	bool checkCollisions() override;

private:
};