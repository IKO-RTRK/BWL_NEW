#include "../../unity/unity_fixture.h"
#include "../src/gui.h"
#include "../include/SDL.h"
#include "../../stats/src/bowling_game.h"

BOWLING_GAME bg1,bg2;
BALL_POSITION bp1, bp2;
SDL_Rect sdlRect;

TRACK_CONSOLE* track;
BOWLING_GAME* game;
BALL_POSITION ball;

KNOCKED_DOWN_PINS knocked_pins;


TEST_GROUP(SDLDrawKnockedPinsTest);
TEST_GROUP(SDLDrawTableTest);
TEST_GROUP(SDLAnimationTest);
TEST_GROUP(ConsoleAnimationTest);

TEST_GROUP_RUNNER(SDLDrawKnockedPinsTest)
{
	//RUN_TEST_CASE(SDLDrawKnockedPinsTest, Test1);
	//RUN_TEST_CASE(SDLDrawKnockedPinsTest, TestXOffset);
	//RUN_TEST_CASE(SDLDrawKnockedPinsTest, TestYOffset);
	//RUN_TEST_CASE(SDLDrawKnockedPinsTest, TestForXAndYOffsetForRowOneAndTwo);

}

TEST_GROUP_RUNNER(SDLDrawTableTest)
{
  RUN_TEST_CASE(SDLDrawTableTest, Test1);
  RUN_TEST_CASE(SDLDrawTableTest, TestYOffset);
}

TEST_GROUP_RUNNER(SDLAnimationTest)
{
//	RUN_TEST_CASE(SDLAnimationTest, Test1);
//	RUN_TEST_CASE(SDLAnimationTest, Test2);
//	RUN_TEST_CASE(SDLAnimationTest, BMP_Load);
//	RUN_TEST_CASE(SDLAnimationTest, Animation);
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
	RUN_TEST_CASE(ConsoleAnimationTest, animateBallMovementOnePositionForwardPrevPosCheck);
	RUN_TEST_CASE(ConsoleAnimationTest, animateBallMovementOnePositionForwardNextPosCheck);
	RUN_TEST_CASE(ConsoleAnimationTest, animateBallMovementForwardUntillTheEndPosition);
	RUN_TEST_CASE(ConsoleAnimationTest, animateBallMovementForwardUntillTheEndPositionAndRestart);
	RUN_TEST_CASE(ConsoleAnimationTest, drawTableConsole);
}

TEST_SETUP(SDLDrawTableTest)
{
  initGUI(SDL);
  bg1.lane_number = 1;
}

TEST_SETUP(SDLDrawKnockedPinsTest)
{
   initGUI(SDL);
   bg1.lane_number = 1;
	
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
	
	ball.isStartPosition=1;
	ball.isEndOfLane=0;
	ball.y=0;
      	ball.x=FIRST_BALL_POS_COL;
	
	
	initialisation_track_console(track, game);
	uint8_t i;

	knocked_pins.number_of_pins = 0;
	for (i = 0; i < NUM_OF_PINS; i++)
	{
	  knocked_pins.pins[i] = 0;
	} 
	
}

TEST_TEAR_DOWN(SDLDrawTableTest)
{
  
}

TEST_TEAR_DOWN(SDLDrawKnockedPinsTest)
{
}

TEST_TEAR_DOWN(SDLAnimationTest)
{
}

TEST_TEAR_DOWN(ConsoleAnimationTest)
{
	free(track);
	free(game);

}


