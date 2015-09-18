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
  ball_position -> isStartPosition = false;
}

static void isEndOfLane(BALL_POSITION* ball_position)
{
  if (ball_position -> y == lane.length - 1)
  {
    ball_position -> isEndOfLane = true;
  }
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
	if (isBallOnStartPosition(current_ball_position))
	{
	  next_ball_position.y = 0;
	  uint32_t center = lane.width / 2;
	  uint32_t offset = center / QUALITY_MAX;
	  uint8_t i;
	  for (i = QUALITY_MAX; i > the_player -> quality; i--)
	  {
	    center += offset;
	  }
	  
	  setIsStartPosition(&current_ball_position);
	  next_ball_position.isEndOfLane = false;
	  next_ball_position.x = center;
	}
	else
	{  
	  next_ball_position.y = current_ball_position.y + 1;
	  next_ball_position.x = current_ball_position.x;
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

static double power_f(double x,uint8_t n)
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
	pins->number_of_pins = 0;
	uint8_t i;
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

KNOCKED_DOWN_PINS knockDownPins(PLAYER* the_player, BALL_POSITION ball_position)
{
	KNOCKED_DOWN_PINS pins;
	uint8_t i, max;

	resetKnockedDownpins(&pins);
	max = howManyToKnockMax((int32_t)ball_position.x);

	uint32_t (*randomNumber)();
	static uint32_t which = 0;
	which++;
	
	if ( which % 2 ) randomNumber = randomNumber1;
		else randomNumber = randomNumber2;

	if ( max == 0 ) pins.number_of_pins =  0; 
	else pins.number_of_pins = max - ( randomNumber() % max );

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
	listDestroy();
	return pins;
}
