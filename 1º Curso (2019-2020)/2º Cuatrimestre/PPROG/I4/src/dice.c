/**
* @brief It implements the die interface
*
* @file dice.c
* @author David Teófilo Garitagoitia Romero
* @version 1.0
* @date 20-02-2020
* @copyright GNU Public License
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../include/types.h"
#include "../include/dice.h"
/**
* @brief The die structure
*
* It stores information of a die
*/
struct _Dice
{
  Id id; /*!< identifier of the dice */
  int max;  /*!< the maximumvalue of the roll */
  int min; /*!< the minimum the value of the roll */
  int last;   /*!< value of the last roll */
};
Dice *dice_create(Id id, int max, int min){
  Dice *newDice = NULL;
  if (id == NO_ID || min>max) /*it's checked if there is an error*/
    return NULL;
  newDice = (Dice *)malloc(sizeof(Dice));
  if (newDice == NULL)
  { /*it's checked if there is an error*/
    return NULL;
  }
  srand (time(0));
  newDice->id = id;
  newDice->max = max;
  newDice->min = min ;
  newDice->last = 0;
  return newDice;
}

STATUS dice_destroy(Dice *dice)
{
  /* 
 First it's checked if is something wrong with the Dice that we want to free,  if there is no error the Dice is released
*/
  if (!dice)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  free(dice);
  return OK;
}

int dice_roll(Dice *dice){
  if(!dice){
    return -1;
  }
  dice->last = rand() % (dice->max-dice->min + 1) + dice->min;
  /*dice->last=rand()%dice->max;*/
  return dice->last;
}

int dice_get_last(Dice *dice){
  if(!dice){
    return -1;
  }
  return dice->last;
}

STATUS dice_print(Dice *dice){
  if(!dice){
    return ERROR;
  }
  printf("%ld:\n", dice->id);
  printf("%d %d %d", dice->last, dice->max, dice->min);
  return OK;
}
