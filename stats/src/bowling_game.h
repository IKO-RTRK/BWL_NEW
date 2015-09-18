/**
* @file bowling_game.h
* @brief Document contains short description of used structures and functions
* @author RT-RK Bowling_Game
* @date September , 2015
*/
#ifndef _BOWLING_GAME_H
#define _BOWLING_GAME_H
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "../../player/src/player.h"

/*!
  Defines number of knocked pins when all fall down
*/
#define ALL_PINS_DOWN 10
/*!
  Defines maximum number for first throw in last frame
*/
#define LAST_FRAME_FIRST_THROW 18
enum 
{ 
	MAX_LANES		= 3,		///<  Maximum number of lanes per game 
	MAX_PLAYERS_PER_LANE 	= 6,		///<  Maximum number of players per lane in one game
	NUM_OF_FRAMES 		= 10,		///<  Number of frames in one game
	MAX_ROLLS 		= 21 		///<  Maximum number of rolls for each player in one game
};

/**
* @brief Structure contains information about bowling game 

*/

typedef struct bowling_game
{
	uint8_t lane_number;						///< Number of lane in game
	uint8_t number_of_players;					///< Number of players in game

	uint8_t current_roll[MAX_PLAYERS_PER_LANE];			///< Number of roll for each player in that moment

	uint8_t rolls[MAX_PLAYERS_PER_LANE][MAX_ROLLS];			///< Matrix of all players with their scores for each roll
	uint16_t totalScore[MAX_PLAYERS_PER_LANE];			///< Total score of one player in game. See #MAX_PLAYERS_PER_LANE
	uint16_t frames[MAX_PLAYERS_PER_LANE][NUM_OF_FRAMES];		///< Matrix of all players with their scores in each frame

	struct player* players[MAX_PLAYERS_PER_LANE];			///< See struct player in BWL_NEW/player/src/player.h
} BOWLING_GAME;

/**
  * @brief	This method allocates memory for structure \ref bowling_game.
		Must be called before any other method in this file.
  * @param	void
  * @retval	BOWLING_GAME* Returns pointer to the allocated memory.
  */
BOWLING_GAME* bowlingGameCreate();


/**
  * @brief	This method checks if player can throw the ball
		
  * @param	*the_game	pointer to structure \ref BOWLING_GAME
  * @param	current_frame	information about current frame
  * @param	current_player	information about current player who plays on lane
  * @retval	int		information can be 1 or 0
  */
uint8_t playerCanThrow(BOWLING_GAME* the_game, uint8_t current_frame, uint8_t current_player);



/**
  * @brief	This method calculates score of each player for each frame
  * @param	*the_game	   Pointer to structure BOWLING_GAME
  * @param	current_player	   Information about current player who plays on lane
  * @param	number_of_pins 	   Number of knocked down pins		
 
  * @retval	void	   
  */
void writeDownTheScore(BOWLING_GAME* the_game, uint8_t current_player, uint8_t number_of_pins);



/**
  * @brief	This method is validation of lane
		
  * @param	number_of_lanes
  * @retval	int
  */
uint8_t isLaneValid(uint8_t number_of_lanes);



/**
  * @brief	This method is validation of player	
		
  * @param	number_of_players
  * @retval	int
  */
uint8_t isPlayerValid(uint8_t number_of_players);
#endif

