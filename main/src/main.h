/**
*	@file 	main.h
*	@brief 	 This document contains short description about used macros and enumeration.
*	@author RT-RK
*	@date 	Septembar, 2015
*/
#ifndef _MAIN_H
#define _MAIN_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

#include "../../stats/src/bowling_game.h"
#include "../../player/src/player.h"
#include "../../gui/src/gui.h"
#include "../../ball_logic/src/ball.h"
/**
	Time between two throws in micro secunds.
*/
#define MICRO_TIME_BETWEEN_TWO_ROLLS 	1500000

/**
	Enumeration of errors.
*/
enum 
{
	ERROR_OK	= 0,
	ERROR_USAGE	= 1,
	ERROR_LANES	= 2,
	ERROR_PLAYERS	= 3,
	ERROR_MEMORY	= 4
};


#endif

