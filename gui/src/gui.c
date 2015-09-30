/**
 * @file gui.c
 * @brief Document contains short description of used structures and functions 
 * @author RT-RK Ball_logic
 * @date September, 2015
 */

#include "gui.h"

static SDL_Surface* screen = NULL;
static SDL_Surface* ball[2] = {NULL, NULL};  
static SDL_Surface* bowling_lane = NULL; 
static SDL_Surface* pin = NULL; 
static SDL_Surface* table = NULL;
static SDL_Surface* text = NULL;
static SDL_Color textColor = { 255, 255, 255 };

static SDL_Rect offsetForLastPic;///< for testing

static uint16_t prevX[3];
static uint16_t prevY[3];

static void SetCursorPos(int XPos, int YPos);
void initialisation_track_console(TRACK_CONSOLE* t, BOWLING_GAME* the_game);
static void initialisation_pins_console(TRACK_CONSOLE* track);
static void initialisation_lane_console(TRACK_CONSOLE* track);
static void initialisation_table_console(TRACK_CONSOLE* track, BOWLING_GAME* the_game);

void print_lane_console(TRACK_CONSOLE* track);
void print_table_console(TRACK_CONSOLE* track);

TRACK_CONSOLE* track;
char bowling_ball = 'o';
char init_bowling_pins[NUM_OF_PINS] = {[0 ... NUM_OF_PINS-1] = '!'};



uint8_t drawKnockedPinsAndTable_console(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins);
uint8_t animateBallMovement_console(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position);

static uint8_t drawKnockedPinsAndTable_SDL(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins);
static uint8_t animateBallMovement_SDL(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position);
static void printTable (BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins, uint8_t numberOfPlayers);
static uint8_t printLane(uint8_t i);
static void printBall(uint32_t x, uint32_t y, uint8_t lane);
static void showAllPins(uint8_t lane);
static void setBackground();

LANE_CONFIG my_lane_config;

uint8_t initGUI(uint8_t gui)
{
	if (gui == CONSOLE)
	{
		//awKdrawKnockedPinsAndTable = drnockedPinsAndTable_console;
		animateBallMovement = NULL;
		my_lane_config.length=LENGTH_OF_LANE_CONSOLE - START_COLUMN_PINS;
		my_lane_config.width=WIDTH_OF_LANE_CONSOLE-2;

	} 
	else
	{
		// Assign function pointer to adequate function...
		// configure my_lane_config based on GUI choose (width/length/...)
		drawKnockedPinsAndTable = drawKnockedPinsAndTable_SDL;
		animateBallMovement = animateBallMovement_SDL;

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return 1;

		screen = SDL_SetVideoMode(1832, 800, 32, SDL_DOUBLEBUF); 

		setBackground();		
	
		ball[0] = SDL_LoadBMP("../resources/ball1.bmp");
		ball[1] = SDL_LoadBMP("../resources/ball2.bmp");
		bowling_lane = SDL_LoadBMP("../resources/bowling_lane.bmp");
		pin = SDL_LoadBMP("../resources/pin.bmp"); ///<	Load pin image

		if (screen == NULL || ball[0] == NULL || ball[1] == NULL || bowling_lane == NULL || pin == NULL)
		return 2;

		SDL_WM_SetCaption("Bowling", NULL);

		Uint32 colorkey3 = SDL_MapRGB( pin -> format, 255, 255, 255);
		SDL_SetColorKey(pin, SDL_SRCCOLORKEY, colorkey3); ///<	Set pin key color to white

		uint8_t i;
		for (i = 0; i < MAX_LANES; i++)
		{
			if (printLane(i))	
			return 3;
			showAllPins(i);
		}

		Uint32 colorkey1 = SDL_MapRGB( ball[0] -> format, 255, 234, 157);
		SDL_SetColorKey(ball[0], SDL_SRCCOLORKEY, colorkey1);

		Uint32 colorkey2 = SDL_MapRGB( ball[1] -> format, 255, 234, 157);
		SDL_SetColorKey(ball[1], SDL_SRCCOLORKEY, colorkey2);
		
		return 0;
	}
}


// CONSOLE GUI START

static void SetCursorPos(int XPos, int YPos)
{
 	printf("\033[%d;%dH", YPos+1, XPos+1);
}

