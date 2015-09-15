#include "../unity/unity_fixture.h"
#include "../src/bowling_game.h"



TEST_GROUP(BowlingTest);

TEST_GROUP_RUNNER(BowlingTest)
{
	RUN_TEST_CASE(BowlingTest, TestNumberOfPins0);
	
}

TEST_SETUP(BowlingTest)
{
	bowlingGameCreate();
}

TEST_TEAR_DOWN(BowlingTest)
{
}




//1. test - nije srusen nijedan cunj




