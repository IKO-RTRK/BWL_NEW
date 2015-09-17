#include "../../unity/unity_fixture.h"
#include "../src/ball.h"
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>

#include "../../player/src/player.h"

uint32_t* expected;
uint32_t* positions;

PLAYER player;
BALL_POSITION position;
BALL_POSITION ball_pos;
BALL_POSITION ball_pos_next;

KNOCKED_DOWN_PINS pins;

static void fillExpectedArray(uint32_t element)
{
	expected = (uint32_t*) calloc(lane.length, sizeof(uint32_t));
	int i;
	for (i = 0; i < lane.length; i++)
	{
		expected[i] = element;
	}
}

static void initialiseArray()
{
	positions = (uint32_t*) calloc(lane.length, sizeof(uint32_t));
}

static void addPositionToArray(int position)
{
    ball_pos_next = rollTheBall(&player, ball_pos);
    positions[position] = ball_pos_next.x;
    ball_pos.x = ball_pos_next.x;
    ball_pos.y = ball_pos_next.y;
    ball_pos.isStartPosition = ball_pos_next.isStartPosition;
}

static void freeArrays()
{
	free(expected);
	free(positions);
}

TEST_GROUP(knockDownPins);
TEST_GROUP(RollTheBallTests);

TEST_GROUP_RUNNER(RollTheBallTests)
{
    RUN_TEST_CASE(RollTheBallTests, IsBallOnStartPosition);
    RUN_TEST_CASE(RollTheBallTests, IsStartPositionNotTrue);
    RUN_TEST_CASE(RollTheBallTests, MakeOffsetOnStartLine);
    RUN_TEST_CASE(RollTheBallTests, OffsetFromCentralLine);
    RUN_TEST_CASE(RollTheBallTests, StraightLineTest);
    RUN_TEST_CASE(RollTheBallTests, OffsetStraightLineTest);
    RUN_TEST_CASE(RollTheBallTests, IsEndOfLine);
    RUN_TEST_CASE(RollTheBallTests, CheckEndOfLineOnStart);
}

TEST_GROUP_RUNNER(knockDownPins)
{
	RUN_TEST_CASE(knockDownPins, BallInLeftCanal);
	RUN_TEST_CASE(knockDownPins, BallInRightCanal);
	RUN_TEST_CASE(knockDownPins, BallAlmostInLeftCanal);
	RUN_TEST_CASE(knockDownPins, BallAlmostInRightCanal);
	RUN_TEST_CASE(knockDownPins, BallHitsCentre);
	RUN_TEST_CASE(knockDownPins, BallInMiddleOfLeftHalf);
	RUN_TEST_CASE(knockDownPins, BallInMiddleOfRightHalf);
	RUN_TEST_CASE(knockDownPins, BallAlmostHitCentreLeft);
	RUN_TEST_CASE(knockDownPins, BallAlmostHitCentreRight);
}

TEST_SETUP(RollTheBallTests)
{
    LANE_CONFIG lane2;
    lane2.width = 43;
    lane2.length = 50;
    initBallLogic(lane2);
}

TEST_TEAR_DOWN(RollTheBallTests)
{
	
}

extern LANE_CONFIG lane;

TEST_SETUP(knockDownPins)
{
	uint8_t i;
	lane.width = 13;
	lane.bumperWidth = 3;
	lane.length = 40;

	for(i = 0; i <= NUMBER_OF_PINS - 1; i++)
	{
		pins.pins[i] = 0;
	}
	pins.number_of_pins = 0;
}

TEST_TEAR_DOWN(knockDownPins)
{
	
}

// ==========================================================================================

TEST(RollTheBallTests, IsBallOnStartPosition)
{
  ball_pos.isStartPosition = true;
  ball_pos_next.y = 5;
  ball_pos_next = rollTheBall(&player, ball_pos);
  TEST_ASSERT_EQUAL_UINT32(0, ball_pos_next.y);
}

TEST(RollTheBallTests, IsStartPositionNotTrue)
{
  ball_pos.isStartPosition = false;
  ball_pos_next = rollTheBall(&player, ball_pos);
  TEST_ASSERT_NOT_EQUAL(0, ball_pos_next.y);
}

TEST(RollTheBallTests, MakeOffsetOnStartLine)
{
  player.quality = 8;
  
  ball_pos.isStartPosition = true;
  ball_pos_next = rollTheBall(&player, ball_pos);
  TEST_ASSERT_EQUAL_UINT32(25, ball_pos_next.x);
}

