#include "gui.h"

static SDL_Surface* screen = NULL;
static SDL_Surface* ball[2] = {NULL, NULL};  
static SDL_Surface* bowling_lane = NULL; 

static uint8_t drawKnockedPinsAndTable_console(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins);
static uint8_t animateBallMovement_console(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position);

static uint8_t drawKnockedPinsAndTable_SDL(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins);
static uint8_t animateBallMovement_SDL(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position);

static uint8_t printLane(uint8_t i);

LANE_CONFIG my_lane_config;

uint8_t initGUI(uint8_t gui)
{
	if (gui == CONSOLE)
	{
		drawKnockedPinsAndTable = NULL;
		animateBallMovement = NULL;
		// configure my_lane_config based on GUI choose (width/length/...)
		
	} 
	else
	{
		// Assign function pointer to adequate function...
		// configure my_lane_config based on GUI choose (width/length/...)
		drawKnockedPinsAndTable = drawKnockedPinsAndTable_SDL;
		animateBallMovement = animateBallMovement_SDL;

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return 1;

		screen = SDL_SetVideoMode(1200, 900, 32, SDL_DOUBLEBUF); 
		ball[0] = SDL_LoadBMP("../resources/ball1.bmp");
		ball[1] = SDL_LoadBMP("../resources/ball2.bmp");
		bowling_lane = SDL_LoadBMP("../resources/bowling_lane.bmp");

		if (screen == NULL || ball[0] == NULL || ball[1] == NULL || bowling_lane == NULL)
		return 2;

		SDL_WM_SetCaption("Bowling", NULL);

		uint8_t i;
		for (i = 0; i < MAX_LANES; i++)
		{
			if (printLane(i))	
			return 3;
		}
		
		return 0;
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

// i = 0, ..., n
static uint8_t printLane(uint8_t i)
{
	SDL_Rect dstOffset; 

	dstOffset.x = INIT_OFFSET_X + i * TWO_LANES_DISTANCE; 
	dstOffset.y = INIT_OFFSET_Y;

	int8_t k = SDL_BlitSurface(bowling_lane, NULL, screen, &dstOffset);
	int8_t j = SDL_Flip(screen);

	return ((k || j) ? 1 : 0);
}

static uint8_t drawKnockedPinsAndTable_SDL(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins)
{

}

static uint8_t animateBallMovement_SDL(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position)
{
	
	
}

void quit()
{
	SDL_FreeSurface(ball[0]);
	SDL_FreeSurface(ball[1]);
	SDL_FreeSurface(screen);	
	SDL_FreeSurface(bowling_lane);

	SDL_Quit(); 
}
// SDL GUI END

