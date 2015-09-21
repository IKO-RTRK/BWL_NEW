#include "../../unity/unity_fixture.h"
#include "../src/gui.h"
#include "../include/SDL.h"

BOWLING_GAME bg1, bg2;
BALL_POSITION bp1, bp2;

TRACK_CONSOLE* track;
BOWLING_GAME* game;
BALL_POSITION* ball;

KNOCKED_DOWN_PINS knocked_pins;


TEST_GROUP(SDLAnimationTest);
TEST_GROUP(ConsoleAnimationTest);

TEST_GROUP_RUNNER(SDLAnimationTest)
{
//	RUN_TEST_CASE(SDLAnimationTest, SDL_Init);
//	RUN_TEST_CASE(SDLAnimationTest, BMP_Load);
	//RUN_TEST_CASE(SDLAnimationTest, Animation);
}

TEST_GROUP_RUNNER(ConsoleAnimationTest)
{
	RUN_TEST_CASE(ConsoleAnimationTest, drawKnockedPinsNone);
	RUN_TEST_CASE(ConsoleAnimationTest, drawKnockedPinsAll);
	RUN_TEST_CASE(ConsoleAnimationTest, drawKnockedPinsNegative);
	RUN_TEST_CASE(ConsoleAnimationTest, drawKnockedPinsOverride);
	RUN_TEST_CASE(ConsoleAnimationTest, drawKnockedPinsCheckPosition);
	RUN_TEST_CASE(ConsoleAnimationTest, drawKnockedPinsCheckPosition1);
	
	RUN_TEST_CASE(ConsoleAnimationTest, animateBallMovementStartPosition);
	RUN_TEST_CASE(ConsoleAnimationTest, animateBallMovementOnePositionForwardPrevPosCheck)

}

TEST_SETUP(SDLAnimationTest)
{
	
}

TEST_SETUP(ConsoleAnimationTest)
{
	track = (TRACK_CONSOLE*)calloc(1, sizeof(TRACK_CONSOLE));
	track->trackID = 1;
	game = (BOWLING_GAME*)calloc(1,sizeof(BOWLING_GAME));
	game->lane_number = 1;
	game->number_of_players = 1;
	ball = (BALL_POSITION*)calloc(1,sizeof(BALL_POSITION));
	ball->isStartPosition=1;
	ball->isEndOfLane=0;
	
	
	initialisation_track_console(track, game);
	uint8_t i;

	knocked_pins.number_of_pins = 0;
	for (i = 0; i < NUM_OF_PINS; i++)
	{
	  knocked_pins.pins[i] = 0;
	} 
	
}

TEST_TEAR_DOWN(SDLAnimationTest)
{
}

TEST_TEAR_DOWN(ConsoleAnimationTest)
{
	free(track);
	free(game);
	free(ball);
}

// Prvi test - SDL inicijalizacija
TEST(SDLAnimationTest, SDL_Init)
{
	TEST_ASSERT_EQUAL(0, initGUI(SDL));
}

// Drugi test - Ucitavanje resursa
TEST(SDLAnimationTest, BMP_Load)
{
	TEST_ASSERT_EQUAL(0, initGUI(SDL));
}

// Treci test - Animacija
TEST(SDLAnimationTest, Animation)
{
	initGUI(SDL);
	bp1.x = 35;
	bp2.x = 70;
	bg1.lane_number = 0;
	bg2.lane_number = 2;
	uint32_t i;
	for (i = 0; i < 420; i++)
	{	
		SDL_Delay(10);
		bp1.y = i;
		bp2.y = i;
		animateBallMovement(&bg1, 0, bp1);
		animateBallMovement(&bg2, 0, bp2);
	}
		
	knocked_pins.pins[0] = 1;
	knocked_pins.pins[1] = 1;

	drawKnockedPinsAndTable(&bg2, 0, knocked_pins);

	knocked_pins.pins[0] = 0;
	knocked_pins.pins[1] = 0;
	knocked_pins.pins[2] = 1;
	knocked_pins.pins[3] = 1;

	drawKnockedPinsAndTable(&bg1, 0, knocked_pins);
	SDL_Delay(5000);
	quit();
	TEST_ASSERT_EQUAL(0, 0);
}


//Prvi test - Console gui
TEST(ConsoleAnimationTest, drawKnockedPinsNone)
{	
	   
	
	TEST_ASSERT_TRUE(drawKnockedPinsAndTable_console(game, 1, knocked_pins, track));
	
}

TEST(ConsoleAnimationTest, drawKnockedPinsOverride)
{
	
	knocked_pins.number_of_pins = 15;	
	TEST_ASSERT_EQUAL(0, drawKnockedPinsAndTable_console(game, 1, knocked_pins, track));
}

TEST(ConsoleAnimationTest, drawKnockedPinsNegative)
{
	knocked_pins.number_of_pins = -5;;
	TEST_ASSERT_EQUAL(0, drawKnockedPinsAndTable_console(game, 1, knocked_pins, track));

}

TEST(ConsoleAnimationTest, drawKnockedPinsAll)
{
	knocked_pins.number_of_pins = 10;
	TEST_ASSERT_EQUAL(1, drawKnockedPinsAndTable_console(game, 1, knocked_pins, track));
}

TEST(ConsoleAnimationTest, drawKnockedPinsCheckPosition)
{
	system("clear");
	knocked_pins.number_of_pins = 1;
	knocked_pins.pins[0] = 1;
	drawKnockedPinsAndTable_console(game, 1, knocked_pins, track);
	print_lane_console();
	TEST_ASSERT_EQUAL('x',track->lane_gui[3][8]);
}

TEST(ConsoleAnimationTest, drawKnockedPinsCheckPosition1)
{
	uint8_t i, counter = 0;
	system("clear");
	knocked_pins.number_of_pins = 1;
	knocked_pins.pins[0] = 1;
 	knocked_pins.pins[1] = 1;
	knocked_pins.pins[2] = 1;
	knocked_pins.pins[3] = 1;
	drawKnockedPinsAndTable_console(game, 1, knocked_pins, track);
	print_lane_console(track);
	for (i = 0; i < 10; i++)
	{
	  if(track->bowling_pins[i] == 'x')
		counter++;
	}
	TEST_ASSERT_EQUAL(4, counter);
}


TEST(ConsoleAnimationTest, animateBallMovementStartPosition)
{ 	
  
      animateBallMovement_console(game,1,*ball,track);
      TEST_ASSERT_EQUAL('o', track->lane_gui[FIRST_BALL_POS_ROW][FIRST_BALL_POS_COL]);
}

TEST(ConsoleAnimationTest, animateBallMovementOnePositionForwardPrevPosCheck)
{
      ball->isStartPosition=0;
      ball->y=FIRST_BALL_POS_ROW-1;
      ball->x=FIRST_BALL_POS_COL;
      animateBallMovement_console(game,1,*ball,track);
      system("clear");
      print_lane_console(track);
      TEST_ASSERT_EQUAL('.', track->lane_gui[FIRST_BALL_POS_ROW][FIRST_BALL_POS_COL]);

  
}


