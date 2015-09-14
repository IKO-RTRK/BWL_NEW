#include <stdlib.h>
#include "bowling_game.h"

BOWLING_GAME* bowlingGameCreate()
{
	BOWLING_GAME* game = (BOWLING_GAME*) malloc( sizeof(BOWLING_GAME) );
	return game;
}

uint8_t playerCanThrow(BOWLING_GAME* the_game, uint8_t current_frame, uint8_t current_player)
{
	return 0;
}

void writeDownTheScore(BOWLING_GAME* the_game, uint8_t current_player, uint8_t number_of_pins)
{

}


uint8_t isLaneValid(uint8_t number_of_lanes)
{
	return	(number_of_lanes >= 1 && number_of_lanes <= MAX_LANES);
}

uint8_t isPlayerValid(uint8_t number_of_players)
{
	return (number_of_players >= 1 && number_of_players <= MAX_PLAYERS_PER_LANE);
}

