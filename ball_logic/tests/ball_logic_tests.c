#include "../../unity/unity_fixture.h"
#include "../src/ball.h"
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>

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

static void addPositionToArray(int position, uint32_t offset)
{
	ball_pos.y = position;
	if (position == 0)
		ball_pos.x = offset;
	ball_pos_next = rollTheBall(&player, ball_pos);
	positions[position] = ball_pos.x;
	ball_pos.x = ball_pos_next.x;
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
    RUN_TEST_CASE(RollTheBallTests, StraightLineTest);
    RUN_TEST_CASE(RollTheBallTests, OffsetStraightLineTest);
}

TEST_GROUP_RUNNER(knockDownPins)
{
	RUN_TEST_CASE(knockDownPins, BallInLeftCanal);
	RUN_TEST_CASE(knockDownPins, BallInRightCanal);
	RUN_TEST_CASE(knockDownPins, BallAlmostInLeftCanal);
	RUN_TEST_CASE(knockDownPins, BallAlmostInRightCanal);
}

TEST_SETUP(RollTheBallTests)
{
    LANE_CONFIG lane2;
    lane2.width = 20;
    lane2.length = 50;
    initBallLogic(lane2);
}

TEST_TEAR_DOWN(RollTheBallTests)
{
	
}

extern LANE_CONFIG lane;

TEST_SETUP(knockDownPins)
{
	lane.width = 13;
	lane.bumperWidth = 3;
	lane.length = 40;
}

TEST_TEAR_DOWN(knockDownPins)
{
	
}

TEST(RollTheBallTests, StraightLineTest)
{
  int i;
  
  fillExpectedArray(10);
  
  player.quality = 10;
  
  initialiseArray();
  for(i = 0;i < lane.length;i++)
  {
      addPositionToArray(i,lane.width/2);
  }
  
  TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, positions, lane.length);
  
  freeArrays();
}

TEST(RollTheBallTests, OffsetStraightLineTest)
{
	int i;
	
	fillExpectedArray(13);
	
	initialiseArray();
	for (i = 0;i < lane.length;i++)
	{
		addPositionToArray(i,lane.width/2 + 3);
	}
	
	TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, positions, lane.length);
	
	freeArrays();
}

TEST(knockDownPins, BallInLeftCanal)
{
	uint8_t i;
	uint8_t howMuch=0, isValid=0;
	position.x = 3;
	KNOCKED_DOWN_PINS pins = knockDownPins(&player, position);
	for(i = 0; i <= NUMBER_OF_PINS - 1; i++)
	{
		if ( pins.pins[i] ) howMuch++;
	}
	if ( howMuch == 0 )
		if ( howMuch == pins.number_of_pins ) isValid = 1;

	TEST_ASSERT_EQUAL(1, isValid);
}

TEST(knockDownPins, BallInRightCanal)
{
	uint8_t i;
	uint8_t howMuch=0, isValid=0;
	position.x = 13;
	KNOCKED_DOWN_PINS pins = knockDownPins(&player, position);
	for(i = 0; i <= NUMBER_OF_PINS - 1; i++)
	{
		if ( pins.pins[i] ) howMuch++;
	}
	
	if ( howMuch >= 0 && howMuch <=3 )
		if ( howMuch == pins.number_of_pins ) isValid = 1;

	TEST_ASSERT_EQUAL(1, isValid);
}

TEST(knockDownPins, BallAlmostInLeftCanal)
{
	uint8_t i;
	uint8_t howMuch=0, isValid=0;
	position.x = 4;
	KNOCKED_DOWN_PINS pins = knockDownPins(&player, position);
	for(i = 0; i <= NUMBER_OF_PINS - 1; i++)
	{
		if ( pins.pins[i] ) howMuch++;
	}
	
	if ( howMuch >= 0 && howMuch <=4 )
		if ( howMuch == pins.number_of_pins ) isValid = 1;

	TEST_ASSERT_EQUAL(1, isValid);
	
	 
}

TEST(knockDownPins, BallAlmostInRightCanal)
{
	uint8_t i;
	uint8_t howMuch=0, isValid;
	position.x = 12;
	KNOCKED_DOWN_PINS pins = knockDownPins(&player, position);
	for(i = 0; i <= NUMBER_OF_PINS - 1; i++)
	{
		if ( pins.pins[i] ) howMuch++;
	}
	
	if ( howMuch >= 0 && howMuch <=4 ) isValid = 1;
	else isValid = 0;

	TEST_ASSERT_EQUAL(1, isValid);
}
