/** 
 * @brief test to see if player works correctly
 * 
 * @file player_test.c
 * @author Daniel Cerrato Sánchez
 * @version 2.0 
 * @date 09-06-2020
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/player.h"
#include "../include/test.h"
#include "../include/player_test.h"

/*! \def MAX_TESTS
    \brief maximum number of test
   
    Details.
*/
#define MAX_TESTS 23

/**
* @brief the main function of player_test
** main
*
* @date 09-06-2020 
* @author Daniel Cerrato Sánchez
* @return
*/
int main(int argc, char **argv){

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Player:\n");
  } else {
      test = atoi(argv[1]);
      all = 0;
      printf("Running test %d:\t", test);
      if (test < 1 && test > MAX_TESTS) {
        printf("Error: unknown test %d\t", test);
	exit(EXIT_SUCCESS);
      }
  }

   if (all || test == 1) test1_player_create();
   if (all || test == 2) test2_player_create();
   if (all || test == 3) test1_player_add_object();
   if (all || test == 4) test2_player_add_object();
   if (all || test == 5) test3_player_add_object();
   if (all || test == 6) test1_player_dell_object();
   if (all || test == 7) test2_player_dell_object();
   if (all || test == 8) test3_player_dell_object();
   if (all || test == 9) test4_player_dell_object();
   if (all || test == 10) test1_player_set_name();
   if (all || test == 11) test2_player_set_name();
   if (all || test == 12) test1_player_get_name();
   if (all || test == 13) test2_player_get_name();
   if (all || test == 14) test1_player_set_location();
   if (all || test == 15) test2_player_set_location();
   if (all || test == 16) test1_player_get_location();
   if (all || test == 17) test2_player_get_location();
   if (all || test == 18) test1_player_set_id();
   if (all || test == 19) test2_player_set_id();
   if (all || test == 20) test1_player_get_id();
   if (all || test == 21) test2_player_get_id();
   if (all || test == 22) test1_player_get_inventory();
   if (all || test == 23) test2_player_get_inventory();

  PRINT_PASSED_PERCENTAGE;
  return 0;
}


void test1_player_create(){
  int result = player_create(0,3)!=NULL;
  PRINT_TEST_RESULT(result);
}

void test2_player_create(){
  Player *player = player_create(0,3);
  PRINT_TEST_RESULT(player_get_id(player)==0);
}

void test1_player_add_object(){
  Player *player = player_create(0,3);
  Object *object = object_create(1);
  PRINT_TEST_RESULT(player_add_object(player, object)==OK);
}

void test2_player_add_object(){
  Player *player = player_create(0,3);
  Object *object = NULL;
  PRINT_TEST_RESULT(player_add_object(player, object)==ERROR);
}

void test3_player_add_object(){
  Player *player = NULL;
  Object *object = object_create(1);
  PRINT_TEST_RESULT(player_add_object(player, object)==ERROR);
}

void test1_player_dell_object(){
  Player *player = player_create(0,3);
  Object *object = object_create(1);
  player_add_object(player, object);
  PRINT_TEST_RESULT(player_dell_object(player, object)==OK);
}

void test2_player_dell_object(){
  Player *player = player_create(0,3);
  Object *object = object_create(1);
  PRINT_TEST_RESULT(player_dell_object(player, object)==ERROR);
}

void test3_player_dell_object(){
  Player *player = player_create(0,3);
  Object *object = object_create(1), *object2 = object_create(2);
  player_add_object(player, object);
  PRINT_TEST_RESULT(player_dell_object(player, object2)==ERROR);
}

void test4_player_dell_object(){
  Player *player = NULL;
  Object *object = object_create(1);
  PRINT_TEST_RESULT(player_dell_object(player, object)==ERROR);
}

void test1_player_set_name(){
  Player *player = player_create(0,3);
  PRINT_TEST_RESULT(player_set_name(player, "PRUEBA")==OK);
}

void test2_player_set_name(){
  Player *player = player_create(0,3);
  PRINT_TEST_RESULT(player_set_name(player, NULL)==ERROR);
}

void test1_player_get_name(){
  Player *player = player_create(0,3);
  player_set_name(player,"PRUEBA");
  PRINT_TEST_RESULT(strcmp(player_get_name(player), "PRUEBA")==0);
}

void test2_player_get_name(){
  Player *player = NULL;
  PRINT_TEST_RESULT(player_get_name(player)==NULL);
}

void test1_player_set_location(){
  Player *player = player_create(0,3);
  PRINT_TEST_RESULT(player_set_location(player, 4)==OK);
}

void test2_player_set_location(){
  Player *player = NULL;
  PRINT_TEST_RESULT(player_set_location(player, 4)==ERROR);
}

void test1_player_get_location(){
  Player *player = player_create(0,3);
  player_set_location(player, 4);
  PRINT_TEST_RESULT(player_get_location(player)==4);
}

void test2_player_get_location(){
  Player *player = NULL;
  PRINT_TEST_RESULT(player_get_location(player)==NO_ID);
}

void test1_player_set_id(){
  Player *player = player_create(0,3);
  PRINT_TEST_RESULT(player_set_id(player,1)==OK);
}

void test2_player_set_id(){
  Player *player = NULL;
  PRINT_TEST_RESULT(player_set_id(player,1)==ERROR);
}

void test1_player_get_id(){
  Player *player = player_create(0,3);
  PRINT_TEST_RESULT(player_get_id(player)==0);
}

void test2_player_get_id(){
  Player *player = NULL;
  PRINT_TEST_RESULT(player_get_id(player)==NO_ID);
}

void test1_player_get_inventory(){
  Player *player = player_create(0,3);
  PRINT_TEST_RESULT(player_get_inventory(player)!=NULL);
}

void test2_player_get_inventory(){
  Player *player = NULL;
  PRINT_TEST_RESULT(player_get_inventory(player)==NULL);
}
