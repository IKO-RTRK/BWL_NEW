#include "main.h"

static void printUsage(const char* const program_name);
static void init(GUI_TYPE gui);
static uint8_t createPlayers(BOWLING_GAME* the_game);
static void startGame(BOWLING_GAME* the_game);
static void doTheRoll(BOWLING_GAME* the_game, uint8_t current_frame, uint8_t current_player);
static BALL_POSITION throwTheBall(BOWLING_GAME* the_game, uint8_t current_player);
static void freeResources(BOWLING_GAME* games[]);
static uint8_t createGame(BOWLING_GAME* game_init[], uint8_t the_lane);
static uint8_t initPlayers(BOWLING_GAME* game_init[], uint8_t the_lane);
static uint8_t numberOfLanes();
uint32_t main(uint32_t argc, char* argv[])
{
	uint8_t number_of_lanes = 0;

	uint8_t lane = 0;

	BOWLING_GAME* games[MAX_LANES]={NULL};
	
	GUI_TYPE gui;

	if (argc != 2)
	{
		printUsage(argv[0]);
		return ERROR_USAGE;
	} else
	{
		gui = atoi(argv[1]);
	}
	
	// do INIT based on parsed argv!
	init(gui);
	//input number of lanes
	number_of_lanes= numberOfLanes();
	if (number_of_lanes < 0)
		number_of_lanes = 3;

	// for each game
	for (lane = 0; lane < number_of_lanes; lane++)
	{
		// create the game
		createGame(games,lane);

		//create and init players on the lane
		initPlayers(games,lane);
		createPlayers(games[lane]);
		//start game on that lane
		startGame(games[lane]);
	}
	freeResources(games);
	return ERROR_OK;
}

/**
*	@brief 			Determine number of lanes.
*	@retval 		uint8_t
*/
static uint8_t numberOfLanes()
{	
	uint8_t temp=0;
	printf("# of lanes: ");
	scanf("%"SCNd8, &temp);
	
	if (!isLaneValid(temp))
	{
		return ERROR_LANES;
	}
	return temp;;
}

/**
*	@brief			Determine number of players on each lane and name of players.
*	@param game_init[]	Pointer on array of struct BOWLING_GAME. Assign the number of players to each element of array.
*	@param the_lane 	Represents the lane with which function works.
*	@retval 		uint8_t
*/
static uint8_t initPlayers(BOWLING_GAME* game_init[], uint8_t the_lane)
{
	printf("# of players on lanefree #%d: ", the_lane+1);
	scanf("%"SCNd8, &game_init[the_lane]->number_of_players);
		
	if (!isPlayerValid(game_init[the_lane]->number_of_players))
	{
		freeResources(game_init);
		return ERROR_PLAYERS;
	}

	/*if (!createPlayers(game_init[the_lane]))
	{
		freeResources(game_init);
		return ERROR_MEMORY;
	}*/
	
}
	
/**
*	@brief			Create stats for lane.
*	@param game_init[]	Pointer on array of struct BOWLING_GAME. Create the game for the lane.
*	@param the_lane 	Represents the lane with which function works.
*	@retval			uint8_t
*/	
static uint8_t createGame(BOWLING_GAME* game_init[], uint8_t the_lane)
{
		game_init[the_lane] = bowlingGameCreate();

		if (game_init[the_lane] == NULL)
		{	
			freeResources(game_init);
			return ERROR_MEMORY;
		} 
		
		game_init[the_lane]->lane_number = the_lane;
		
}	

/**
*	@brief			Create players.
*	@param the_game		Pointer on array of struct BOWLING_GAME. Create players.
*	@retval 		uint8_t
*/
static uint8_t createPlayers(BOWLING_GAME* the_game)
{
	uint8_t player = 0;
	char player_name[NAME_LENGTH_MAX];
	uint8_t player_quality;
	int8_t player_main_hand;
	for (player = 0; player < the_game->number_of_players; player++)
	{	
		the_game->players[player] = playerCreate();
		if (the_game->players[player] == NULL)
		{
			return ERROR_MEMORY;
		}
		printf("Unesite ime igraca: ");		
		scanf("%s", player_name);
		assignPlayerName(the_game->players[player], player_name);
		printf("Unesite kvalitet igraca: ");		
		scanf("%"SCNu8, &player_quality);
		assignPlayerQuality(the_game->players[player], player_quality);
		printf("Unesite kojom rukom igrac igra: ");		
		scanf("%"SCNd8, &player_main_hand);
		assignPlayerMainHand(the_game->players[player], player_main_hand);
	}
}

