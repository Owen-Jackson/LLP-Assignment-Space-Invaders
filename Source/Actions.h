#pragma once
#include <string>
#include <atomic>

/** @file Actions.h
    @brief   Actions file defines a thread safe game action
    @details GameActions are stored here as well as a thread safe  
             GameAction variable, which has external linkage. 
*/


/** @enum GameAction
*   @brief is a strongly typed enum class representing the next game action
*/
enum class GameAction
{
	INVALID = -1,  /**< is a non-valid game action */
	NONE    =  0,  /**< means no outstanding action to process */
	LEFT,		   /**< signals to move the player left */
	RIGHT,		   /**< signals to move the player right */
	UP,			   /**< used to navigate up in the menu */
	DOWN,		   /**< used to navigate down in the menu */
	SHOOT,		   /**< signals the intention to shoot */
	SELECT,		   /**< used when choosing options from the menus */
	PAUSE           /**< signals the intention to pause or exit the game */
};

extern std::atomic<GameAction> game_action;