void initialisation_track_console(TRACK_CONSOLE* t, BOWLING_GAME* the_game)
{
	
	initialisation_pins_console(t);
	initialisation_lane_console(t);
	initialisation_table_console(t, the_game);
}
static void initialisation_lane_console(TRACK_CONSOLE* track)
{
	uint8_t i,j;
	uint8_t current_row;
	uint8_t current_column;
	
	for (i = 0; i < LENGTH_OF_LANE_CONSOLE; i++) 
	{
	  for (j = 0; j < WIDTH_OF_LANE_CONSOLE; j++)
	  {
	    track->table_gui[i][j] = ' ';
	  }
	}
	
	track->ball_prevXpos = FIRST_BALL_POS_COL; 
	track->ball_prevYpos = FIRST_BALL_POS_ROW;

	for (current_row = START_OF_FIRST_TRACK_ROW ; current_row < LENGTH_OF_LANE_CONSOLE; current_row++)
	{
		track->lane_gui[current_row][2] = '|';
		track->lane_gui[current_row][4] = '|';
		track->lane_gui[current_row][12] = '|';
		track->lane_gui[current_row][14] = '|';
	}
    
	track->lane_gui[FIRST_BALL_POS_ROW][FIRST_BALL_POS_COL] = bowling_ball; 
	return;
}

static void initialisation_pins_console(TRACK_CONSOLE* track)
{
    uint8_t current_row, i;
    uint8_t current_column;
    uint8_t counter = NUM_OF_PINS - 1;
    uint8_t tmp = START_OF_FIRST_TRACK_ROW, tmp1;
    uint8_t n = END_COLUMN_PINS;

    for (current_row = END_OF_PINS_ROW; current_row > START_OF_FIRST_TRACK_ROW; current_row--)
    {
	tmp1 = n;
	for (current_column = current_row; current_column >START_OF_FIRST_TRACK_ROW; current_column--)
	{
	    track->lane_gui[tmp][tmp1] = init_bowling_pins[counter--];
	    tmp1-=2;
	}
	tmp++;
	n--;	
    }

	for (i = 0; i < NUM_OF_PINS; i++)
	{
	   track->bowling_pins[i] = '!';
	}

   
    return;
}

static void initialisation_table_console(TRACK_CONSOLE* track, BOWLING_GAME* the_game)
{   
	uint8_t i, j;
	uint8_t diff = 0;
	uint8_t temp = 0;
	char num = '1';

	for (i = 0; i < LENGTH_OF_TABLE_CONSOLE; i++) 
	{
	  for (j = 0; j < WIDTH_OF_TABLE_CONSOLE; j++)
	  {
	    track->table_gui[i][j] = ' ';
	  }
	}
	
	for (i = 0; i < 10; i++)
	{
	  track->table_gui[0][diff] = '|';
	  diff+=4;
	}
	
	
	track->table_gui[0][42] = '|';
	track->table_gui[0][48] = '|';
	
	diff = 2;
	
	for (i = 0; i < 9; i++)
	{
	    track->table_gui[0][diff] = num;
	    num+=1;
	    diff += 4;
	}
	
	track->table_gui[0][38] = '1';
	track->table_gui[0][39] = '0';
	
	track->table_gui[0][44] = 'T';
	track->table_gui[0][45] = 'O';
	track->table_gui[0][46] = 'T';
	
	while(temp < the_game->number_of_players)
	{		
		uint8_t current_column;
		uint8_t tmp1 = START_LANE_ROW;			
		uint8_t counter;
		for (counter = 0; counter < 9; counter++)
		{
			for (current_column = 1; current_column < 4; current_column++) 
			{
				track->table_gui[1 + DIFF_TABLE*temp][tmp1 + current_column] = '-';
				track->table_gui[4 + DIFF_TABLE*temp][tmp1 + current_column] = '-';
			}
			
			tmp1+=4;
		 }
		 
		 for (counter = 0; counter < 2; counter++)
		{
			for (current_column = 1; current_column < 6; current_column++) 
			{
				track->table_gui[1 + DIFF_TABLE*temp][tmp1 + current_column] = '-';
				track->table_gui[4 + DIFF_TABLE*temp][tmp1 + current_column] = '-';
			}
			
			tmp1+=6;
		 }
		
		 uint8_t tmp = START_LANE_COLUMN;		
		 for (counter = 0; counter < 10; counter++)
		 {
			for (current_column = 0; current_column < 2; current_column++) 
			{
				track->table_gui[2 + DIFF_TABLE*temp][tmp] = '|';
				track->table_gui[3 + DIFF_TABLE*temp][tmp] = '|';
			}
			tmp+=4;
		 }

 	       track->table_gui[2 + DIFF_TABLE*temp][42] = '|';	
	       track->table_gui[3 + DIFF_TABLE*temp][42] = '|';
	       track->table_gui[2 + DIFF_TABLE*temp][48] = '|';
	       track->table_gui[3 + DIFF_TABLE*temp][48] = '|';
		
//	  for (i = 1; the_game->players[temp].name[i-1] != '\0'; i++)	
//          {
//	   track->table_gui[5 + DIFF_TABLE*temp][i] =the_game->players[temp].name[i-1];
//	  }
				    
         	temp++;
	}				    
}

