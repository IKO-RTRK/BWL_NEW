#include "../../unity/unity_fixture.h"
#include "../src/bowling_game.h"

BOWLING_GAME pok;


TEST_GROUP(writeDownTheScoreTest);
TEST_GROUP(PlayerCanTrowTests);

TEST_GROUP_RUNNER(writeDownTheScoreTest)
{
	RUN_TEST_CASE(writeDownTheScoreTest, TestAllZeroes );	
	RUN_TEST_CASE(writeDownTheScoreTest, TestAllOnes );
	RUN_TEST_CASE(writeDownTheScoreTest, TestOneStrike);
	RUN_TEST_CASE(writeDownTheScoreTest, TestOneSpare);	
	RUN_TEST_CASE(writeDownTheScoreTest, TwoStrikesInRow);
	RUN_TEST_CASE(writeDownTheScoreTest, TenStrikesInRow);
	RUN_TEST_CASE(writeDownTheScoreTest, SparesAndStrikes);
			
}

TEST_GROUP_RUNNER(PlayerCanTrowTests)
{
	RUN_TEST_CASE(PlayerCanTrowTests, first_roll_in_current_frame);
	RUN_TEST_CASE(PlayerCanTrowTests, second_roll_in_curent_frame);
	RUN_TEST_CASE(PlayerCanTrowTests, third_rool_in_current_frame);
	RUN_TEST_CASE(PlayerCanTrowTests, player_had_not_strike_in_current_frame);
	RUN_TEST_CASE(PlayerCanTrowTests, player_had_strike_in_current_frame);
	RUN_TEST_CASE(PlayerCanTrowTests, player_had_not_strike_in_10th_frame);
	RUN_TEST_CASE(PlayerCanTrowTests, player_had_not_strike_or_clean_in_10th_frame);
	RUN_TEST_CASE(PlayerCanTrowTests, player_had_strike_or_clean_in_10th_frame);
	RUN_TEST_CASE(PlayerCanTrowTests, trying_illegal_roll);
}

TEST_SETUP(writeDownTheScoreTest)
{
	BOWLING_GAME* pok=bowlingGameCreate();
	 
}


TEST_SETUP(PlayerCanTrowTests)
{
	BOWLING_GAME* the_game=bowlingGameCreate();
	 
}


TEST_TEAR_DOWN(writeDownTheScoreTest)
{
}

TEST_TEAR_DOWN(PlayerCanTrowTests)
{
}
/******************************************************************************************TESTOVI_ZA_writeDownTheScore***********************************************************************************/

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


//7. test - spares i strikes 


TEST(writeDownTheScoreTest, SparesAndStrikes)
{
	BOWLING_GAME* pok = bowlingGameCreate();
	int i;
	writeDownTheScore(pok, 1, 10);	
	writeDownTheScore(pok, 1, 10);
	writeDownTheScore(pok, 1, 5);
	writeDownTheScore(pok, 1, 5);
	writeDownTheScore(pok, 1, 6);
	writeDownTheScore(pok, 1, 4);	
	for ( i = 0; i <= MAX_ROLLS - 10 ; i++ )	
		writeDownTheScore(pok, 1, 1);
	
	TEST_ASSERT_EQUAL(84, pok->totalScore[1]);
}





/******************************************************************************************TESTOVI_ZA_PlayerCanTrow***********************************************************************************/



// Prvi test
TEST(PlayerCanTrowTests , first_roll_in_current_frame)
{	
	BOWLING_GAME* the_game = bowlingGameCreate();
	the_game->current_roll[1]=1;
	the_game->frames[1][1]=5;
	
	TEST_ASSERT_EQUAL(1, playerCanThrow(the_game,  1 ,1));
}

//Drugi test
TEST(PlayerCanTrowTests , second_roll_in_curent_frame)
{
	BOWLING_GAME* the_game = bowlingGameCreate();
	the_game->current_roll[1]=2;
	the_game->frames[1][1]=5;

	TEST_ASSERT_EQUAL(1, playerCanThrow(the_game,  1 ,1));
}

//Treci test
TEST(PlayerCanTrowTests , third_rool_in_current_frame)
{
	BOWLING_GAME* the_game = bowlingGameCreate();
	the_game->frames[1][1]=5;
	the_game->current_roll[1]=3;
	
	TEST_ASSERT_EQUAL(0, playerCanThrow(the_game,1 ,1));
}


//Cetvrti test
TEST(PlayerCanTrowTests , player_had_not_strike_in_current_frame)
{	
	BOWLING_GAME* the_game = bowlingGameCreate();
	the_game->frames[1][1]=5;
	the_game->current_roll[1]=2;

	TEST_ASSERT_EQUAL(1, playerCanThrow(the_game , 1 , 1));
}

//Peti test
TEST(PlayerCanTrowTests , player_had_strike_in_current_frame)
{	
	BOWLING_GAME* the_game = bowlingGameCreate();
	the_game->frames[1][1]=10;
	the_game->current_roll[1]=2;

	TEST_ASSERT_EQUAL(0, playerCanThrow(the_game , 1 , 1));
}

//Sesti test
TEST(PlayerCanTrowTests , player_had_not_strike_in_10th_frame)
{
	BOWLING_GAME* the_game = bowlingGameCreate();
	the_game->frames[1][10]=5;
	the_game->current_roll[1]=2*10;  //drugo bacanje u 10 frame-u

	TEST_ASSERT_EQUAL(1, playerCanThrow(the_game , 10 , 1));
}

//Sedmi test

TEST(PlayerCanTrowTests , player_had_not_strike_or_clean_in_10th_frame)
{	
	BOWLING_GAME* the_game = bowlingGameCreate();
	the_game->frames[1][10]=5;
	the_game->current_roll[1]=2*10+1;  //trece bacanje u 10 frame-u

	TEST_ASSERT_EQUAL(0, playerCanThrow(the_game , 10 , 1));
}


//8. test

TEST(PlayerCanTrowTests , player_had_strike_or_clean_in_10th_frame)
{	
	
	BOWLING_GAME* the_game = bowlingGameCreate();
	the_game->frames[1][10]=10;
	the_game->current_roll[1]=2*10+1;  //trece bacanje u 10 frame-u

	TEST_ASSERT_EQUAL(1, playerCanThrow(the_game , 10 , 1));
}

//9. test

TEST(PlayerCanTrowTests , trying_illegal_roll)
{	
	BOWLING_GAME* the_game = bowlingGameCreate();
	the_game->frames[1][10]=10;
	the_game->current_roll[1]=2*10+2;  //cetvrto bacanje u 10 frame-u

	TEST_ASSERT_EQUAL(0, playerCanThrow(the_game , 10 , 1));
}







