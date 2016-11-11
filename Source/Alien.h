#pragma once
#include "GameActor.h"

class Alien : public GameActor
{
public:
	Alien() = default;
	~Alien() = default;

	void attack();
	int getScoreToAdd();
	void setScoreToAdd();
	virtual void move() override;
protected:
	int points_worth;
};