void print_lane_console(TRACK_CONSOLE* track)
{
	uint8_t current_row;
	uint8_t current_column;


	for (current_row = 0; current_row < LENGTH_OF_LANE_CONSOLE; current_row++)
	{
		for (current_column = 0; current_column < WIDTH_OF_LANE_CONSOLE; current_column++)
		{

			SetCursorPos( (track->trackID-1) * DIFF_CONSOLE + current_column, current_row + 1);

			printf("%c", track->lane_gui[current_row][current_column]);

		}
	}

	return;
}



void print_table_console(TRACK_CONSOLE* track)
{

	uint8_t current_row;
	uint8_t current_column;
	
	for (current_row = 0 ; current_row < LENGTH_OF_TABLE_CONSOLE ; current_row++) 
	{
	    for (current_column = 0 ; current_column < WIDTH_OF_TABLE_CONSOLE ; current_column++)
	    {
		  SetCursorPos(((track->trackID-1) * DIFF_CONSOLE) + current_column + 16, current_row);
		  printf("%c", track->table_gui[current_row][current_column]);
	    }
	printf("\n");
	}
	
	return;
}



uint8_t drawKnockedPinsAndTable_console(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins)
{
    uint8_t current_row;
    uint8_t current_column;
    uint8_t counter = NUM_OF_PINS - 1;
    uint8_t tmp = START_OF_FIRST_TRACK_ROW, tmp1;
    uint8_t n = END_COLUMN_PINS;
    uint8_t i, temp;
    	
	if ((knocked_down_pins.number_of_pins > 10) || (knocked_down_pins.number_of_pins < 0))
		return 0;
	
	for (i = 0; i < 10; i++)
	  if (knocked_down_pins.pins[i]){
	    track->bowling_pins[i] = 'x';
	 }
    															
    for (current_row = END_OF_PINS_ROW; current_row > START_OF_FIRST_TRACK_ROW; current_row--)				
    {
	tmp1 = n;											
	for (current_column = current_row; current_column >START_OF_FIRST_TRACK_ROW; current_column--)
	{								
	   track->lane_gui[tmp][tmp1] = track->bowling_pins[counter--];	
	    tmp1-=2;				
	}			
	tmp++;			
	n--;					
						
    }
	return 1;
}

