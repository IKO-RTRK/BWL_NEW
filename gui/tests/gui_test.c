#include "../../unity/unity_fixture.h"
#include "../src/gui.h"
#include "../../include/SDL.h"

BOWLING_GAME bg1, bg2;
BALL_POSITION bp1, bp2;

TEST_GROUP(SDLAnimationTest);


TEST_GROUP_RUNNER(SDLAnimationTest)
{
	RUN_TEST_CASE(SDLAnimationTest, SDL_Init);
	RUN_TEST_CASE(SDLAnimationTest, BMP_Load);
	RUN_TEST_CASE(SDLAnimationTest, Animation);
}

TEST_SETUP(SDLAnimationTest)
{
	quit();
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

// Treci test - Animacija
TEST(SDLAnimationTest, Animation)
{
	initGUI(SDL);
	bp1.x = 0;
	bp2.x = 50;
	bg1.lane_number = 0;
	bg2.lane_number = 2;
	uint8_t i;
	for (i = 0; i < 250; i++)
	{	
		SDL_Delay(10);
		bp1.y = i;
		bp2.y = i;
		animateBallMovement(&bg1, 0, bp1);
		animateBallMovement(&bg2, 0, bp2);
	}
	SDL_Delay(4000);
	TEST_ASSERT_EQUAL(0, 0);
}




