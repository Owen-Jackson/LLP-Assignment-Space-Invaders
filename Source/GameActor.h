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
	enum ActorType	//used in collision checks
	{
		PLAYER_LASER,
		ALIEN_LASER,
		PLAYER,
		ALIEN
	};

	enum Movement	//used in move() to determine new positions
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
	ActorType getActorType();
	bool getIsAlive();
	void setMoveState(Movement new_state);
	void setPreviousMoveState(Movement last_state);
	void setIsAlive(bool setting);
	void setActorType(ActorType new_type);

	virtual void tick() = 0;
	virtual void move() = 0;

protected:
	std::unique_ptr<ASGE::Sprite> actor_sprite = nullptr;	//the sprite for this game actor
	float move_speed = 1;
	bool alive = true;
	Movement previous_move_state = NONE;	//used when moving the aliens down one tick before moving left/right again
	Movement move_state = NONE;
	GameData* game_data = nullptr;
	ActorType type;
};