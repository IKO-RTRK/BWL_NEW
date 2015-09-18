#ifndef _BOWLING_GAME_H
#define _BOWLING_GAME_H
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#define ALL_PINS_DOWN 10
#define LAST_FRAME_FIRST_THROW 18


enum 
{ 
	MAX_LANES		= 3,
	MAX_PLAYERS_PER_LANE 	= 6,
	NUM_OF_FRAMES 		= 10,
	MAX_ROLLS 		= 21 
};

typedef struct bowling_game
{
	uint8_t lane_number;
	uint8_t number_of_players;

	uint8_t current_roll[MAX_PLAYERS_PER_LANE];

	uint8_t rolls[MAX_PLAYERS_PER_LANE][MAX_ROLLS];
	uint16_t totalScore[MAX_PLAYERS_PER_LANE];
	uint16_t frames[MAX_PLAYERS_PER_LANE][NUM_OF_FRAMES];

	struct player* players[MAX_PLAYERS_PER_LANE];
} BOWLING_GAME;

BOWLING_GAME* bowlingGameCreate();
uint8_t playerCanThrow(BOWLING_GAME* the_game, uint8_t current_frame, uint8_t current_player);
void writeDownTheScore(BOWLING_GAME* the_game, uint8_t current_player, uint8_t number_of_pins);

uint8_t isLaneValid(uint8_t number_of_lanes);
uint8_t isPlayerValid(uint8_t number_of_players);
#endif

