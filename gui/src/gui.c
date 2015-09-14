#include "gui.h"


static void drawKnockedPinsAndTable_console(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins);
static void animateBallMovement_console(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position);

static void drawKnockedPinsAndTable_SDL(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins);
static void animateBallMovement_SDL(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position);

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
	}
}


// CONSOLE GUI START
static void drawKnockedPinsAndTable_console(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins)
{

}

static void animateBallMovement_console(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position)
{

}
// CONSOLE GUI END


// SDL GUI START
static void drawKnockedPinsAndTable_SDL(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins)
{

}

static void animateBallMovement_SDL(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position)
{

}
// SDL GUI END

