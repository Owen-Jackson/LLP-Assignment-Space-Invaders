#pragma once
#include <Engine/Sprite.h>
#include"GameData.h"
#include "GameActor.h"

namespace ASGE
{
	class Renderer;
	class Sprite;
}

class Laser : public GameActor
{
public:
	Laser(bool player_laser, int pos_x, int pos_y, GameData* _GD);
	~Laser() = default;

	void init(int spawn_x, int spawn_y);
	void move();
	void tick();
	bool checkCollisions();
	void render();

private:
	bool is_alive = true;
	bool is_player_laser;
};