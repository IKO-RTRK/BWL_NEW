#ifndef _GUI_H
#define _GUI_H
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "../../ball_logic/src/ball.h"
#include "../../stats/src/bowling_game.h"
#include "../include/SDL.h"

#define INIT_OFFSET_X 40
#define INIT_OFFSET_Y 40
#define LANE_WIDTH 170
#define LANE_HEIGHT 508
#define BALL_DIM 30 
#define BALL_MIDDLE 15
#define TWO_LANES_DISTANCE 350

#define LENGTH_OF_LANE_CONSOLE 35    
#define WIDTH_OF_LANE_CONSOLE 15     
#define LENGTH_OF_TABLE_CONSOLE 37   
#define WIDTH_OF_TABLE_CONSOLE 49    
#define FIRST_BALL_POS_COL 8         
#define FIRST_BALL_POS_ROW 34        
#define NUM_OF_PINS 10		     
#define START_LANE_ROW 0             
#define START_LANE_COLUMN 0         
#define START_COLUMN_PINS 5  
#define END_COLUMN_PINS 11
#define END_OF_PINS_ROW 4	     
#define START_OF_FIRST_TRACK_ROW 0   
#define DIFF_CONSOLE 66
#define DIFF_TABLE 6

typedef enum
{
	CONSOLE = 0,
	SDL	= 1
} GUI_TYPE;

typedef struct track_console
{
	uint8_t trackID;
	uint8_t	ball_prevXpos;
	uint8_t ball_prevYpos;
	char lane_gui[LENGTH_OF_LANE_CONSOLE][WIDTH_OF_LANE_CONSOLE];
	char table_gui[LENGTH_OF_TABLE_CONSOLE][WIDTH_OF_TABLE_CONSOLE];
	char bowling_pins[NUM_OF_PINS];
	
}TRACK_CONSOLE;


extern LANE_CONFIG my_lane_config;

uint8_t (*drawKnockedPinsAndTable)(BOWLING_GAME*, uint8_t, KNOCKED_DOWN_PINS);
uint8_t (*animateBallMovement)(BOWLING_GAME*, uint8_t, BALL_POSITION);

uint8_t initGUI(uint8_t gui);
void quit();
#endif

