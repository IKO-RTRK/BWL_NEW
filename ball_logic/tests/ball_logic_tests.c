#include "../../unity/unity_fixture.h"
#include "../src/ball.h"
#include "../../player/src/player.h"


extern LANE_CONFIG lane;

PLAYER player;
BALL_POSITION position;


TEST_GROUP(knockDownPins);

TEST_GROUP_RUNNER(knockDownPins)
{
	RUN_TEST_CASE(knockDownPins, BallInLeftCanal);
	RUN_TEST_CASE(knockDownPins, BallInRightCanal);
}

TEST_SETUP(knockDownPins)
{
	lane.width = 7;
	lane.length = 40;
}

TEST_TEAR_DOWN(knockDownPins)
{
	
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
