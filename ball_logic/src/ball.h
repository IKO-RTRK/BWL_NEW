/**
 * @file ball.h
 * @brief Document contains short description of used structures and functions 
 * @author RT-RK Ball_logic
 * @date September, 2015
 */

#ifndef _BALL_H
#define _BALL_H
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#include "../../player/src/player.h"
#include "../../stats/src/bowling_game.h"
/*!
  Number of pins in lane when game starts
 */
#define NUMBER_OF_PINS 10

/*!	\struct ball_position_struct
  Structure contains information about ball position
 */

typedef struct ball_position_struct
{
	uint8_t isEndOfLane;		///<	Did the ball reached the end of lane, have values 0 or 1 
	uint8_t isStartPosition;	///<	Is the ball at the start of lane, have values 0 or 1  
	uint32_t x;			///<	x coordinate current value for ball, represents distance between ball and central line of lane 
	uint32_t y;			///<	y coordinate current value for ball, represents distance between ball and the beginning of lane
} BALL_POSITION;


/*!	\struct knocked_down_pins_struct
  Structure contains information about pins on the lane
 */
typedef struct knocked_down_pins_struct
{
	uint8_t number_of_pins;		///<	Number of knocked pins in a throw
	uint8_t pins[NUMBER_OF_PINS];	///<	Array of pins, array element is 0 if a matching pin has been knocked
} KNOCKED_DOWN_PINS;

/*!	\struct LANE_CONFIG
  Structure contains information about lane size
 */
typedef struct
{
	int32_t width;		///<	Lane width
	int32_t length;		///<	Lane length
	int32_t bumperWidth;	///<	Bumper width
} LANE_CONFIG;

LANE_CONFIG lane;	///<	Structure in which are informations about lane dimensions

/**
 * @brief 	Function define dimensions of lanes used in game.
 * 			Values of parameter \a lane_cfg are assigned to global \ref LANE_CONFIG 
 * @param 	lane_cfg	Structure with lane information
 * @retval	void
 */
void initBallLogic(LANE_CONFIG lane_cfg);

/**
 * @brief 	Function which determinates next ball position on lane
 * @param 	*the_player	Information about current \a player who play on lane
 * @param 	current_ball_position	Information about current ball position on lane 
 * @retval 	BALL_POSITION Function returns structure with information of ball new position
 */
BALL_POSITION rollTheBall(PLAYER* the_player, BALL_POSITION current_ball_position);

/**
 * @brief 	Function implements knocking down pins
 * @param 	*the_player	Information about current player who play on lane
 * @param 	ball_position	Information of ball position immediately before knocking pins
 * @retval	KNOCKED_DOWN_PINS Function returns structure with information which and how many pins are koncked 
 */
KNOCKED_DOWN_PINS knockDownPins(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position);
#endif

