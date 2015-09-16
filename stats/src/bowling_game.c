#include <stdlib.h>
#include "bowling_game.h"

BOWLING_GAME* bowlingGameCreate()
{
	BOWLING_GAME* game = (BOWLING_GAME*) malloc( sizeof(BOWLING_GAME) );
	return game;
}

uint8_t playerCanThrow(BOWLING_GAME* the_game, uint8_t current_frame, uint8_t current_player)
{
	return 1;
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



/*

static void doTheRoll(BOWLING_GAME* the_game, uint8_t current_frame, uint8_t current_player)
{
	BALL_POSITION final_ball_position;
	KNOCKED_DOWN_PINS knocked_down_pins;

	while (playerCanThrow(the_game, current_frame, current_player))
	{
		final_ball_position = throwTheBall(the_game, current_player);
		
		knocked_down_pins = knockDownPins(the_game->players[current_player], final_ball_position);

		writeDownTheScore(the_game, current_player, knocked_down_pins.number_of_pins);
		// animation spare/strike should go here based on writeDownTheScore() result!

		drawKnockedPinsAndTable(the_game, current_player, knocked_down_pins);
		usleep(MICRO_TIME_BETWEEN_TWO_ROLLS);
	}
}

*/
