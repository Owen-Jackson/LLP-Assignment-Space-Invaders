#pragma once
#include "Alien.h"
#include "Laser.h"

class StandardAlien : public Alien
{
public:
	StandardAlien(GameData* _GD);
	~StandardAlien() = default;

	void tick() override;
	void move() override;
	bool hitScreenEdge();	//check if alien has hit the edge of the game screen
	void changeDirection();	//change direction when at edge of game screen
	void attack();	//shoot towards the player

	//Accessors
	Laser* getLaser();

private:
	std::unique_ptr<Laser> laser;
};