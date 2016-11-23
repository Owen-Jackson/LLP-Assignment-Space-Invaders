#pragma once
#include "GameActor.h"

class Player : public GameActor
{
public:
	Player();
	~Player() = default;

	void attack() override;
	void move() override;
};