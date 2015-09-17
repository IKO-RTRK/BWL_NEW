#include "player.h"

static int isQualityInBounds(uint8_t quality)
{
	return ((quality >= QUALITY_MIN) && (quality <= QUALITY_MAX));
}

PLAYER* playerCreate()
{
	return (PLAYER*) malloc( sizeof(PLAYER) );
}

void assignPlayerName(PLAYER* player, char* name)
{
	strncpy (player -> name, name, NAME_LENGTH_MAX);
	player -> name[NAME_LENGTH_MAX-1] = '\0';
}

void assignPlayerQuality(PLAYER* player, uint8_t quality)
{
	if (isQualityInBounds (quality))
	{
		player -> quality = quality;
	}
	else
	{
		player -> quality = 1;
	}
}

void assignPlayerMainHand(PLAYER* player, uint8_t main_hand)
{
	if ((main_hand == 0) || (main_hand == 1))
	{
		player -> main_hand = main_hand;
	}
	else
	{
		player -> main_hand = 1;
	}
}
