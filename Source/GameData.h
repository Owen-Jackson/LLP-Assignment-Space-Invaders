#pragma once
#include <Engine/Sprite.h>
#include <memory>

class Laser;

struct GameData
{
	enum class GameState
	{
		MAIN_MENU,
		PLAYING,
		LEADERBOARD,
		PAUSED,
		GAME_OVER,
		EXIT
	};

	int player_lives = 3;
	int player_score = 0;
	int number_of_alive_aliens = 0;
	float frame_count = 0;	//increments until over max_count
	float max_count = 40;	//when reached, tick the aliens
	bool player_can_shoot = true;	//toggled to prevent player from rapid firing
	bool aliens_can_shoot = true;	//toggled to prevent aliens from rapid firing
	GameState game_state = GameState::MAIN_MENU;

	std::shared_ptr<ASGE::Renderer> renderer;
};