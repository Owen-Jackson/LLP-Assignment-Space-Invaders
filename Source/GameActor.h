#pragma once
#include <Engine/Sprite.h>

namespace ASGE
{
	class Renderer;
	class Sprite;
}

class GameActor
{
public:
	GameActor() = default;
	virtual ~GameActor() = default;

	//Accessors
	int getXPosition() const;
	int getYPosition() const;
	void setXPosition(int xPos);
	void setYPosition(int yPos);
	void loadSprite(std::shared_ptr<ASGE::Renderer> renderer);
	ASGE::Sprite* getSprite();

	virtual void attack() = 0;
	virtual void move() = 0;

protected:
	std::unique_ptr<ASGE::Sprite> actor_sprite = nullptr;
	int x_pos = 0;
	int y_pos = 0;
	float move_speed;
	bool alive = true;
};