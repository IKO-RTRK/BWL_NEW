#ifndef _BALL_H
#define _BALL_H
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "../../player/src/player.h"

#define NUMBER_OF_PINS 10

typedef struct ball_position_struct
{
	uint8_t isEndOfLane;
	uint8_t isStartPosition;
	uint8_t x;
	uint8_t y;
} BALL_POSITION;

typedef struct knocked_down_pins_struct
{
	uint8_t number_of_pins;
	uint8_t pins[NUMBER_OF_PINS];
} KNOCKED_DOWN_PINS;


typedef struct
{
	uint32_t width;
	uint32_t length;
} LANE_CONFIG;

void initBallLogic(LANE_CONFIG lane_cfg);
BALL_POSITION rollTheBall(PLAYER* the_player, BALL_POSITION current_ball_position);
KNOCKED_DOWN_PINS knockDownPins(PLAYER* the_player, BALL_POSITION ball_position);
#endif