TEST(RollTheBallTests, OffsetFromCentralLine)
{
  player.quality = 6;
  
  ball_pos.isStartPosition = false;
  ball_pos.x = 29;
  ball_pos.y = 3;
  ball_pos_next = rollTheBall(&player, ball_pos);
  TEST_ASSERT_EQUAL_UINT32(29, ball_pos_next.x);
}

TEST(RollTheBallTests, IsEndOfLine)
{
  player.quality = 9;
  ball_pos.x = 21;
  ball_pos.y = lane.length - 2;
  ball_pos.isStartPosition = false;
  //ball_pos.isEndOfLane = false;
  
  ball_pos_next = rollTheBall(&player, ball_pos);
  TEST_ASSERT_TRUE(ball_pos_next.isEndOfLane == true);
}


TEST(RollTheBallTests, CheckEndOfLineOnStart)
{
  player.quality = 9;
  ball_pos.x = 21;
  ball_pos.isStartPosition = true;
  
  ball_pos_next = rollTheBall(&player, ball_pos);
  TEST_ASSERT_TRUE(ball_pos_next.isEndOfLane == false);
}

TEST(RollTheBallTests, StraightLineTest)
{
  int i;
  
  fillExpectedArray(21);
  
  player.quality = 10;
  
  initialiseArray();
  ball_pos.isStartPosition = true;
  for(i = 0;i < lane.length;i++)
  {
      addPositionToArray(i);
  }
  
  TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, positions, lane.length);
  
  freeArrays();
}

TEST(RollTheBallTests, OffsetStraightLineTest)
{
	int i;
	
	fillExpectedArray(27);
	
	player.quality = 7;
	initialiseArray();
	
	ball_pos.isStartPosition = true;
	for (i = 0;i < lane.length;i++)
	{
	    addPositionToArray(i);
	}
	
	TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, positions, lane.length);
	
	freeArrays();
} 

// ==========================================================================================


static uint8_t howMuch()
{
	uint8_t i;
	uint8_t counter = 0;
	pins = knockDownPins(&player, position);
	for(i = 0; i <= NUMBER_OF_PINS - 1; i++)
	{
		if ( pins.pins[i] ) counter++;
	}
	for(i = 0; i <= NUMBER_OF_PINS - 1; i++)
	{
		pins.pins[i] = 0;
	}
	return counter;
}

static uint8_t isValid(uint8_t parameter, uint8_t lower_bound, uint8_t upper_bound)
{
	if ( parameter >= lower_bound && parameter <= upper_bound )
		if ( parameter == pins.number_of_pins ) return 1;
	return 0;
}

TEST(knockDownPins, BallInLeftCanal)
{
	uint8_t counter;
	position.x = 2;
	counter = howMuch();
	TEST_ASSERT_EQUAL(1, isValid(counter, 0, 0));
}

TEST(knockDownPins, BallInRightCanal)
{
	uint8_t counter;
	position.x = 10;
	counter = howMuch();
	TEST_ASSERT_EQUAL(1, isValid(counter, 0, 0));
}

TEST(knockDownPins, BallAlmostInLeftCanal)
{
	uint8_t counter;
	position.x = 3;
	counter = howMuch();
	TEST_ASSERT_EQUAL(1, isValid(counter, 0, 4));
}

TEST(knockDownPins, BallAlmostInRightCanal)
{
	uint8_t counter;
	position.x = 9;
	counter = howMuch();
	TEST_ASSERT_EQUAL(1, isValid(counter, 0, 4));
}

TEST(knockDownPins, BallHitsCentre)
{
	uint8_t counter;
	position.x = 6;
	counter = howMuch();
	TEST_ASSERT_EQUAL(1, isValid(counter, 0, 10));
}

TEST(knockDownPins, BallInMiddleOfLeftHalf)
{
	uint8_t counter;
	position.x = 4;
	counter = howMuch();
	TEST_ASSERT_EQUAL(1, isValid(counter, 0, 6));
}

TEST(knockDownPins, BallInMiddleOfRightHalf)
{
	uint8_t counter;
	position.x = 8;
	counter = howMuch();
	TEST_ASSERT_EQUAL(1, isValid(counter, 0, 6));
}

TEST(knockDownPins, BallAlmostHitCentreLeft)
{
	uint8_t counter;
	position.x = 5;
	counter = howMuch();
	TEST_ASSERT_EQUAL(1, isValid(counter, 0, 8));
}

TEST(knockDownPins, BallAlmostHitCentreRight)
{
	uint8_t counter;
	position.x = 7;
	counter = howMuch();
	TEST_ASSERT_EQUAL(1, isValid(counter, 0, 8));
}
