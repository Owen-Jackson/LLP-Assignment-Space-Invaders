#include "BonusAlien.h"

//IMPLEMENTATION INCOMPLETE
BonusAlien::BonusAlien(GameData* _GD) : Alien::Alien(_GD)
{
	game_data = _GD;
	setScoreToAdd(300);
	move_speed = 3;
	type = ALIEN;
}

void BonusAlien::move()
{

}

bool BonusAlien::checkCollisions()
{
	return false;
}

void BonusAlien::tick()
{

}