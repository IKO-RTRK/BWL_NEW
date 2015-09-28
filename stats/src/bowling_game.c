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


int allPinsDownInCurrentFrame(BOWLING_GAME* the_game, uint8_t current_player, uint8_t current_frame)
{
	if(the_game -> rolls[current_player][current_frame] == ALL_PINS_DOWN)
	{	
		return 1;
	}else
	{
		return 0;
	}
}

uint16_t addPoints(BOWLING_GAME* the_game, uint8_t current_player, uint8_t all_pins_are_down, uint8_t add_roll_1 , uint8_t add_roll_2)
{
	uint16_t return_value=0;
	
	if(all_pins_are_down && add_roll_1!=0 && add_roll_2 !=0 )
	{	
		return_value = (ALL_PINS_DOWN + the_game -> rolls[current_player][add_roll_1] + the_game -> rolls[current_player][add_roll_2]);
	
	}else if(all_pins_are_down && add_roll_1!=0 && add_roll_2 ==0)
	{
		return_value = (ALL_PINS_DOWN + the_game -> rolls[current_player][add_roll_1]);
	}else
	{
		return_value = ( the_game -> rolls[current_player][add_roll_1] + the_game -> rolls[current_player][add_roll_2]);
	}


	return return_value;
}

static void score(BOWLING_GAME* the_game, uint8_t current_player)
{
	uint8_t i; 
	uint8_t current_roll = 0;
	uint8_t current_frame = (the_game -> current_roll[current_player]) / 2;

	the_game -> totalScore[current_player] = 0;
	uint16_t tot_score = the_game -> totalScore[current_player];
	
	
	for (i = 0; i < current_frame ; i++) 									
	{
		if (allPinsDownInCurrentFrame(the_game , current_player , current_roll))            			// clear in current frame (current_roll is first roll in each frame here)
		{	
			if(current_roll < LAST_FRAME_FIRST_THROW)							// NOT LAST FRAME
			{
				if (allPinsDownInCurrentFrame(the_game , current_player , current_roll+2 ))            //clear in next frame (current_roll+2 is firs roll in next frame)
				{
					the_game -> frames[current_player][i] = tot_score += addPoints(the_game, current_player, 1 , current_roll+2 , current_roll+4); // points= 
																	//    ALL_PINS_DOWN+next_frame_points+ (next_frame+1)_points
				}							
				else				                   				       //player hadnt clear in next frame , but had strike in next frame 
				{
				the_game -> frames[current_player][i] = tot_score += addPoints( the_game , current_player, 1 , current_roll+2, current_roll+3);	       // points=
																	//    ALL_PINS_DOWN+next_frame_points (1st and 2nd roll points)
				}
			}
			else														//	IS LAST FRAME
			{	
				the_game -> frames[current_player][i] = tot_score += addPoints( the_game , current_player, 1 , current_roll+1, current_roll+2);	// add points from next 2 rolls
			}
		}
		else if (isSpare(the_game, current_roll, current_player) && (current_roll <= LAST_FRAME_FIRST_THROW))           // Spare in current frame
		{
			the_game -> frames[current_player][i] = tot_score += addPoints( the_game , current_player, 1 , current_roll+2, 0);	//adding just points from first roll in next frame
		}
		else														// player had not even clear or spare in current frame
		{
			the_game -> frames[current_player][i] = tot_score += addPoints( the_game , current_player, 0 , current_roll,current_roll+1); //just add this frame points(2 rolls in frame)
		}
		current_roll += 2;																		//sledeci frame
		the_game -> totalScore[current_player] = tot_score;											//ukupni score se uvecava za ugatanu vrednost
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




