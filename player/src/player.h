#ifndef _PLAYER_H
#define _PLAYER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#define LEFT_HAND 0
#define RIGHT_HAND 1
#define QUALITY_MIN 1
#define QUALITY_MAX 10

	typedef struct player 
	{
		char name[20];
		uint8_t quality;
		uint8_t main_hand;
	} PLAYER;

	PLAYER* playerCreate();

#endif

