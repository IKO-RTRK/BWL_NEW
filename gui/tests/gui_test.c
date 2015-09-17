#include "../../unity/unity_fixture.h"
#include "../src/gui.h"
#include "../include/SDL.h"

BOWLING_GAME bg1, bg2;
BALL_POSITION bp1, bp2;

TRACK_CONSOLE* track;
BOWLING_GAME* game;
KNOCKED_DOWN_PINS knocked_pins;


TEST_GROUP(SDLAnimationTest);
TEST_GROUP(ConsoleAnimationTest);

TEST_GROUP_RUNNER(SDLAnimationTest)
{
	RUN_TEST_CASE(SDLAnimationTest, SDL_Init);
	RUN_TEST_CASE(SDLAnimationTest, BMP_Load);
	RUN_TEST_CASE(SDLAnimationTest, Animation);
}

TEST_GROUP_RUNNER(ConsoleAnimationTest)
{
	RUN_TEST_CASE(ConsoleAnimationTest, drawKnockedPinsNone);
	RUN_TEST_CASE(ConsoleAnimationTest, drawKnockedPinsAll);
	RUN_TEST_CASE(ConsoleAnimationTest, drawKnockedPinsOne);
	RUN_TEST_CASE(ConsoleAnimationTest, drawKnockedPinsTwo);
}

TEST_SETUP(SDLAnimationTest)
{
	quit();
}

TEST_SETUP(ConsoleAnimationTest)
{
	track = (TRACK_CONSOLE*)calloc(1, sizeof(TRACK_CONSOLE));
	track->trackID = 1;
	game = (BOWLING_GAME*)malloc(sizeof(BOWLING_GAME));
	game->lane_number = 1;
	game->number_of_players = 1;
	
	initialisation_track_console(track, game);
	uint8_t i;

	knocked_pins.number_of_pins = 0;
	for (i = 0; i < NUM_OF_PINS; i++)
	{
	  knocked_pins.pins[i] = 0;
	} 
	
}

TEST_TEAR_DOWN(SDLAnimationTest)
{
}

TEST_TEAR_DOWN(ConsoleAnimationTest)
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
	bp1.x = 15;
	bp2.x = 125;
	bg1.lane_number = 0;
	bg2.lane_number = 2;
	uint32_t i;
	for (i = 0; i < 450; i++)
	{	
		SDL_Delay(10);
		bp1.y = i;
		bp2.y = i;
		if (i < 300)
		animateBallMovement(&bg1, 0, bp1);
		animateBallMovement(&bg2, 0, bp2);
	}
	SDL_Delay(4000);
	TEST_ASSERT_EQUAL(0, 0);
}


//Prvi test - Console gui
TEST(ConsoleAnimationTest, drawKnockedPinsNone)
{	
	
	TEST_ASSERT_EQUAL(0, drawKnockedPinsAndTable_console(game, 1, knocked_pins, track));
	free(track);
	free(game);
	
}

TEST(ConsoleAnimationTest, drawKnockedPinsAll)
{

	uint8_t i;
	
	knocked_pins.number_of_pins = 10;
	for (i = 0; i < NUM_OF_PINS; i++)
	{
	  knocked_pins.pins[i] = 1;
	} 
	
	TEST_ASSERT_EQUAL(10, drawKnockedPinsAndTable_console(game, 1, knocked_pins, track));
	free(track);
	free(game);
}

TEST(ConsoleAnimationTest, drawKnockedPinsOne)
{
	knocked_pins.number_of_pins = 1;
	knocked_pins.pins[0] = 1;
	
	TEST_ASSERT_EQUAL(1, drawKnockedPinsAndTable_console(game, 1, knocked_pins, track));
	free(track);
	free(game);
}

TEST(ConsoleAnimationTest, drawKnockedPinsTwo)
{

	knocked_pins.number_of_pins = 2;
	knocked_pins.pins[0] = 1;
	knocked_pins.pins[1] = 1;
	
	TEST_ASSERT_EQUAL(2, drawKnockedPinsAndTable_console(game, 1, knocked_pins, track));
	free(track);
	free(game);
}


