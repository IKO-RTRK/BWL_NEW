#include "ball.h"

static bool isBallOnStartPosition(BALL_POSITION ball_position)
{
  if (ball_position.isStartPosition)
    return true;
  return false;
}

static void setIsStartPosition(BALL_POSITION* ball_position)
{
  ball_position -> isStartPosition = false;
}

void initBallLogic(LANE_CONFIG lane_cfg)
{

  lane.width = lane_cfg.width;
  lane.length = lane_cfg.length;
}

BALL_POSITION rollTheBall(struct player* the_player, BALL_POSITION current_ball_position)
{
	BALL_POSITION next_ball_position;
	if (isBallOnStartPosition(current_ball_position))
	{
	  next_ball_position.y = 0;
	  int center = lane.width / 2;
	  int offset = center / 10;//QULAITY_MAX;
	  int i;
	  for (i = 10; i > the_player -> quality; i--)
	  {
	    center += offset;
	  }
	  
	  setIsStartPosition(&current_ball_position);
	  next_ball_position.x = center;
	}
	else
	{  
	  next_ball_position.y = current_ball_position.y + 1;
	  next_ball_position.x = current_ball_position.x;
	}
	
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

