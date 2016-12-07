#include "Alien.h"

Alien::Alien(GameData* _GD) : GameActor::GameActor(_GD)
{
	game_data = _GD;
	type = ALIEN;
}

int Alien::getScoreToAdd()
{
	return points_worth;
}

void Alien::setScoreToAdd(int score)
{
	points_worth = score;
}