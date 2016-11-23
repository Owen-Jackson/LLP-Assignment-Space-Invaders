#pragma once
#include "Alien.h"

class StandardAlien : public Alien
{
public:
	StandardAlien();
	~StandardAlien() = default;

	virtual void move() override;
	bool hitScreenEdge();
};