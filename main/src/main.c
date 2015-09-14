#include "main.h"

static void printUsage(const char* const program_name);
static void init(GUI_TYPE gui);
static uint8_t createPlayers(BOWLING_GAME* the_game);
static void startGame(BOWLING_GAME* the_game);
static void doTheRoll(BOWLING_GAME* the_game, uint8_t current_frame, uint8_t current_player);
static BALL_POSITION throwTheBall(BOWLING_GAME* the_game, uint8_t current_player);
static void freeResources(BOWLING_GAME* games[]);

uint32_t main(uint32_t argc, char* argv[])
{
	uint8_t number_of_lanes = 0;

	uint8_t lane = 0;

	BOWLING_GAME* games[MAX_LANES];
	
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

	printf("# of lanes: ");
	scanf("%"SCNd8, &number_of_lanes);

	if (!isLaneValid(number_of_lanes))
	{
		return ERROR_LANES;
	}

	// for each game
	for (lane = 0; lane < number_of_lanes; lane++)
	{
		// create the game
		games[lane] = bowlingGameCreate();

		if (games[lane] == NULL)
		{
			return ERROR_MEMORY;
		} 
		
		games[lane]->lane_number = lane;

		printf("# of players on lane #%d: ", lane+1);
		scanf("%"SCNd8, &games[lane]->number_of_players);
		
		if (!isPlayerValid(games[lane]->number_of_players))
		{
			freeResources(games);
			return ERROR_PLAYERS;
		}

		if (!createPlayers(games[lane]))
		{
			freeResources(games);
			return ERROR_MEMORY;
		}		

		startGame(games[lane]);
	}	
	
	freeResources(games);
	return ERROR_OK;
}


static uint8_t createPlayers(BOWLING_GAME* the_game)
{
	uint8_t player = 0;
	for (player = 0; player < the_game->number_of_players; player++)
	{
		the_game->players[player] = playerCreate();
		if (the_game->players[player] == NULL)
		{
			return ERROR_MEMORY;
		}

		strcpy(the_game->players[player]->name, "Player");
	}
}

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

static void doTheRoll(BOWLING_GAME* the_game, uint8_t current_frame, uint8_t current_player)
{
	BALL_POSITION final_ball_position;
	KNOCKED_DOWN_PINS knocked_down_pins;

	while (playerCanThrow(the_game, current_frame, current_player))
	{
		final_ball_position = throwTheBall(the_game, current_player);
		
		knocked_down_pins = knockDownPins(the_game->players[current_player], final_ball_position);

		writeDownTheScore(the_game, current_player, knocked_down_pins.number_of_pins);
		// animation spare/strike should go here based on writeDownTheScore() result!

		drawKnockedPinsAndTable(the_game, current_player, knocked_down_pins);
		usleep(MICRO_TIME_BETWEEN_TWO_ROLLS);
	}
}

static BALL_POSITION throwTheBall(BOWLING_GAME* the_game, uint8_t current_player)
{
	BALL_POSITION current_ball_position;
	current_ball_position.isStartPosition = true;
	do
	{
		current_ball_position = rollTheBall(the_game->players[current_player], current_ball_position);
		animateBallMovement(the_game, current_player, current_ball_position);
	} while (!current_ball_position.isEndOfLane);

	return current_ball_position;
}

static void printUsage(const char* const program_name)
{
	printf("Usage %s [0 or 1]\n", program_name);
	printf("\t 0 - console GUI\n");
	printf("\t 1 - SDL GUI\n");
}

static void init(GUI_TYPE gui_id)
{
	system("clear");

	initGUI(gui_id);
	initBallLogic(my_lane_config);
}

static void freeResources(BOWLING_GAME* games[])
{	
	uint8_t l = 0;
	uint8_t p = 0;

	for (l = 0; l < MAX_LANES; l++)
	{
		for (p = 0; p < games[l]->number_of_players; p++)
		{
			if (games[l]->players[p] != NULL)
			{
				free(games[l]->players[p]); 
				games[l]->players[p] = NULL;
			}
		}
		
		if (games[l] != NULL)
		{
			free(games[l]); 
			games[l] = NULL;
		}
	}
}

