#pragma once
#include <Engine/Sprite.h>
#include "GameData.h"
#include "GameActor.h"

namespace ASGE
{
	class Renderer;
	class Sprite;
}

class Laser : public GameActor
{
public:
	Laser(bool player_laser, GameData* _GD);
	~Laser() = default;

	void init();
	void move() override;
	void tick() override;
	bool checkCollisions();
	void render();
	void spawn(int spawn_x, int spawn_y);

private:
	bool is_alive = false;	//toggled to determine whether to render
	bool is_player_laser;	//determines move_speed and travel direction
};