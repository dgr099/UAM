/** 
 * @brief test to see if dice works correctly
 * 
 * @file dice_test.c
* @author Daniel Cerrato Sánchez
 * @version 2.0 
 * @date 10-06-2020
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include "../include/test.h"
#include "../include/dice.h"
#include "../include/dice_test.h"

/*! \def MAX_TESTS
    \brief maximum number of test
   
    Details.
*/
#define MAX_TESTS 9

/**
* @brief the main function of dice_test
** main
*
* @date 10-06-2020 
* @author Daniel Cerrato Sánchez
* @return
*/
int main(int argc, char **argv){

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Dice:\n");
  } else {
      test = atoi(argv[1]);
      all = 0;
      printf("Running test %d:\t", test);
      if (test < 1 && test > MAX_TESTS) {
        printf("Error: unknown test %d\t", test);
	exit(EXIT_SUCCESS);
      }
  }

  if (all || test == 1) test1_dice_create();
  if (all || test == 2) test2_dice_create();
  if (all || test == 3) test1_dice_roll();
  if (all || test == 4) test2_dice_roll();
  if (all || test == 5) test3_dice_roll();
  if (all || test == 6) test1_dice_get_last();
  if (all || test == 7) test2_dice_get_last();
  if (all || test == 8) test3_dice_get_last();
  if (all || test == 9) test4_dice_get_last();

  PRINT_PASSED_PERCENTAGE;
  return 0;
}

void test1_dice_create(){
  int result = dice_create(101,6,1)!=NULL;
  PRINT_TEST_RESULT(result);
}

void test2_dice_create(){
  int result = dice_create(101,1,6)==NULL;
  PRINT_TEST_RESULT(result);
}

void test1_dice_roll(){
  Dice *dice = dice_create(101,6,1);
  PRINT_TEST_RESULT(dice_roll(dice)>=1);
}

void test2_dice_roll(){
  Dice *dice = dice_create(101,6,1);
  PRINT_TEST_RESULT(dice_roll(dice)<=6);
}

void test3_dice_roll(){
  Dice *dice = NULL;
  PRINT_TEST_RESULT(dice_roll(dice)==-1);
}

void test1_dice_get_last(){
  Dice *dice = dice_create(101,6,1);
  dice_roll(dice);
  PRINT_TEST_RESULT(dice_get_last(dice)>=1);
}

void test2_dice_get_last(){
  Dice *dice = dice_create(101,6,1);
  dice_roll(dice);
  PRINT_TEST_RESULT(dice_get_last(dice)<=6);
}

void test3_dice_get_last(){
  Dice *dice = dice_create(101,6,1);
  PRINT_TEST_RESULT(dice_get_last(dice)==0);
}

void test4_dice_get_last(){
  Dice *dice = NULL;
  PRINT_TEST_RESULT(dice_get_last(dice)==-1);
}
