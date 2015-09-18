#include "ball.h"
#include <stdlib.h>
#include <math.h>


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

static void isEndOfLane(BALL_POSITION* ball_position)
{
  if (ball_position -> y == lane.length - 1)
  {
    ball_position -> isEndOfLane = true;
  }
}

void initBallLogic(LANE_CONFIG lane_cfg)
{

  lane.width = lane_cfg.width;
  lane.length = lane_cfg.length;
  lane.bumperWidth = lane_cfg.bumperWidth;
}

BALL_POSITION rollTheBall(struct player* the_player, BALL_POSITION current_ball_position)
{
	BALL_POSITION next_ball_position;
	if (isBallOnStartPosition(current_ball_position))
	{
	  next_ball_position.y = 0;
	  uint32_t center = lane.width / 2;
	  uint32_t offset = center / QUALITY_MAX;
	  uint8_t i;
	  for (i = QUALITY_MAX; i > the_player -> quality; i--)
	  {
	    if (the_player -> main_hand == LEFT_HAND)
	    {
	      center -= offset;
	    }
	    else
	    {
	      center += offset;
	    }
	  }
	  
	  setIsStartPosition(&current_ball_position);
	  next_ball_position.isEndOfLane = false;
	  next_ball_position.x = center;
	}
	else
	{  
	  next_ball_position.y = current_ball_position.y + 1;
	  next_ball_position.x = current_ball_position.x;
	  isEndOfLane(&next_ball_position);
	}
	
	return next_ball_position;
}

static double power_f(double x,uint8_t n)
{
	uint8_t i;
	double p = 1;
	for(i=1; i<=n ; i++)
	{
		p *= x;
	}
	return p;
}

static uint8_t howManyToKnockMax(int32_t position)
{

	if ( position - lane.bumperWidth <= -1 ) return 0; // ball went down the left canal
	if ( position + lane.bumperWidth >= lane.width ) return 0; // ball went down the right canal
	double place = (double)position - (double)(lane.width - 1)/2;
	double relative_offset;
	double realValue;
	
	relative_offset=place/(lane.width-2*lane.bumperWidth);


	if ( relative_offset <= 0 ) realValue = 10+23*relative_offset+36*power_f(relative_offset, 2)+36*power_f(relative_offset, 3);  // y = 10+23*x+36*x^2+36*x^3 for -0.5 >= x >= 0
	else realValue = 10-23*relative_offset+36*power_f(relative_offset, 2)-36*power_f(relative_offset, 3);  // y = 10-23*x+36*x^2-36*x^3 for 0 < x <= 0.5
	// function that approximates convention values
	
	//printf("%lf\n\n\n", realValue);

	return (uint8_t)ceil(realValue);
}



static void resetKnockedDownpins(KNOCKED_DOWN_PINS *pins)
{
	uint8_t i;
	
	pins->number_of_pins = 0;
	
	for(i=0; i <= NUMBER_OF_PINS - 1 ; i++)
	{
		pins->pins[i] = 0;
	}
}

KNOCKED_DOWN_PINS knockDownPins(PLAYER* the_player, BALL_POSITION ball_position)
{
	KNOCKED_DOWN_PINS pins;
	uint8_t i, max;
	resetKnockedDownpins(&pins);
	max = howManyToKnockMax((int32_t)ball_position.x);

	if ( max == 0 ) pins.number_of_pins =  0; 
	else pins.number_of_pins = max - ( random() % max );
	//printf("%"PRIu8" ", pins.number_of_pins);

	for(i=0; i < pins.number_of_pins ; i++)
	{
		pins.pins[i] = 1;
	}
	return pins;
}
