#include "gui.h"

static SDL_Surface* screen = NULL;
static SDL_Surface* ball[2] = {NULL, NULL};  
static SDL_Surface* bowling_lane = NULL; 

static uint16_t prevX[3];
static uint16_t prevY[3];

static uint8_t drawKnockedPinsAndTable_console(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins);
static uint8_t animateBallMovement_console(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position);

static uint8_t drawKnockedPinsAndTable_SDL(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins);
static uint8_t animateBallMovement_SDL(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position);

static uint8_t printLane(uint8_t i);
static void printBall(uint32_t x, uint32_t y, uint8_t lane);

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

		Uint32 colorkey1 = SDL_MapRGB( ball[0] -> format, 255, 234, 157);
		SDL_SetColorKey(ball[0], SDL_SRCCOLORKEY, colorkey1);

		Uint32 colorkey2 = SDL_MapRGB( ball[1] -> format, 255, 234, 157);
		SDL_SetColorKey(ball[1], SDL_SRCCOLORKEY, colorkey2);
		
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
	printBall(ball_position.x, ball_position.y, the_game -> lane_number);
	return 0;
}

static void printBall(uint32_t x, uint32_t y, uint8_t lane)  // x,y - centar lopte
{

	// Pozicija na stazi na kojoj se brise lopta
	SDL_Rect dstOffsetDel; 
	dstOffsetDel.x = INIT_OFFSET_X + prevX[lane] + (lane) * TWO_LANES_DISTANCE; 
	dstOffsetDel.y = INIT_OFFSET_Y + LANE_HEIGHT - BALL_DIM - prevY[lane];

	SDL_Rect srcOffsetDel;

	srcOffsetDel.w = BALL_DIM; 
	srcOffsetDel.h = BALL_DIM;
	srcOffsetDel.x = prevX[lane]; 
	srcOffsetDel.y = LANE_HEIGHT - BALL_DIM - prevY[lane];
	// Brisanje prethodno iscrtane lopte
	if (y != 0)
	{
		SDL_BlitSurface(bowling_lane, &srcOffsetDel, screen, &dstOffsetDel);
	}
	// Pozicija na stazi na koju se stavlja lopta
	SDL_Rect dstOffset; 
	dstOffset.x = INIT_OFFSET_X + x + (lane) * TWO_LANES_DISTANCE; 
	dstOffset.y = INIT_OFFSET_Y + LANE_HEIGHT - BALL_DIM - y;

	SDL_Surface* tmp = (y % 30 == 0) ? ball[0] : ball[1];

	SDL_BlitSurface(tmp, NULL, screen, &dstOffset);

	SDL_Flip(screen);

	prevX[lane] = x;
	prevY[lane] = y;
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

