#include "../../unity/unity_fixture.h"
#include "../src/gui.h"

BOWLING_GAME bg;
BALL_POSITION bp;

TEST_GROUP(GuiSDLTest);


TEST_GROUP_RUNNER(GuiSDLTest)
{
	RUN_TEST_CASE(GuiSDLTest, SDL_Init);
}

TEST_SETUP(GuiSDLTest)
{
	 
}

TEST_TEAR_DOWN(GuiSDLTest)
{
}

// Prvi test - SDL inicijalizacija
TEST(GuiSDLTest, SDL_Init)
{
	initGUI(SDL);
	TEST_ASSERT_EQUAL(0, animateBallMovement(&bg, 0, bp));
}


