#include "../../unity/unity_fixture.h"
#include "../src/bowling_game.h"

TEST_GROUP(PlayerCanTrowTests);


TEST_GROUP_RUNNER(PlayerCanTrowTests)
{
	RUN_TEST_CASE(PlayerCanTrowTests, prviTestPada );
//	RUN_TEST_CASE(PlayerCanTrowTests, _____);
//	RUN_TEST_CASE(PlayerCanTrowTests, _____);
//	RUN_TEST_CASE(PlayerCanTrowTests, _____);
//	RUN_TEST_CASE(PlayerCanTrowTests, _____);
//	RUN_TEST_CASE(PlayerCanTrowTests, _____);
}

TEST_SETUP(PlayerCanTrowTests)
{
	 
}

TEST_TEAR_DOWN(PlayerCanTrowTests)
{
}

// Prvi test
TEST(PlayerCanTrowTests,prviTestPada)
{
	
	TEST_ASSERT_EQUAL(0, playerCanThrow(the_game, current_frame,current_player));
}



