#include "ball.h"

void initBallLogic(LANE_CONFIG lane_cfg)
{
  lane.width = lane_cfg.width;
  lane.length = lane_cfg.length;
}

BALL_POSITION rollTheBall(struct player* theplayer, BALL_POSITION current_ball_position)
{
	BALL_POSITION next_ball_position;
	next_ball_position.x = 0;//current_ball_position.coeff * current_ball_position.y + current_ball_position.x;
	return next_ball_position;
}

KNOCKED_DOWN_PINS knockDownPins(PLAYER* the_player, BALL_POSITION ball_position)
{
	KNOCKED_DOWN_PINS pins;
	return pins;
}

