#include <stdlib.h>
#include "bowling_game.h"
#include <inttypes.h>

static uint8_t canThrowFirst9Frames(BOWLING_GAME* the_game, uint8_t current_frame, uint8_t current_player)
{
	if(the_game->current_roll[current_player]>=current_frame*2 && the_game->current_roll[current_player]<=current_frame*2+1 && the_game->frames[current_player][current_frame]<10)
		return 1;
	else 
		return 0;
}

static uint8_t canThrowInLastFrame(BOWLING_GAME* the_game, uint8_t current_frame, uint8_t current_player)
{
	if(current_frame == NUM_OF_FRAMES-1 && the_game->current_roll[current_player]>=current_frame*2 && the_game->current_roll[current_player]<=current_frame*2+2)
		return 1;
	else 
		return 0;
}


static uint8_t firstAndSecondRollInLastFrame(BOWLING_GAME* the_game, uint8_t current_frame, uint8_t current_player)
{
	if(the_game->current_roll[current_player]<current_frame*2+2)
		return 1;
	else 
		return 0;
}

static uint8_t allowed3thRollInLastFrame(BOWLING_GAME* the_game, uint8_t current_frame, uint8_t current_player)
{
	if(the_game->frames[current_player][current_frame]>=10 && the_game->current_roll[current_player]==current_frame*2+2)
		return 1;
	else
		return 0;
}
static int isSpare(BOWLING_GAME* the_game, uint8_t i, uint8_t current_player)
{

	if ((the_game -> rolls[current_player][i] + the_game -> rolls[current_player][i+1]) == ALL_PINS_DOWN)
	{
		return 1;
	}
	return 0;
}

BOWLING_GAME* bowlingGameCreate()
{
	BOWLING_GAME* game = (BOWLING_GAME*) calloc( 1, sizeof(BOWLING_GAME) );
	return game;
}


uint8_t playerCanThrow(BOWLING_GAME* the_game, uint8_t current_frame, uint8_t current_player)
{
	uint8_t return_value;
	if(current_frame < NUM_OF_FRAMES-1)
	{
		if(canThrowFirst9Frames(the_game, current_frame, current_player))
		{
			return_value = 1;		
		}else
		{
			return_value = 0;	
		}

		return return_value;

	}else if(canThrowInLastFrame(the_game, current_frame, current_player))
	{
		
		if(firstAndSecondRollInLastFrame(the_game , current_frame , current_player))
		{
			return_value = 1;

		}else if(allowed3thRollInLastFrame(the_game, current_frame, current_player))
		{
			return_value = 1;		
		}else
		{
			return_value = 0;
		}		

		return return_value;
	}else
	{
		printf("prekoracenje broja frame-ova");
		return 0;		
	}
}



static void score(BOWLING_GAME* the_game, uint8_t current_player)
{
	uint8_t i; 
	uint8_t j = 0;


	the_game -> totalScore[current_player] = 0;
	uint16_t tot_score = the_game -> totalScore[current_player];
	uint8_t cr = the_game -> current_roll[current_player];
	int8_t k = cr / 2;
	
	for (i = 0; i < k; i++) 
	{
		if (the_game -> rolls[current_player][j] == ALL_PINS_DOWN)            
		{	
			if(j < LAST_FRAME_FIRST_THROW)
			{
				if (the_game -> rolls[current_player][j + 2] == ALL_PINS_DOWN)           // Double
				{
					the_game -> frames[current_player][i] = tot_score += (ALL_PINS_DOWN + the_game -> rolls[current_player][j + 2] + the_game -> rolls[current_player][j + 4]);
				}							
				else				                   // Strike
				{
					the_game -> frames[current_player][i] = tot_score += (ALL_PINS_DOWN + the_game -> rolls[current_player][j + 2] + the_game -> rolls[current_player][j + 3]);
				}
			}
			else
			{	
				the_game -> frames[current_player][i] = tot_score += (ALL_PINS_DOWN + the_game -> rolls[current_player][j + 1] + the_game -> rolls[current_player][j + 2]);
			}
		}
		else if (isSpare(the_game, j, current_player) && (j <= LAST_FRAME_FIRST_THROW))           // Spare
		{
			the_game -> frames[current_player][i] = tot_score += (ALL_PINS_DOWN + the_game -> rolls[current_player][j + 2]);
		}
		else
		{
			the_game -> frames[current_player][i] = tot_score += (the_game -> rolls[current_player][j] + the_game -> rolls[current_player][j + 1]);
		}
		j += 2;
		the_game -> totalScore[current_player] = tot_score;
	}
}

void writeDownTheScore(BOWLING_GAME* the_game, uint8_t current_player, uint8_t number_of_pins)
{	
	uint8_t cr = the_game -> current_roll[current_player];

	if (cr == MAX_ROLLS)
	{
		cr = 0;
	}
	
	the_game -> rolls[current_player][cr] = number_of_pins;

	if ((number_of_pins == ALL_PINS_DOWN) && (cr < LAST_FRAME_FIRST_THROW)) 
	{
		the_game -> rolls[current_player][++the_game -> current_roll[current_player]] = 0;	
	}
	
	the_game -> current_roll[current_player]++;

	cr = the_game -> current_roll[current_player];
	
	if ((cr % 2 == 0 && cr != 0) || cr  == MAX_ROLLS)
	score(the_game, current_player);
}







uint8_t isLaneValid(uint8_t number_of_lanes)
{
	return	(number_of_lanes >= 1 && number_of_lanes <= MAX_LANES);
}

uint8_t isPlayerValid(uint8_t number_of_players)
{
	return (number_of_players >= 1 && number_of_players <= MAX_PLAYERS_PER_LANE);
}




