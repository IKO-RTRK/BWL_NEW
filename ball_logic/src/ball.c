#include "ball.h"

void initBallLogic(LANE_CONFIG lane_cfg)
{
	lane.width = lane_cfg.width;
	lane.length = lane_cfg.length;	
}

BALL_POSITION rollTheBall(struct player* theplayer, BALL_POSITION current_ball_position)
{
	BALL_POSITION next_ball_position;
	return next_ball_position;
}

KNOCKED_DOWN_PINS knockDownPins(PLAYER* the_player, BALL_POSITION ball_position)
{
	KNOCKED_DOWN_PINS pins;
	uint8_t i;
	pins.number_of_pins = 0;
	for (i = 0 ; i <= NUMBER_OF_PINS - 1; i++)
		pins.pins[i] = 0;
	return pins;
}

