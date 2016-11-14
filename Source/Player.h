#pragma once
#include "GameActor.h"

class Player : public GameActor
{
public:
	enum class Movement
	{
		NONE,
		LEFT,
		RIGHT
	};

	Player() = default;
	~Player() = default;

	Movement getMoveState();
	void setMoveState(Movement new_state);

	void attack() override;
	void move() override;
private:
	Movement move_state = Movement::NONE;
};