// Prvi test
TEST(SDLDrawTableTest, Test1)
{
  bg1.number_of_players = 1;
  drawKnockedPinsAndTable(&bg1, 1, knocked_pins);
  sdlRect = getOffsetForLastPic();
  TEST_ASSERT_EQUAL(sdlRect.x, INIT_TABLE_OFFSET_X + 1 * TWO_LANES_DISTANCE);
  TEST_ASSERT_EQUAL(sdlRect.y, INIT_OFFSET_Y);
}
// Drugi test
TEST(SDLDrawTableTest, TestYOffset)
{
  bg1.number_of_players = 2;
  drawKnockedPinsAndTable(&bg1, 1, knocked_pins);
  sdlRect = getOffsetForLastPic();
  TEST_ASSERT_EQUAL(sdlRect.x, INIT_TABLE_OFFSET_X + 1 * TWO_LANES_DISTANCE);
  TEST_ASSERT_EQUAL(sdlRect.y, INIT_OFFSET_Y + TABLE_OFFSET_Y);
}
// Prvi test
TEST(SDLDrawKnockedPinsTest, Test1)
{
  knocked_pins.number_of_pins = 5;
  knocked_pins.pins[6] = 1;
  drawKnockedPinsAndTable(&bg1, 1, knocked_pins);
  sdlRect = getOffsetForLastPic();
  TEST_ASSERT_EQUAL(sdlRect.x, INIT_OFFSET_FOR_PINS_X + 1 * TWO_LANES_DISTANCE);
  TEST_ASSERT_EQUAL(sdlRect.y, INIT_OFFSET_Y);
   
  knocked_pins.pins[6] = 0;
}
// Drugi test
TEST(SDLDrawKnockedPinsTest, TestXOffset)
{
  knocked_pins.pins[9] = 1;
  bg1.lane_number = 1;
  drawKnockedPinsAndTable(&bg1, 1, knocked_pins);
  sdlRect = getOffsetForLastPic();
  TEST_ASSERT_EQUAL(sdlRect.x, INIT_OFFSET_FOR_PINS_X + 1 * TWO_LANES_DISTANCE + 3 * OFFSET_FOR_PINS_X);
  
  knocked_pins.pins[9] = 0;
}
// Treci test
TEST(SDLDrawKnockedPinsTest, TestYOffset)
{
  knocked_pins.pins[3] = 1;
  bg1.lane_number = 1;
  drawKnockedPinsAndTable(&bg1, 1, knocked_pins);
  sdlRect = getOffsetForLastPic();
  TEST_ASSERT_EQUAL(sdlRect.y, 1 * OFFSET_FOR_PINS_Y + INIT_OFFSET_Y);
  
  knocked_pins.pins[3] = 0;
}
// Cetvrti test
TEST(SDLDrawKnockedPinsTest, TestForXAndYOffsetForRowOneAndTwo)
{
  knocked_pins.pins[2] = 1;
  bg1.lane_number = 1;
  drawKnockedPinsAndTable(&bg1, 1, knocked_pins);
  sdlRect = getOffsetForLastPic();
  TEST_ASSERT_EQUAL(sdlRect.y, 2 * OFFSET_FOR_PINS_Y + INIT_OFFSET_Y);
  TEST_ASSERT_EQUAL(sdlRect.x, INIT_OFFSET_FOR_PINS_X + 1 * TWO_LANES_DISTANCE  + 2 * OFFSET_FOR_PINS_X / 2 + 1 * OFFSET_FOR_PINS_X);
  
  knocked_pins.pins[0] = 1;
  bg1.lane_number = 1;
  drawKnockedPinsAndTable(&bg1, 1, knocked_pins);
  sdlRect = getOffsetForLastPic();
  TEST_ASSERT_EQUAL(sdlRect.y, 3 * OFFSET_FOR_PINS_Y + INIT_OFFSET_Y);
  TEST_ASSERT_EQUAL(sdlRect.x, INIT_OFFSET_FOR_PINS_X + 1 * TWO_LANES_DISTANCE + 0 * OFFSET_FOR_PINS_X + 3 * OFFSET_FOR_PINS_X / 2);
  
  knocked_pins.pins[0] = 0;
  knocked_pins.pins[2] = 0;
}
// Prvi test
TEST(SDLAnimationTest, Test1)
{
	bp1.x = 5;
	bp1.y = 5;
	
	bp2.x = 6;
	bp2.y = 6;

	ballLogic(&bp1, &bp2, 0, 1);

	TEST_ASSERT_EQUAL(bp1.x, bp2.x);
	TEST_ASSERT_EQUAL(bp1.y, bp2.y);
}

// Drugi test
TEST(SDLAnimationTest, Test2)
{
	bp1.x = 5;
	bp1.y = 5;
	
	bp2.x = 6;
	bp2.y = 6;

	ballLogic(&bp1, &bp2, 1, 1);

	TEST_ASSERT_EQUAL(bp2.x, INIT_OFFSET_X + 6 + 1 * TWO_LANES_DISTANCE);
}

// Drugi test
TEST(SDLAnimationTest, BMP_Load)
{
	BALL_POSITION a, b;
	ballLogic(&a, &b, 0, 1);

	TEST_ASSERT_EQUAL(a.x, b.x);
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
	   

	TEST_ASSERT_TRUE(drawKnockedPinsAndTable_console(game, 1, knocked_pins));
	
}

TEST(ConsoleAnimationTest, drawKnockedPinsOverride)
{
	
	knocked_pins.number_of_pins = 15;	
	TEST_ASSERT_EQUAL(0, drawKnockedPinsAndTable_console(game, 1, knocked_pins));
}

