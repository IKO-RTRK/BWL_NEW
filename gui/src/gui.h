#ifndef _GUI_H
#define _GUI_H
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "../../ball_logic/src/ball.h"
#include "../../stats/src/bowling_game.h"
#include "../../include/SDL.h"

typedef enum
{
	CONSOLE = 0,
	SDL	= 1
} GUI_TYPE;

extern LANE_CONFIG my_lane_config;

uint8_t (*drawKnockedPinsAndTable)(BOWLING_GAME*, uint8_t, KNOCKED_DOWN_PINS);
uint8_t (*animateBallMovement)(BOWLING_GAME*, uint8_t, BALL_POSITION);

uint8_t initGUI(uint8_t gui);
#endif

