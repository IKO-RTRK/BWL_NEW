#include "../../unity/unity_fixture.h"

static void RunAllTests(void)
{
	RUN_TEST_GROUP(BallLogicTests);
}

int main(int argc, char* argv[])
{
	return UnityMain(argc, (char **) argv, RunAllTests);
}