#ifndef _GUI_H
#define _GUI_H
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "../../ball_logic/src/ball.h"
#include "../../stats/src/bowling_game.h"
#include "../../include/SDL.h"

#define INIT_OFFSET_X 40
#define INIT_OFFSET_Y 40
#define LANE_WIDTH 110
#define LANE_HEIGHT 508
#define BALL_DIM 30 
#define BALL_MIDDLE 15
#define TWO_LANES_DISTANCE 350

typedef enum
{
	CONSOLE = 0,
	SDL	= 1
} GUI_TYPE;

extern LANE_CONFIG my_lane_config;

uint8_t (*drawKnockedPinsAndTable)(BOWLING_GAME*, uint8_t, KNOCKED_DOWN_PINS);
uint8_t (*animateBallMovement)(BOWLING_GAME*, uint8_t, BALL_POSITION);

uint8_t initGUI(uint8_t gui);
void quit();
#endif

