#pragma once
#include "Alien.h"

class BonusAlien : public Alien
{
public:
	BonusAlien();
	~BonusAlien() = default;

	virtual void move() override;
};