uint8_t animateBallMovement_console(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position)
{

	if(ball_position.isStartPosition==0)
	{
		track->lane_gui[track->ball_prevYpos][track->ball_prevXpos] = '.';
		track->ball_prevYpos = ball_position.y;
		track->ball_prevXpos = ball_position.x;
		if(ball_position.isEndOfLane==0)
		{
	  		track->lane_gui[track->ball_prevYpos][track->ball_prevXpos] = 'o';
		}
      	}
	else if(ball_position.isStartPosition==1)
	{
		int num; 		
		for(num=END_OF_PINS_ROW; num<LENGTH_OF_LANE_CONSOLE; num++)
		{
			track->lane_gui[num][FIRST_BALL_POS_COL]=' ';		
		}
		track->lane_gui[FIRST_BALL_POS_ROW][FIRST_BALL_POS_COL]='o';

	}

      return 1;
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
/**
 * @brief Hellper functions for TDD - get position for last picture
 */
SDL_Rect getOffsetForLastPic()
{
  return   offsetForLastPic;
}
/**
 * @brief Drawing pictures on the screen
 * @param 	rect	Offset for picture
 * @param 	pic	Picture
 * @retval	void
 */
static void drawPic(SDL_Rect rect, SDL_Surface* pic)
{
  SDL_BlitSurface(pic, NULL, screen, &rect); ///<	Add pin to the sceen
  SDL_Flip(screen);
  offsetForLastPic = rect; ///< For testing
  //SDL_Sleep(1000);
}


/**
 * @brief 	Function drow pins on lane
 * @param 	lane	Number of lain (lane ID)
 * @param 	knocked_down_pins	Structure who keep data of knocked pins
 * @retval	int8_t	This function returns 0 if successful, or -1 if there was an error.
 */
static int8_t drawPins(uint8_t lane, KNOCKED_DOWN_PINS knocked_down_pins )
{
  printLane(lane); ///< Clean lane
  uint8_t pinNum = NUM_OF_PINS;
  SDL_Rect dstOffset;
 // int8_t numOfPin = NUM_OF_PINS; 
  uint8_t numOfRow;
  uint8_t numOfPinsInRow;
  
  dstOffset.x = INIT_OFFSET_FOR_PINS_X + 3 * OFFSET_FOR_PINS_X + (lane) * TWO_LANES_DISTANCE;
  dstOffset.y = INIT_OFFSET_Y;
  for (numOfRow = 4; numOfRow > 0; numOfRow--)
    {
      for(numOfPinsInRow = numOfRow; numOfPinsInRow > 0; numOfPinsInRow--)
      {
	if(knocked_down_pins.pins[--pinNum] == 1)
	{
	  drawPic(dstOffset, pin); ///<	Add pin to the sceen
	}
	dstOffset.x -= OFFSET_FOR_PINS_X; ///<	Sets  offset for x for next pin
      }
      dstOffset.x = INIT_OFFSET_FOR_PINS_X + (lane) * TWO_LANES_DISTANCE + (5 - numOfRow) * OFFSET_FOR_PINS_X / 2 + (numOfRow - 2) * OFFSET_FOR_PINS_X; ///<	Sets initial offset for x for given row
      dstOffset.y += OFFSET_FOR_PINS_Y; ///<	Sets initial offset for y for given row
    }
 
}

static void printTable (BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins, uint8_t numberOfPlayers)
{	
	
	uint8_t i;
	SDL_Rect dstOffset; 
	SDL_Rect* clip = NULL;

	dstOffset.x = INIT_TABLE_OFFSET_X + (the_game -> lane_number) * TWO_LANES_DISTANCE; 
	dstOffset.y = INIT_OFFSET_Y;
	for( i = 0; i < numberOfPlayers; i++)
	{
		SDL_BlitSurface(table, clip, screen, &dstOffset);
		dstOffset.y += 100;
		SDL_Flip(screen);
	}
	SDL_BlitSurface(text, clip, table, &dstOffset);
	dstOffset.x += 40;
	dstOffset.y += 3;
	SDL_Flip(table);
}

static uint8_t drawKnockedPinsAndTable_SDL(BOWLING_GAME* the_game, uint8_t current_player, KNOCKED_DOWN_PINS knocked_down_pins)
{
  	drawPins(the_game -> lane_number, knocked_down_pins);
	//printTable(the_game, current_player, knocked_down_pins,the_game -> number_of_players);
}

static uint8_t animateBallMovement_SDL(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position)
{
	printBall(ball_position.x, ball_position.y, the_game -> lane_number);
	return 0;
}

static void showAllPins(uint8_t lane)
{
	KNOCKED_DOWN_PINS knocked_pins;

	uint8_t i;
	for (i = 0; i < NUM_OF_PINS; i++)
	{
		knocked_pins.pins[i] = 0;
	} 
	drawPins(lane, knocked_pins);

}


void ballLogic(BALL_POSITION* prev, BALL_POSITION* current, uint8_t lane, uint8_t gui)
{
	if (gui == 1)
	{
		current -> x = INIT_OFFSET_X + current -> x + lane * TWO_LANES_DISTANCE;
	}
	else
	{


	}
	prev -> x = current -> x;
	prev -> y = current -> y;

	
}


static void printBall(uint32_t x, uint32_t y, uint8_t lane)  // x,y - centar lopte
{

	// Pozicija na stazi na kojoj se brise lopta
	SDL_Rect dstOffsetDel; 
	dstOffsetDel.x = INIT_OFFSET_X + prevX[lane] + lane * TWO_LANES_DISTANCE; 
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

static void setBackground()
{
	SDL_Rect screenRect;
	screenRect.x = screenRect.y = 0;
	screenRect.w = screen->w;
	screenRect.h = screen->h;
	Uint32 color = SDL_MapRGB(screen->format, 168, 174, 184);
									
	SDL_FillRect(screen, &screenRect, color);
	SDL_Flip(screen);
}

void quit()
{
	SDL_FreeSurface(ball[0]);
	SDL_FreeSurface(ball[1]);
	SDL_FreeSurface(screen);	
	SDL_FreeSurface(bowling_lane);
	SDL_FreeSurface(pin);
	SDL_Quit(); 
}
// SDL GUI END

