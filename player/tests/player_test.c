#include "../../unity/unity_fixture.h"
#include "../src/player.h"

TEST_GROUP(PlayerTest);
TEST_GROUP_RUNNER(PlayerTest)
{
}
TEST_SETUP(PlayerTest)
{
}
TEST_TEAR_DOWN(PlayerTest)
{
}
TEST(PlayerTest, TestZeroKnockDown)
{
TEST_ASSERT_EQUAL_INT(0,knockDownPins(4,10));
}
