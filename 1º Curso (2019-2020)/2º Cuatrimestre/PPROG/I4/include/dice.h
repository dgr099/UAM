/** 
 * @brief It defines the dice interface
 * for each command
 * 
 * @file dice.h
 * @author David Teófilo Garitagoitia Romero
 * @version 1.0 
 * @date 20-02-2020 
 * @copyright GNU Public License
 */
#ifndef DICE_H
#define DICE_H
#include "../include/types.h"
#include <stdio.h>
/*! \var typedef struct _Dice Dice
    \brief A type definition for a dice.
    
    Details.
*/
typedef struct _Dice Dice;
/**
*@brief Create a dice
*
* dice_create Create a dice with a specific Id, max and min
*
* @date 20-02-2019
* @author David Teófilo Garitagoitia Romero
*
* @param id the id of the new dice
* @param max the maximum of the dice
* @param min the minimum of the dice
* @return the new dice that has been created
*/
Dice *dice_create(Id id, int max, int min);
/**
* @brief free a dice
*
* dice_destroy free a especific dice 
*
* @date 20-02-2019
* @author David Teófilo Garitagoitia Romero
*
* @param dice a dice that has been created before
* @return ERROR if there is an error, otherwise return OK
*/
STATUS dice_destroy(Dice *dice);
/**
* @brief roll a dice
*
* dice_roll roll a especific dice 
*
* @date 20-02-2019
* @author David Teófilo Garitagoitia Romero
*
* @param dice a dice which you want to roll
* @return -1 if there is an error, otherwise return the number of the roll
*/
int dice_roll(Dice *dice);
/**
* @brief print a dice
*
* dice_print print a especific dice 
*
* @date 20-02-2019
* @author David Teófilo Garitagoitia Romero
*
* @param dice a dice which you want to print
* @return -1 if there is an error, otherwise return the number of the roll
*/
STATUS dice_print(Dice *dice);
/**
* @brief get the last roll value
*
* dice_get_last 
*
* @date 20-02-2019
* @author David Teófilo Garitagoitia Romero
*
* @param dice a dice that has been created before
* @return -1 if there is an error, otherwise return the last roll value
*/
int dice_get_last(Dice *dice);
#endif
