#pragma once
#include "Alien.h"

class StandardAlien : public Alien
{
public:
	StandardAlien(GameData* _GD);
	~StandardAlien() = default;

	void move() override;
	bool checkCollisions() override;
	bool hitScreenEdge();
	void changeDirection();
	void attack();
};