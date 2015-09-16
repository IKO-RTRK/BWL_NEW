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
#define NAME_LENGTH_MAX 20

	typedef struct player 
	{
		char name[NAME_LENGTH_MAX];
		uint8_t quality;
		uint8_t main_hand;
	} PLAYER;

	PLAYER* playerCreate();
	void assignPlayerName(PLAYER* p, char* name);
	void assignPlayerQuality(PLAYER* p, uint8_t quality);
	void assignPlayerMainHand(PLAYER* p, uint8_t main_hand);
	void increaseQuality (PLAYER* p);
	void decreaseQuality (PLAYER* p);

#endif

