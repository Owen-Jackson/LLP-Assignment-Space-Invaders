#pragma once
#include "GameActor.h"

class Alien : public GameActor
{
public:
	Alien(GameData* _GD);
	virtual ~Alien() = default;

	int getScoreToAdd();
	void setScoreToAdd(int score);
	virtual void move() = 0;
	virtual bool checkCollisions() = 0;

protected:
	int points_worth = 100;
	bool canAttack = true;
};