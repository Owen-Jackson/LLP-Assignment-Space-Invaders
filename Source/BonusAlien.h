#pragma once
#include "Alien.h"

class BonusAlien : public Alien
{
public:
	BonusAlien(GameData* _GD);
	~BonusAlien() = default;

	void move() override;
	bool checkCollisions() override;
	void tick() override;
};