TEST(ConsoleAnimationTest, drawKnockedPinsNegative)
{
	knocked_pins.number_of_pins = -5;;
	TEST_ASSERT_EQUAL(0, drawKnockedPinsAndTable_console(game, 1, knocked_pins));

}

TEST(ConsoleAnimationTest, drawKnockedPinsAll)
{
		
	knocked_pins.number_of_pins = 10;
	TEST_ASSERT_EQUAL(1, drawKnockedPinsAndTable_console(game, 1, knocked_pins));
}

TEST(ConsoleAnimationTest, drawKnockedPinsCheckPosition)
{
	system("clear");
	knocked_pins.number_of_pins = 1;
	knocked_pins.pins[0] = 1;
	drawKnockedPinsAndTable_console(game, 1, knocked_pins);
	print_lane_console(track);
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
	drawKnockedPinsAndTable_console(game, 1, knocked_pins);
	//print_lane_console(track);
	for (i = 0; i < 10; i++)
	{
	  if(track->bowling_pins[i] == 'x')
		counter++;
	}
	system("clear");
	print_lane_console(track);	
	TEST_ASSERT_EQUAL(4, counter);
}


TEST(ConsoleAnimationTest, animateBallMovementStartPosition)
{ 	
  
      animateBallMovement_console(game,1,ball);
	system("clear");
	print_lane_console(track);
      TEST_ASSERT_EQUAL('o', track->lane_gui[FIRST_BALL_POS_ROW][FIRST_BALL_POS_COL]);
}

TEST(ConsoleAnimationTest, animateBallMovementOnePositionForwardPrevPosCheck)
{
      ball.isStartPosition=0;
      ball.y=FIRST_BALL_POS_ROW-1;
      ball.x=FIRST_BALL_POS_COL;
      animateBallMovement_console(game,1,ball);
      system("clear");
      print_lane_console(track);
      TEST_ASSERT_EQUAL('.', track->lane_gui[FIRST_BALL_POS_ROW][FIRST_BALL_POS_COL]);

  
}

TEST(ConsoleAnimationTest, animateBallMovementOnePositionForwardNextPosCheck)
{
      system("clear");  
      ball.isStartPosition=0;
      ball.y=FIRST_BALL_POS_ROW-1;
      ball.x=FIRST_BALL_POS_COL;
      animateBallMovement_console(game,1,ball);
      system("clear");
      print_lane_console(track);
      TEST_ASSERT_EQUAL('o', track->lane_gui[FIRST_BALL_POS_ROW-1][FIRST_BALL_POS_COL]);

  
}

TEST(ConsoleAnimationTest, animateBallMovementForwardUntillTheEndPosition)
{
      system("clear");
      ball.isStartPosition=0;
      ball.x=FIRST_BALL_POS_COL;
      for(ball.y=FIRST_BALL_POS_ROW-1 ; ball.y >= END_OF_PINS_ROW-1 ;ball.y=ball.y-1)
      {  
	if(ball.y==END_OF_PINS_ROW-1)
	{
	  ball.isEndOfLane=1;
	}
	animateBallMovement_console(game,1,ball);

      }
      ball.isEndOfLane=1;
      print_lane_console(track);
      TEST_ASSERT_EQUAL('.', track->lane_gui[END_OF_PINS_ROW][FIRST_BALL_POS_COL]);

  
}

TEST(ConsoleAnimationTest, animateBallMovementForwardUntillTheEndPositionAndRestart)
{

        ball.isStartPosition=0;
	ball.isEndOfLane=0;
        ball.x=FIRST_BALL_POS_COL;
        for(ball.y=FIRST_BALL_POS_ROW-1 ; ball.y >= END_OF_PINS_ROW-1 ;ball.y=ball.y-1)
      {  
	if(ball.y==END_OF_PINS_ROW-1)
	{
	  ball.isEndOfLane=1;
	}
	animateBallMovement_console(game,1,ball);

      }
        ball.isStartPosition=1;
	ball.isEndOfLane=0;
	ball.y=0;
	ball.x=FIRST_BALL_POS_COL;
      
	animateBallMovement_console(game,1,ball);
  system("clear");	
	print_lane_console(track);
	TEST_ASSERT_EQUAL('o', track->lane_gui[FIRST_BALL_POS_ROW][FIRST_BALL_POS_COL]);

        
}

// Test provjera ispisa tabele 
TEST(ConsoleAnimationTest, drawTableConsole)
{
	system("clear");
	TEST_ASSERT_EQUAL('|', track->table_gui[0][0]);
}


