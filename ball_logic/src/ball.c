#include "ball.h"
#include <stdlib.h>
#include <math.h>


static bool isBallOnStartPosition(BALL_POSITION ball_position)
{
  if (ball_position.isStartPosition)
    return true;
  return false;
}

static void setIsStartPosition(BALL_POSITION* ball_position)
{
  ball_position->isStartPosition = false;
}

static void isEndOfLane(BALL_POSITION* ball_position)
{
  if (ball_position->y == lane.length - 1)
  {
    ball_position->isEndOfLane = true;
  }
  else
  {
  	ball_position->isEndOfLane = false;
  }
}

static bool isLaneConfigured()
{
	if (lane.width < 1 && lane.length < 1)
		return false;
	return true;
}

static void initBallPosition(BALL_POSITION* ball_position)
{
	ball_position->isEndOfLane = false;
	ball_position->isStartPosition = false;
}
static double getFraction(BALL_POSITION* ball_position)
{
	if (ball_position->y < function.y2)
		return ((function.x2 - function.x1)/(function.y2 - function.y1))/1.0;
	else
		return ((function.x3 - function.x2)/(function.y3 - function.y2))/1.0;
}

static void nextBallPosition(BALL_POSITION* ball_position)
{
	ball_position->x = getFraction(ball_position)*ball_position->y - getFraction(ball_position)*function.y1 + function.x1;
}

static void setKeyPoints(double center)
{
	function.x1 = function.x3 = center;
	function.x2 = center;
	function.y1 = 0;
	function.y2 = lane.width / 2 + 1;
	function.y3 = lane.length - 1; 
}

void initBallLogic(LANE_CONFIG lane_cfg)
{

  lane.width = lane_cfg.width;
  lane.length = lane_cfg.length;
  lane.bumperWidth = lane_cfg.bumperWidth;
}

BALL_POSITION rollTheBall(struct player* the_player, BALL_POSITION current_ball_position)
{

	BALL_POSITION next_ball_position;
	initBallPosition(&next_ball_position);

	if (!isLaneConfigured())
	{
		next_ball_position.x = -1;
		next_ball_position.y = -1;
	}
	else if (isBallOnStartPosition(current_ball_position))
	{

	  	next_ball_position.y = 0;
	  	double center = round(lane.width / 2.0);

	  	double offset = center / QUALITY_MAX;
	  	double total_offset = 0;
	  	uint8_t i;
	  	for (i = QUALITY_MAX; i > the_player->quality; i--)
	  	{
	  		total_offset += offset;
	  	}
	    
	  	if ( LEFT_HAND == the_player->main_hand)
	  	{
	    	center -= total_offset;
	  	}
	  	else
	  	{
	    	center += total_offset;
	  	}

	  	center = round(center);

	  	setKeyPoints(center);

	  	setIsStartPosition(&next_ball_position);
	  	next_ball_position.isEndOfLane = false;
	  	next_ball_position.x = center;
	}
	else
	{  
	  	next_ball_position.y = current_ball_position.y + 1;
	  	nextBallPosition(&next_ball_position);
	  	isEndOfLane(&next_ball_position);
	}
	
	return next_ball_position;
}


// ==========================================================================================


typedef struct node{ // lista koja sluzi za izvlacenje rednog broja dostupnih pinova koji se mogu srusiti
	uint8_t position;
	struct node *next;
} node;

static node * head=NULL;
static node * tail=NULL;
static uint8_t listSize=0;

static void listAppend(uint8_t broj)
{
	if ( head == NULL ) 
	{
		head=tail=(node*)malloc(sizeof(node));
		head->position=tail->position=broj;
		head->next=tail->next=NULL;
		return;
	}
	node *temp=tail;
	tail=(node*)malloc(sizeof(node));
	tail->next=NULL;
	temp->next=tail;
	tail->position=broj;
}

static void listDestroy()
{
	node *temp;
	while(head!=NULL)
	{
		temp=head->next;
		free(head);
		head=temp;
	}
	head=tail=NULL;
	listSize=0;
}

