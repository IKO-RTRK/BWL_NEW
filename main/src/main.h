/**
	@file 	main.h
	@brief 	Dokument sadrzi kratak opis koristenih makroa i koristene enumeracije.
	@author RT-RK
	@date 	Septembar, 2015
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
	Vrijeme izmedju dva bacanja kugle izrazeno u mikro sekundama
*/
#define MICRO_TIME_BETWEEN_TWO_ROLLS 	1500000

/**
	Enumeracija errora.
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

