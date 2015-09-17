#include <stdlib.h>
#include "bowling_game.h"
#include <inttypes.h>

static int isSpare(BOWLING_GAME* the_game, uint8_t i, uint8_t current_player)
{
//	uint8_t cr = the_game -> current_roll[current_player];
	
//	printf("%hhd %hhd\n", the_game -> rolls[current_player][cr], the_game -> rolls[current_player][cr+1]);
	if ((the_game -> rolls[current_player][i] + the_game -> rolls[current_player][i+1]) == 10)
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
	
	return 1;
}



static void score(BOWLING_GAME* the_game, uint8_t current_player)
{
	uint8_t i; 
	uint8_t j = 0;


	the_game -> totalScore[current_player] = 0;
	
	uint8_t cr = the_game -> current_roll[current_player];
	int8_t k = cr / 2;
	
	for (i = 0; i < k; i++) 
	{
		if (the_game -> rolls[current_player][j] == 10)            
		{	
			if(j < 18)
			{
				if (the_game -> rolls[current_player][j + 2] == 10)           // Double
				{
					the_game -> frames[current_player][i] = the_game -> totalScore[current_player] += (10 + the_game -> rolls[current_player][j + 2] + the_game -> rolls[current_player][j + 4]);
				}							
				else				                   // Strike
				{
					the_game -> frames[current_player][i] = the_game -> totalScore[current_player] += (10 + the_game -> rolls[current_player][j + 2] + the_game -> rolls[current_player][j + 3]);
				}
			}
			else
			{	
				the_game -> frames[current_player][i] = the_game -> totalScore[current_player] += (10 + the_game -> rolls[current_player][j + 1] + the_game -> rolls[current_player][j + 2]);
			}
		}
		else if (isSpare(the_game, j, current_player) && (j <= 18))           // Spare
		{
			the_game -> frames[current_player][i] = the_game -> totalScore[current_player] += (10 + the_game -> rolls[current_player][j + 2]);
		}
		else
		{
			the_game -> frames[current_player][i] = the_game -> totalScore[current_player] += (the_game -> rolls[current_player][j] + the_game -> rolls[current_player][j + 1]);
		}
		j += 2;
	}
}

void writeDownTheScore(BOWLING_GAME* the_game, uint8_t current_player, uint8_t x)
{	
	uint8_t cr = the_game -> current_roll[current_player];

	if (cr == MAX_ROLLS)
	{
		cr = 0;
	}
	
	the_game -> rolls[current_player][cr] = x;

	if ((x == 10) && (cr < 18)) 
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




