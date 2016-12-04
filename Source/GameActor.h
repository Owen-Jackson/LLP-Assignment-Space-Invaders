#pragma once
#include <Engine/Sprite.h>
#include "GameData.h"
#include "Constants.h"

enum class GameAction;

namespace ASGE
{
	class Renderer;
	class Sprite;
}

class GameActor
{
public:
	enum Movement
	{
		NONE,
		LEFT,
		RIGHT,
		DOWN
	};

	GameActor(GameData* _GD);
	virtual ~GameActor() = default;

	//Accessors
	void loadSprite(std::shared_ptr<ASGE::Renderer> renderer);
	ASGE::Sprite* getSprite();
	Movement getMoveState();
	Movement getPreviousMoveState();
	bool getIsAlive();
	void setMoveState(Movement new_state);
	void setPreviousMoveState(Movement last_state);
	void setIsAlive(bool setting);

	virtual void move() = 0;
	virtual bool checkCollisions() = 0;

protected:
	std::unique_ptr<ASGE::Sprite> actor_sprite = nullptr;
	float move_speed = 1;
	bool alive = true;
	Movement previous_move_state = NONE;
	Movement move_state = NONE;
	GameData* game_data = nullptr;
};