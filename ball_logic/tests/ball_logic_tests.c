#include "../../unity/unity_fixture.h"
#include "../src/ball.h"
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>

TEST_GROUP(RollTheBallTests);

TEST_GROUP_RUNNER(RollTheBallTests)
{
    RUN_TEST_CASE(RollTheBallTest, StraightLineTest);
   // RUN_TEST_CASE(RollTheBallTest, OffsetStraightLineTest);
}

TEST_SETUP(RollTheBallTest)
{
    LANE_CONFIG lane2;
    lane2.width = 20;
    lane2.length = 50;
    initBallLogic(lane2);
}

TEST_TEAR_DOWN(RollTheBallTest)
{
	
}

TEST(RollTheBallTest, StraightLineTest)
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
  positions[0] = 0;
  
  for(i = 0;i < lane.length;i++)
  {
      ball_pos.y = i;
      ball_pos.x = 0;
      ball_pos_next = rollTheBall(NULL,ball_pos);
      positions[i+1] = ball_pos_next.x; 
  }
  
  TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, positions, lane.length);
}

