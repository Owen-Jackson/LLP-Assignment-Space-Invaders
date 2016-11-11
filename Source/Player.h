#pragma once
#include "GameActor.h"

class Player : public GameActor
{
public:
	Player() = default;
	~Player() = default;

	void attack() override;
	void move() override;
};