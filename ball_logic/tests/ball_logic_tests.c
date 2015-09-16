#include "../../unity/unity_fixture.h"
#include "../src/ball.h"
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>

#include "../../player/src/player.h"


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

PLAYER player;
BALL_POSITION position;

extern LANE_CONFIG lane;

TEST_SETUP(knockDownPins)
{
	lane.width = 7;
	lane.length = 40;
}

TEST_TEAR_DOWN(knockDownPins)
{
	
}

TEST(RollTheBallTests, StraightLineTest)
{
  int i;
  
  uint32_t expected[lane.length];
  for (i = 0; i < lane.length; i++)
  {
    expected[i] = 0;
  }
  
  uint32_t positions[lane.length];
  BALL_POSITION ball_pos;
  BALL_POSITION ball_pos_next;
  
  for(i = 0;i < lane.length;i++)
  {
      ball_pos.y = i;
      ball_pos.x = 0;
      ball_pos_next = rollTheBall(NULL,ball_pos);
      positions[i] = ball_pos.x;
	  ball_pos.x = ball_pos_next.x;
  }
  
  TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, positions, lane.length);
}

TEST(RollTheBallTests, OffsetStraightLineTest)
{
	int i;
	
	uint32_t expected[lane.length];
	for (i = 0; i < lane.length; i++)
	{
		expected[i] = 3;
	}
	
	uint32_t positions[lane.length];
	BALL_POSITION ball_pos;
	BALL_POSITION ball_pos_next;
	
	for (i = 0;i < lane.length;i++)
	{
		ball_pos.y = i;
		ball_pos.x = 3;
		ball_pos_next = rollTheBall(NULL, ball_pos);
		positions[i] = ball_pos.x;
		ball_pos.x = ball_pos_next.x;
	}
	
	TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, positions, lane.length);
}

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
