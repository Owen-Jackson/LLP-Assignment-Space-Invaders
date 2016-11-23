#pragma once
#include "GameActor.h"

class Alien : public GameActor
{
public:
	Alien() = default;
	~Alien() = default;

	void attack();
	int getScoreToAdd();
	void setScoreToAdd(int score);
	virtual void move() = 0;

protected:
	int points_worth = 100;
	bool canAttack = true;
};