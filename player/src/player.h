/**
@file player.h
@brief This document contains detail description of structure PLAYER
@author RT-RK team
@date Septembar, 2015
*/

#ifndef _PLAYER_H
#define _PLAYER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

/*!
  Represents left hand as main hand of player. When assigning main hand to player, other modules should use LEFT_HAND instead of -1.
*/
#define LEFT_HAND -1
/*!
  Represents right hand as main hand of player. When assigning main hand to player, other modules should use RIGHT_HAND instead of 1.
*/
#define RIGHT_HAND 1
/*!
  Minimum value for player quality.
*/
#define QUALITY_MIN 1
/*!
  Maximum value for player quality. 
*/
#define QUALITY_MAX 10
/*!
  Maximum length of player name. 
*/
#define NAME_LENGTH_MAX 20

  /*! \struct player
    Structure player is apstraction of player in game.
  */
  typedef struct player 
  {
    char name[NAME_LENGTH_MAX];	///<	Name of player in game. Used as player ID in game. See #NAME_LENGTH_MAX
    uint8_t quality;		///<	Quality of player. Higher number means better player. See #QUALITY_MIN and #QUALITY_MAX
    uint8_t main_hand;		///<	Main hand of player. Important for game logic. See #LEFT_HAND and #RIGHT_HAND
  } PLAYER;

  /**
  * @brief	This method allocates memory for structure \ref player.
		Must be called before any other method in this file.
  * @param	void
  * @retval	PLAYER* Returns pointer to the allocated memory or NULL pointer if error is occured while allocating memory.
  */
  PLAYER* playerCreate();
  
  /**
  * @brief	This method assignes \a name to the \a player.
		If \a name of the player is higher than #NAME_LENGTH_MAX, the name will be cut to be exactly #NAME_LENGTH_MAX long.
		Must be called after playerCreate(), not before.
  * @param	PLAYER*	Pointer to structure \ref player whom we want to assign \a name.
  * @param	char*	The name to assign to the \a player.
  * @retval	void	
  */
  void assignPlayerName(PLAYER* player, char* name);

	/**
  * @brief	This method assignes \a quality to the \a player.
		If \a quality of the player is higher than #QUALITY_MAX or lower than #QUALITY_MIN, the quality will be set on #QUALITY_MIN.
		Must be called after playerCreate(), not before.
  * @param	PLAYER*	Pointer to structure \ref player whom we want to assign \a quality.
  * @param	uint8_t	The quality to assign to the \a player.
  * @retval	void	
  */
  void assignPlayerQuality(PLAYER* player, uint8_t quality);

	/**
  * @brief	This method assignes \a main_hand to the \a player.
		If \a main_hand is different than #LEFT_HAND and #RIGHT_HAND, it will be set on #RIGHT_HAND.
		Must be called after playerCreate(), not before.
  * @param	PLAYER*	Pointer to structure \ref player whom we want to assign \a quality.
  * @param	uint8_t	The main_hand to assign to the \a player.
  * @retval	void	
  */
  void assignPlayerMainHand(PLAYER* player, uint8_t main_hand);
  void increaseQuality (PLAYER* player);
  void decreaseQuality (PLAYER* player);
  void playerDelete (PLAYER* player);

#endif