static uint8_t listGetAvailablePin(uint8_t atPosition) // vraca pin koji se moze srusiti, a nalazi se na poziciji "atPosition" u listi
{
	if ( atPosition > listSize || atPosition < 1 ) atPosition=1; // u slucaju da dodje nedozvoljena vrijednost izbacuje se onaj na poziciji 1
	uint8_t i=1;
	node *temp=head;
	node *prev=NULL;
	for(; i<atPosition; i++)
	{
		prev=temp;
		temp=temp->next;
	}
	i=temp->position;
	if ( temp==head ) { head=head->next; free(temp); listSize--; return i; }
	if ( temp==tail ) { free(tail); tail=prev; tail->next=NULL; listSize--; return i; }
	prev->next=temp->next;
	free(temp);
	listSize--;
	return i;
	
}
static void listInitialisation()
{
	uint8_t i;
	listDestroy();
	for(i=0; i <= NUMBER_OF_PINS - 1; i++)
		listAppend(i);
	listSize=10;
}
static double power_f(double x, uint8_t n)
{
	uint8_t i;
	double p = 1;
	for(i=1; i<=n ; i++)
	{
		p *= x;
	}
	return p;
}

static uint8_t howManyToKnockMax(int32_t position)
{

	if ( position - lane.bumperWidth <= -1 ) return 0; // ball went down the left canal
	if ( position + lane.bumperWidth >= lane.width ) return 0; // ball went down the right canal
	double place = (double)position - (double)(lane.width - 1)/2;
	double relative_offset;
	double realValue;
	
	relative_offset=place/(lane.width-2*lane.bumperWidth);


	if ( relative_offset <= 0 ) realValue = 10+23*relative_offset+36*power_f(relative_offset, 2)+36*power_f(relative_offset, 3);  // y = 10+23*x+36*x^2+36*x^3 for -0.5 >= x >= 0
	else realValue = 10-23*relative_offset+36*power_f(relative_offset, 2)-36*power_f(relative_offset, 3);  // y = 10-23*x+36*x^2-36*x^3 for 0 < x <= 0.5
	// function that approximates convention values
	
	//printf("%lf\n\n\n", realValue);

	return (uint8_t)ceil(realValue);
}



static void resetKnockedDownpins(KNOCKED_DOWN_PINS *pins)
{
	uint8_t i;
	
	pins->number_of_pins = 0;
	
	for(i=0; i <= NUMBER_OF_PINS - 1 ; i++)
	{
		pins->pins[i] = 0;
	}
}


static uint32_t randomNumber1()
{
	static uint32_t coeff = 19 ;
	uint32_t rand = rand*coeff + 3;
	coeff = coeff + 5;
	return rand;
}
static uint32_t randomNumber2()
{
	return random();
}

typedef uint32_t (*fptr)();

static fptr whatToCall()
{
	static uint32_t which = 0;
	which++;
	if ( which % 2 ) return randomNumber1;
		else return randomNumber2;
}
KNOCKED_DOWN_PINS knockDownPins(BOWLING_GAME* the_game, uint8_t current_player, BALL_POSITION ball_position)
{
	KNOCKED_DOWN_PINS pins;
	uint8_t i, max;

	resetKnockedDownpins(&pins);
	max = howManyToKnockMax((int32_t)ball_position.x);

	fptr randomNumber = whatToCall();
	
	if ( max == 0 ) pins.number_of_pins =  0; 
	else pins.number_of_pins = max - ( randomNumber() % ( QUALITY_MAX+1 - the_game->players[current_player]->quality ) );


	if ( the_game->current_roll[current_player] % 2 == 0 || the_game->current_roll[current_player] == 21 ) listInitialisation();  
	listInitialisation();
	//printf("%"PRIu8" ", pins.number_of_pins);

	for(i=0; i < pins.number_of_pins ; i++)
	{
		if ( listSize == 0 ) pins.pins[listGetAvailablePin(1)] = 1;
			else pins.pins[listGetAvailablePin( ( randomNumber() % listSize ) + 1 )] = 1;
	}

	/*for(i=0; i < NUMBER_OF_PINS ; i++)
	{
		printf("%"PRIu8" ", pins.pins[i]);
	}
	printf("\n\n\n");*/
	if ( the_game->current_roll[current_player] % 2 || the_game->current_roll[current_player] == 21 ) listDestroy();
	return pins;
}
