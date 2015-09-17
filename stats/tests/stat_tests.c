#include "../../unity/unity_fixture.h"
#include "../src/bowling_game.h"

BOWLING_GAME pok;


TEST_GROUP(writeDownTheScoreTest);

TEST_GROUP_RUNNER(writeDownTheScoreTest)
{
	RUN_TEST_CASE(writeDownTheScoreTest, TestAllZeroes );	
	RUN_TEST_CASE(writeDownTheScoreTest, TestAllOnes );
	RUN_TEST_CASE(writeDownTheScoreTest, TestOneStrike);
	RUN_TEST_CASE(writeDownTheScoreTest, TestOneSpare);	
	RUN_TEST_CASE(writeDownTheScoreTest, TwoStrikesInRow);
	RUN_TEST_CASE(writeDownTheScoreTest, TenStrikesInRow);
	
}



TEST_SETUP(writeDownTheScoreTest)
{
	
	 
}


TEST_TEAR_DOWN(writeDownTheScoreTest)
{
}


//1. test - nijedan cunj nije srusen 



TEST(writeDownTheScoreTest, TestAllZeroes)
{
	BOWLING_GAME* pok = bowlingGameCreate();

	int i;
	for ( i=0; i < MAX_ROLLS; i++ )
		writeDownTheScore(pok, 1, 0);
	
	TEST_ASSERT_EQUAL(0, pok->totalScore[1]);
}


//2. test - u svakom bacanju srusen po jedan cunj 


TEST(writeDownTheScoreTest, TestAllOnes)
{
	BOWLING_GAME* pok = bowlingGameCreate();

	int i;
	for ( i=0; i < MAX_ROLLS-1; i++ )
		writeDownTheScore(pok, 1, 1);

	TEST_ASSERT_EQUAL(20, pok->totalScore[1]);
}



//3. test - jedna strike 
TEST(writeDownTheScoreTest, TestOneStrike)
{
	BOWLING_GAME* pok = bowlingGameCreate();
	
	int i;
	writeDownTheScore(pok, 1, 3);
	writeDownTheScore(pok, 1, 2);
	writeDownTheScore(pok, 1, 10);
	writeDownTheScore(pok, 1, 3);
	writeDownTheScore(pok, 1, 2);
	writeDownTheScore(pok, 1, 0);
	writeDownTheScore(pok, 1, 0);
	TEST_ASSERT_EQUAL(25, pok->totalScore[1]);
}


//4. test - jedan strike 

TEST(writeDownTheScoreTest, TestOneSpare)
{
	BOWLING_GAME* pok = bowlingGameCreate();
	int i;
	writeDownTheScore(pok, 1, 5);
	writeDownTheScore(pok, 1, 5);
	for ( i=0; i < MAX_ROLLS-2; i++ )
		writeDownTheScore(pok, 1, 1);

	TEST_ASSERT_EQUAL(29, pok->totalScore[1]);
}



//5. test - 2 strike zaredom

TEST(writeDownTheScoreTest, TwoStrikesInRow)
{
	BOWLING_GAME* pok = bowlingGameCreate();
	int i;
	writeDownTheScore(pok, 1, 10);
	writeDownTheScore(pok, 1, 10);
	for ( i=0; i < MAX_ROLLS-4; i++ )
		writeDownTheScore(pok, 1, 1);

	TEST_ASSERT_EQUAL(49, pok->totalScore[1]);
}

//6. test - perfectGame

TEST(writeDownTheScoreTest, TenStrikesInRow)
{
	BOWLING_GAME* pok = bowlingGameCreate();
	int i;
	for ( i=0; i < MAX_ROLLS - 9 ; i++ )
		writeDownTheScore(pok, 1, 10);

	TEST_ASSERT_EQUAL(300, pok->totalScore[1]);
}

