/**
 * @file ball.h
 * @brief Dokument sadrzi kratak opis struktura i funkcija koje su koristene
 * @author RT-RK Ball_logic
 * @date September, 2015
 */

#ifndef _BALL_H
#define _BALL_H
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "../../player/src/player.h"
/**
 * Broj cunjeva u garnituri na pocetku igre
 */
#define NUMBER_OF_PINS 10

/**
 * @brief Struktura sadrzi informacije o poziciji kugle na stazi
 */

uint32_t width;		///<	Promjenjiva koja cuva vrijednost sirine staze
uint32_t length;	///<	Promjenjiva koja cuva vrijednost duzine staze

typedef struct ball_position_struct
{
	uint8_t isEndOfLane;		///<	Informacija o tome da li je kugla dosla do kraja staza, moze imati vrijednost 0 ili 1 
	uint8_t isStartPosition;	///<	Informacija o tome da li je kugla na pocetku staze, moze imati vrijednost 0 ili 1
	uint32_t x;			///<	Trenutna vrijednost koordinate x za kuglu na stazi, predstavlja udaljenost kugle od centralne linije staze
	uint32_t y;			///<	Trenutna vrijednost koordinate y za kuglu na stazi, predstavlja udaljenost kugle od pocetka staze
} BALL_POSITION;


/**
 * @brief Struktura sadrzi informacije o cunjevima
 */
typedef struct knocked_down_pins_struct
{
	uint8_t number_of_pins;		///<	Broj cunjeva koji je srusen u bacanju kugle
	uint8_t pins[NUMBER_OF_PINS];	///<	Niz cunjeva, vrijednosti niza su 0 ako je cunj srusen, inace 1
} KNOCKED_DOWN_PINS;

/**
 * @brief Struktura sadrzi informacije o velicini staze
 */
typedef struct
{
	uint32_t width;		///<	Sirina staze
	uint32_t length;	///<	Duzina staze
} LANE_CONFIG;

/**
 * @brief 	Funkcija postavlja osnovne parametre za pocetak igre
 * @param 	lane_cfg	Struktura koja sadrzi informacije o stazi
 * @retval	void
 */
void initBallLogic(LANE_CONFIG lane_cfg);

/**
 * @brief 	Funkcija odredjuje narednu poziciju kugle na stazi
 * @param 	*the_player	Sadrzi informacije o igracu koji igra trenutno na stazi
 * @param 	current_ball_position	Sadrzi informacije o trenutnoj poziciji kugle na stazi
 * @retval 	BALL_POSITION Funckija vraca strukturu sa informacijama o novom polozaju kugle
 */
BALL_POSITION rollTheBall(PLAYER* the_player, BALL_POSITION current_ball_position);

/**
 * @brief 	Funkcija implementira rusenje cunjeva
 * @param 	*the_player	Sadrzi informacije o igracu koji trenutno igra na stazi
 * @param 	ball_position	Sadrzi informacije o polozaju kugle neposredno prije rusenja cunjeva
 * @retval	KNOCKED_DOWN_PINS Funkcija vraca strukturu sa informacija koliko i koji cunjevi su sruseni
 */
KNOCKED_DOWN_PINS knockDownPins(PLAYER* the_player, BALL_POSITION ball_position);
#endif

