#include "../../unity/unity_fixture.h"

static void RunAllTests(void)
{
	RUN_TEST_GROUP(SDLDrawKnockedPinsTest);
	//RUN_TEST_GROUP(SDLAnimationTest);
//	RUN_TEST_GROUP(ConsoleAnimationTest);
}

int main(int argc, char *argv[])
{
	return UnityMain(argc, (const char **)argv, RunAllTests);
}


