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
	RUN_TEST_CASE (PlayerTest, AssignedQualityOutOfBounds);
	RUN_TEST_CASE (PlayerTest, AssignedQualityInBounds);
	RUN_TEST_CASE (PlayerTest, TestIncreaseQuality);
	RUN_TEST_CASE (PlayerTest, TestIncreaseOutOfBounds)
	RUN_TEST_CASE (PlayerTest, TestDecreaseQuality)
	RUN_TEST_CASE (PlayerTest, TestDecreaseOutOfBounds);
	RUN_TEST_CASE (PlayerTest, AssignedMainHandOutOfBounds);
	RUN_TEST_CASE (PlayerTest, AssignedMainHandInBounds);
	
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
TEST(PlayerTest, AssignedQualityOutOfBounds)
{
	assignPlayerQuality (player, 0);
	TEST_ASSERT_TRUE (player -> quality == QUALITY_MIN);
}

TEST(PlayerTest, AssignedQualityInBounds)
{
	assignPlayerQuality (player, 7);
	TEST_ASSERT_TRUE (player -> quality == 7);
}

TEST(PlayerTest, AssignedMainHandOutOfBounds)
{
	assignPlayerMainHand (player, 7);
	TEST_ASSERT_TRUE (player -> main_hand == RIGHT_HAND);
}

TEST(PlayerTest, AssignedMainHandInBounds)
{

	assignPlayerMainHand (player, LEFT_HAND);
	TEST_ASSERT_TRUE (player -> main_hand == LEFT_HAND);
}


TEST(PlayerTest, TestEmptyName)
{
	assignPlayerName (player,"");
	STRCMP_EQUAL("Player", player->name);
}

TEST(PlayerTest, TestIncreaseQuality)
{
	assignPlayerQuality (player, 5);
	increaseQuality(player);
	TEST_ASSERT_TRUE (player->quality == 6);
}

TEST(PlayerTest, TestIncreaseOutOfBounds)
{
	assignPlayerQuality (player, QUALITY_MAX);
	increaseQuality(player);
	TEST_ASSERT_TRUE (player->quality == QUALITY_MAX);
}

TEST(PlayerTest, TestDecreaseQuality)
{
	assignPlayerQuality (player, 5);
	decreaseQuality(player);
	TEST_ASSERT_TRUE (player->quality == 4);
}

TEST(PlayerTest, TestDecreaseOutOfBounds)
{
	assignPlayerQuality (player, QUALITY_MIN);
	decreaseQuality(player);
	TEST_ASSERT_TRUE (player->quality == QUALITY_MIN);
}

