#pragma once
#include <Engine/Sprite.h>

enum class GameAction;

namespace ASGE
{
	class Renderer;
	class Sprite;
}

class GameActor
{
public:
	enum class Movement
	{
		NONE,
		LEFT,
		RIGHT
	};

	GameActor() = default;
	virtual ~GameActor() = default;

	//Accessors
	void loadSprite(std::shared_ptr<ASGE::Renderer> renderer);
	ASGE::Sprite* getSprite();
	Movement getMoveState();
	void setMoveState(Movement setting);

	virtual void attack() = 0;
	virtual void move() = 0;

protected:
	std::unique_ptr<ASGE::Sprite> actor_sprite = nullptr;
	float move_speed = 1;
	bool alive = true;
	Movement move_state = Movement::NONE;
};