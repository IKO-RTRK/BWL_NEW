#include "gui.h"


static uint8_t drawKnockedPinsAndTable_console(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins);
static uint8_t animateBallMovement_console(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position);

static uint8_t drawKnockedPinsAndTable_SDL(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins);
static uint8_t animateBallMovement_SDL(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position);

LANE_CONFIG my_lane_config;

void initGUI(uint8_t gui)
{
	if (gui == CONSOLE)
	{
		drawKnockedPinsAndTable = NULL;
		animateBallMovement = NULL;
		// configure my_lane_config based on GUI choose (width/length/...)
		
	} else
	{
		// Assign function pointer to adequate function...
		// configure my_lane_config based on GUI choose (width/length/...)
		drawKnockedPinsAndTable = drawKnockedPinsAndTable_SDL;
		animateBallMovement = animateBallMovement_SDL;
	}
}


// CONSOLE GUI START
static uint8_t drawKnockedPinsAndTable_console(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins)
{

}

static uint8_t animateBallMovement_console(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position)
{

}
// CONSOLE GUI END


// SDL GUI START
static uint8_t drawKnockedPinsAndTable_SDL(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins)
{

}

static uint8_t animateBallMovement_SDL(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	return 1;
	
	
	return 0;
}
// SDL GUI END

