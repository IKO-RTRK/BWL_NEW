#include "../../unity/unity_fixture.h"
#include "../src/player.h"

PLAYER* player;

TEST_GROUP(PlayerTest);

TEST_GROUP_RUNNER(PlayerTest)
{
	RUN_TEST_CASE (PlayerTest, TestAllocatePlayer);
	RUN_TEST_CASE (PlayerTest, TestCreateName);
	RUN_TEST_CASE (PlayerTest, TestNameOutOfBounds);
	RUN_TEST_CASE (PlayerTest, TestEmptyName);
}

TEST_SETUP(PlayerTest)
{	 
	player = playerCreate();
}

TEST_TEAR_DOWN(PlayerTest)
{
}

TEST(PlayerTest, TestAllocatePlayer)
{
	TEST_ASSERT_TRUE (player != NULL);
}

TEST(PlayerTest, TestCreateName)
{
	assignPlayerName (player, "name");
	STRCMP_EQUAL("name", player->name);
}

TEST(PlayerTest, TestNameOutOfBounds)
{
	assignPlayerName (player, "name123456789123456789");
	STRCMP_EQUAL("name123456789123456", player->name);
}

TEST(PlayerTest, TestEmptyName)
{
	assignPlayerName (player,"");
	STRCMP_EQUAL("Player", player->name);
}
