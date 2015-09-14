#ifndef _GUI_H
#define _GUI_H
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "../../ball_logic/src/ball.h"
#include "../../stats/src/bowling_game.h"

typedef enum
{
	CONSOLE = 0,
	SDL	= 1
} GUI_TYPE;

extern LANE_CONFIG my_lane_config;

void (*drawKnockedPinsAndTable)(BOWLING_GAME*, uint8_t, KNOCKED_DOWN_PINS);
void (*animateBallMovement)(BOWLING_GAME*, uint8_t, BALL_POSITION);

void initGUI(uint8_t gui);
#endif

