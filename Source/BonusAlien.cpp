#include "BonusAlien.h"
#include "GameActor.h"

BonusAlien::BonusAlien(GameData* _GD) : Alien::Alien(_GD)
{
	game_data = _GD;
	setScoreToAdd(300);
	move_speed = 3;
	canAttack = false;
}

void BonusAlien::move()
{

}

bool BonusAlien::checkCollisions()
{
	return false;
}