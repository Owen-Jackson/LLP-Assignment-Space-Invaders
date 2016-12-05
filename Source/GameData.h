#pragma once
#include <Engine/Sprite.h>
#include <memory>
#include <vector>

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
	float delta_time = 0;
	float frame_count = 0;
	float max_count = 30;
	bool player_can_shoot = true;
	bool aliens_can_shoot = true;
	GameState game_state = GameState::MAIN_MENU;

	std::shared_ptr<ASGE::Renderer> renderer;
};