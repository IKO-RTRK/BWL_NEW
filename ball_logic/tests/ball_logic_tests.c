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
}

TEST_GROUP_RUNNER(knockDownPins)
{
	RUN_TEST_CASE(knockDownPins, BallInLeftCanal);
	RUN_TEST_CASE(knockDownPins, BallInRightCanal);
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
	lane.width = 7;
	lane.length = 40;
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

TEST(knockDownPins, BallInLeftCanal)
{
	uint8_t i;
	position.x = - lane.width/2 - 1;
	KNOCKED_DOWN_PINS pins = knockDownPins(&player, position);
	for(i = 0; i <= NUMBER_OF_PINS - 1; i++)
	{
		TEST_ASSERT_EQUAL(0, pins.pins[i]);
	}
}

TEST(knockDownPins, BallInRightCanal)
{
	uint8_t i;
	position.x = lane.width/2 + 1;
	KNOCKED_DOWN_PINS pins = knockDownPins(&player, position);
	for(i = 0; i <= NUMBER_OF_PINS - 1; i++)
	{
		TEST_ASSERT_EQUAL(0, pins.pins[i]);
	}
}
