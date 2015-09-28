#include "../../unity/unity_fixture.h"
#include "../src/bowling_game.h"

BOWLING_GAME pok;
BOWLING_GAME* the_game;

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
	RUN_TEST_CASE(PlayerCanTrowTests, illegal_roll_in_current_frame);
	RUN_TEST_CASE(PlayerCanTrowTests, player_had_not_strike_in_current_frame);
	RUN_TEST_CASE(PlayerCanTrowTests, player_had_strike_in_current_frame);
	RUN_TEST_CASE(PlayerCanTrowTests, second_roll_in_last_frame_in_first_roll_player_hadnt_clean);
	RUN_TEST_CASE(PlayerCanTrowTests, 3th_roll_of_10th_frame_player_had_not_strike_or_clean_in_1st_or_2nd_roll);
	RUN_TEST_CASE(PlayerCanTrowTests, 3th_roll_of_10th_frame_player_had_strike_or_clean_in_1st_or_2nd_roll);
}

TEST_SETUP(writeDownTheScoreTest)
{
	BOWLING_GAME* pok=bowlingGameCreate();
	 
}


TEST_SETUP(PlayerCanTrowTests)
{
	the_game=bowlingGameCreate();
	 
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



// 1. test
TEST(PlayerCanTrowTests , first_roll_in_current_frame)
{
	uint8_t i;
	uint8_t j;

	for(j=0 ; j < MAX_PLAYERS_PER_LANE ; j++)
	for(i=0 ; i < NUM_OF_FRAMES-1; i++)
	{	
		the_game->current_roll[j]=2*i;
		the_game->frames[j][i]=5;
	
		TEST_ASSERT_EQUAL(1, playerCanThrow(the_game, i ,j));
	}
}



//2. test
TEST(PlayerCanTrowTests , second_roll_in_curent_frame)
{
	uint8_t i;
	uint8_t j;

	for(j=0 ; j < MAX_PLAYERS_PER_LANE ; j++)
	for(i=0 ; i < NUM_OF_FRAMES-1; i++)
	{	
		the_game->current_roll[j]=2*i+1;
		the_game->frames[j][i]=5;

		TEST_ASSERT_EQUAL(1, playerCanThrow(the_game,  i ,j));
	}
}

//3. test
TEST(PlayerCanTrowTests , illegal_roll_in_current_frame)
{

	uint8_t i;
	uint8_t j;

	for(j=0 ; j < MAX_PLAYERS_PER_LANE ; j++)
	for(i=0 ; i < NUM_OF_FRAMES-1; i++)
	{	
		if(i< NUM_OF_FRAMES-1)
		{		
			the_game->current_roll[j]=2*i+2;
			the_game->frames[j][i]=5;
		}
		if(i == NUM_OF_FRAMES-1)
		{		
			the_game->current_roll[j]=2*i+3;
			the_game->frames[j][i]=5;
		}
		TEST_ASSERT_EQUAL(0, playerCanThrow(the_game,  i ,j));

	}
}


//4. test
TEST(PlayerCanTrowTests , player_had_not_strike_in_current_frame)
{
	uint8_t i;
	uint8_t j;

	for(j=0 ; j < MAX_PLAYERS_PER_LANE ; j++)
	for(i=0 ; i < NUM_OF_FRAMES-1; i++)
	{	
		the_game->current_roll[j]=2*i+1;
		the_game->frames[j][i]=5;

		TEST_ASSERT_EQUAL(1, playerCanThrow(the_game,  i ,j));

	}
}

//5. test
TEST(PlayerCanTrowTests , player_had_strike_in_current_frame)
{
	uint8_t i;
	uint8_t j;

	for(j=0 ; j < MAX_PLAYERS_PER_LANE-1 ; j++)
	for(i=0 ; i < NUM_OF_FRAMES-1; i++)
	{	
		the_game->current_roll[j]=2*i+1;
		the_game->frames[j][i]=10;

		TEST_ASSERT_EQUAL(0, playerCanThrow(the_game,  i ,j));
	}
}

//6. test
TEST(PlayerCanTrowTests , second_roll_in_last_frame_in_first_roll_player_hadnt_clean)
{
	uint8_t j;
	uint8_t current_frame=10-1;  			 // 10. frame je frame sa indeksom 9, jer indeksiranje krece od 0 

	for(j=0 ; j < MAX_PLAYERS_PER_LANE ; j++)
	{
		the_game->frames[j][current_frame]=5;
		the_game->current_roll[j]=2*(10-1)+1;  	//drugo bacanje u 10 frame-u
		TEST_ASSERT_EQUAL(1, playerCanThrow(the_game , current_frame , j));
	}
}


//7. test

TEST(PlayerCanTrowTests ,  3th_roll_of_10th_frame_player_had_not_strike_or_clean_in_1st_or_2nd_roll)
{

	uint8_t j;
	uint8_t last_frame=10-1;  			 // 10. frame je frame sa indeksom 9, jer indeksiranje krece od 0 

	for(j=0 ; j < MAX_PLAYERS_PER_LANE ; j++)
	{
		the_game->frames[j][last_frame]=5;
		the_game->current_roll[j]=2*last_frame+2;  	// 3. bacanje u 10 frame-u
		TEST_ASSERT_EQUAL(0, playerCanThrow(the_game , last_frame , j));
	}

}


//8. test

TEST(PlayerCanTrowTests , 3th_roll_of_10th_frame_player_had_strike_or_clean_in_1st_or_2nd_roll)
{

	uint8_t j;
	uint8_t last_frame=10-1;  			 // 10. frame je frame sa indeksom 9, jer indeksiranje krece od 0 

	for(j=0 ; j < MAX_PLAYERS_PER_LANE ; j++)
	{
		the_game->frames[j][last_frame]=10;	// bodovi u prva dva bacanja su 10 ili vise=> clean ili strike
		the_game->current_roll[j]=2*last_frame+2;  	// 3. bacanje u 10 frame-u
		TEST_ASSERT_EQUAL(1, playerCanThrow(the_game , last_frame , j));
	}

}







