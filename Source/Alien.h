#pragma once
#include "GameActor.h"

class Alien : public GameActor
{
public:
	Alien(GameData* _GD);
	virtual ~Alien() = default;

	int getScoreToAdd();
	void setScoreToAdd(int score);

	virtual void tick() = 0;
	virtual void move() = 0;

protected:
	int points_worth;
};