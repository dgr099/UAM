/** 
 * @brief test to see if inventory works correctly
 * 
 * @file inventory_test.c
 * @author Daniel Cerrato Sánchez
 * @version 2.0 
 * @date 10-06-2020
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/inventory.h"
#include "../include/test.h"
#include "../include/inventory_test.h"

/*! \def MAX_TESTS
    \brief maximum number of test
   
    Details.
*/
#define MAX_TESTS 24

/**
* @brief the main function of inventory_test
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
    printf("Running all test for module Inventory:\n");
  } else {
      test = atoi(argv[1]);
      all = 0;
      printf("Running test %d:\t", test);
      if (test < 1 && test > MAX_TESTS) {
        printf("Error: unknown test %d\t", test);
	exit(EXIT_SUCCESS);
      }
  }

  if (all || test == 1) test1_inventory_create();
  if (all || test == 2) test2_inventory_create();
  if (all || test == 3) test1_inventory_get_inside();
  if (all || test == 4) test2_inventory_get_inside();
  if (all || test == 5) test1_inventory_add();
  if (all || test == 6) test2_inventory_add();
  if (all || test == 7) test3_inventory_add();
  if (all || test == 8) test1_inventory_dell();
  if (all || test == 9) test2_inventory_dell();
  if (all || test == 10) test3_inventory_dell();
  if (all || test == 11) test1_inventory_is_object();
  if (all || test == 12) test2_inventory_is_object();
  if (all || test == 13) test3_inventory_is_object();
  if (all || test == 14) test4_inventory_is_object();
  if (all || test == 15) test1_inventory_get_max();
  if (all || test == 16) test2_inventory_get_max();
  if (all || test == 17) test1_inventory_is_full();
  if (all || test == 18) test2_inventory_is_full();
  if (all || test == 19) test3_inventory_is_full();
  if (all || test == 20) test1_inventory_is_emty();
  if (all || test == 21) test2_inventory_is_emty();
  if (all || test == 22) test3_inventory_is_emty();
  if (all || test == 23) test1_inventory_get_id();
  if (all || test == 24) test2_inventory_get_id();

  PRINT_PASSED_PERCENTAGE;
  return 0;
}

void test1_inventory_create(){
  int result = inventory_create(101, 2)!=NULL;
  PRINT_TEST_RESULT(result);
}

void test2_inventory_create(){
  Inventory *inventory = inventory_create(101, 2);
  PRINT_TEST_RESULT(inventory_get_id(inventory)==101);
}

void test1_inventory_get_inside(){
  Inventory *inventory = inventory_create(101, 2);
  PRINT_TEST_RESULT(inventory_get_inside(inventory)!=NULL);
}

void test2_inventory_get_inside(){
  Inventory *inventory = NULL;
  PRINT_TEST_RESULT(inventory_get_inside(inventory)==NULL);
}

void test1_inventory_add(){
  Inventory *inventory = inventory_create(101, 2);
  PRINT_TEST_RESULT(inventory_add(inventory, 1)==OK);
}

void test2_inventory_add(){
  Inventory *inventory = inventory_create(101, 2);
  PRINT_TEST_RESULT(inventory_add(inventory, NO_ID)==ERROR);
}

void test3_inventory_add(){
  Inventory *inventory = NULL;
  PRINT_TEST_RESULT(inventory_add(inventory, 1)==ERROR);
}

void test1_inventory_dell(){
  Inventory *inventory = inventory_create(101, 2);
  inventory_add(inventory, 1);
  PRINT_TEST_RESULT(inventory_dell(inventory, 1)==OK);
}

void test2_inventory_dell(){
  Inventory *inventory = inventory_create(101, 2);
  PRINT_TEST_RESULT(inventory_dell(inventory, 1)==ERROR);
}

void test3_inventory_dell(){
  Inventory *inventory = NULL;
  PRINT_TEST_RESULT(inventory_dell(inventory, 1)==ERROR);
}

void test1_inventory_is_object(){
  Inventory *inventory = inventory_create(101, 2);
  inventory_add(inventory, 1);
  PRINT_TEST_RESULT(inventory_is_object(inventory,1)==TRUE);
}

void test2_inventory_is_object(){
  Inventory *inventory = inventory_create(101, 2);
  PRINT_TEST_RESULT(inventory_is_object(inventory,1)==FALSE);
}

void test3_inventory_is_object(){
  Inventory *inventory = inventory_create(101, 2);
  inventory_add(inventory, 1);
  PRINT_TEST_RESULT(inventory_is_object(inventory,NO_ID)==FALSE);
}

void test4_inventory_is_object(){
  Inventory *inventory = NULL;
  PRINT_TEST_RESULT(inventory_is_object(inventory,1)==FALSE);
}

void test1_inventory_get_max(){
  Inventory *inventory = inventory_create(101, 2);
  PRINT_TEST_RESULT(inventory_get_max(inventory)==2);
}

void test2_inventory_get_max(){
  Inventory *inventory = NULL;
  PRINT_TEST_RESULT(inventory_get_max(inventory)==-1);
}

void test1_inventory_is_full(){
  Inventory *inventory = inventory_create(101, 1);
  inventory_add(inventory,2);
  PRINT_TEST_RESULT(inventory_is_full(inventory)==TRUE);
}

void test2_inventory_is_full(){
  Inventory *inventory = inventory_create(101, 1);
  PRINT_TEST_RESULT(inventory_is_full(inventory)==FALSE);
}

void test3_inventory_is_full(){
  Inventory *inventory = NULL;
  PRINT_TEST_RESULT(inventory_is_full(inventory)==TRUE);
}

void test1_inventory_is_emty(){
  Inventory *inventory = inventory_create(101, 1);
  PRINT_TEST_RESULT(inventory_is_emty(inventory)==TRUE);
}

void test2_inventory_is_emty(){
  Inventory *inventory = inventory_create(101, 1);
  inventory_add(inventory,2);
  PRINT_TEST_RESULT(inventory_is_emty(inventory)==FALSE);
}

void test3_inventory_is_emty(){
  Inventory *inventory = NULL;
  PRINT_TEST_RESULT(inventory_is_emty(inventory)==TRUE);
}

void test1_inventory_get_id(){
  Inventory *inventory = inventory_create(101, 1);
  PRINT_TEST_RESULT(inventory_get_id(inventory)==101);
}

void test2_inventory_get_id(){
  Inventory *inventory = NULL;
  PRINT_TEST_RESULT(inventory_get_id(inventory)==NO_ID);
}

