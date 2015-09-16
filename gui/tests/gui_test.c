#include "../../unity/unity_fixture.h"
#include "../src/gui.h"

BOWLING_GAME bg;
BALL_POSITION bp;

TEST_GROUP(SDLAnimationTest);


TEST_GROUP_RUNNER(SDLAnimationTest)
{
	RUN_TEST_CASE(SDLAnimationTest, SDL_Init);
	RUN_TEST_CASE(SDLAnimationTest, BMP_Load);
}

TEST_SETUP(SDLAnimationTest)
{
	 
}

TEST_TEAR_DOWN(SDLAnimationTest)
{
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


