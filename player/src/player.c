#include "player.h"


PLAYER* playerCreate()
{
	return (PLAYER*) malloc( sizeof(PLAYER) );
}

void assignPlayerName(PLAYER* player, char* name)
{
	if(strlen(name) < 1)
	{
		strcpy (player -> name, "Player");
	}	
	else
	{
		strncpy (player -> name, name, NAME_LENGTH_MAX);
		player -> name[NAME_LENGTH_MAX-1] = '\0';
	}
}

