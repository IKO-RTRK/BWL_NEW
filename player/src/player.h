#ifndef _PLAYER_H
#define _PLAYER_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct player 
{
	char name[20];
} PLAYER;

PLAYER* playerCreate();
#endif

