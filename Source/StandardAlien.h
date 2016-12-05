#pragma once
#include "Alien.h"
#include "Laser.h"

class StandardAlien : public Alien
{
public:
	StandardAlien(GameData* _GD);
	~StandardAlien() = default;

	void setBottomOfColumn(bool setting) { bottom_of_column = setting; }
	bool getBottomOfColumn() { return bottom_of_column; }
	void setColumnPosition(int pos) { column_pos = pos; }
	int getColumnPosition() { return column_pos; }


	void tick() override;
	void move() override;
	bool checkCollisions() override;
	bool hitScreenEdge();
	void changeDirection();
	void attack();

private:
	std::unique_ptr<Laser> laser;
	bool bottom_of_column = false;
	int column_pos;
};