/**
*	@brief 			Start the game on one lane.
*	@param the_game 	Pointer on array of struct BOWLING_GAME. Starts the game.
*	@retval 		void
*/
static void startGame(BOWLING_GAME* the_game)
{
	uint8_t current_player = 0;
	uint8_t current_frame = 0;

	for (current_frame = 0; current_frame < NUM_OF_FRAMES; current_frame++)
	{
		for (current_player = 0; current_player < the_game->number_of_players; current_player++)
		{
			doTheRoll(the_game, current_frame, current_player);
		}
	}
}

/**
*	@brief			Check if player can throw the ball, determine movement of the ball, determine which pins are knocked down and write down the result.
*	@param the_game		Pointer on array of struct BOWLING_GAME. 
*	@param current_frame	The current frame in which player throws the ball.
*	@param current_player	The player which throws the ball.
*	@retval 		void
*/
static void doTheRoll(BOWLING_GAME* the_game, uint8_t current_frame, uint8_t current_player)
{
	BALL_POSITION final_ball_position;
	KNOCKED_DOWN_PINS knocked_down_pins;
		
	
	while (playerCanThrow(the_game, current_frame, current_player))
	{	

		final_ball_position = throwTheBall(the_game, current_player);
		knocked_down_pins = knockDownPins(the_game, current_player, final_ball_position);

		//writeDownTheScore(the_game, current_player, knocked_down_pins.number_of_pins);
		// animation spare/strike should go here based on writeDownTheScore() result!

		//drawKnockedPinsAndTable(the_game, current_player, knocked_down_pins);
		usleep(MICRO_TIME_BETWEEN_TWO_ROLLS);
		the_game->current_roll[current_player]++;
	}
}

/**
*	@brief 			Movement of the ball.
*	@param the_game		Pointer on array of struct BOWLING_GAME. Determine which player currently throws the ball.
*	@param current_player	Player who throws currently.
*	@retval			BALL_POSITION
*/
static BALL_POSITION throwTheBall(BOWLING_GAME* the_game, uint8_t current_player)
{
	BALL_POSITION current_ball_position;
	current_ball_position.isStartPosition = true;
	do
	{
		current_ball_position = rollTheBall(the_game->players[current_player], current_ball_position);
		//animateBallMovement(the_game, current_player, current_ball_position);

		printf("x = %"PRIu8 " y = %"PRIu32 "\n", current_ball_position.x, current_ball_position.y);

	} while (!current_ball_position.isEndOfLane);

	return current_ball_position;
}

/**
*	@brief			Write instructions to choose GUI.	
*	@param program_name	Constant char array with name of program.
*	@retval			void
*/
static void printUsage(const char* const program_name)
{
	printf("Usage %s [0 or 1]\n", program_name);
	printf("\t 0 - console GUI\n");
	printf("\t 1 - SDL GUI\n");
}

/**
*	@brief			Initialization of variable gui_id, which determines which GUI will be used. 
*	@param gui_id		Variable shows which GUI (console or SDL) will be used.
*	@retval			void
*/
static void init(GUI_TYPE gui_id)
{
	system("clear");

	initGUI(gui_id);
	my_lane_config.width = 43;		//postavljene fiksne vrijednosti da bi staza bila inicijalizovana
	my_lane_config.length = 50;
	my_lane_config.bumperWidth = 5;
	initBallLogic(my_lane_config);
}

/**
*	@brief			To free alfreelocated memory for struct BOWLING_GAME.
*	@param games[]		Pointer on array of struct BOWLING_GAME. 
*	@retval			void
*/
static void freeResources(BOWLING_GAME* games[])
{	
	uint8_t l = 0;
	uint8_t p = 0;
	for (l = 0; l < MAX_LANES; l++)
	{	
		if (games[l] != NULL) 
		{
			for (p = 0; p < games[l]->number_of_players; p++)
			{
				if (games[l]->players[p] != NULL)
				{
					free(games[l]->players[p]); 
					games[l]->players[p] = NULL;
				}
			}
		free(games[l]); 
		games[l] = NULL;
		}
		
	}
}

