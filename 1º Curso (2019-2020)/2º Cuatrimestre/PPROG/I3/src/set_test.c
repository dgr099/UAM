/** 
 * @brief test to see if set works correctly
 * 
 * @file set_test.c
 * @author Daniel Cerrato Sánchez
 * @version 2.0 
 * @date 09-06-2020
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include "../include/set.h"
#include "../include/test.h"
#include "../include/set_test.h"
/*! \def MAX_TESTS
    \brief maximum number of test
   
    Details.
*/
#define MAX_TESTS 13
/**
* @brief the main function of set_test
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
    printf("Running all test for module Set:\n");
  } else {
      test = atoi(argv[1]);
      all = 0;
      printf("Running test %d:\t", test);
      if (test < 1 && test > MAX_TESTS) {
        printf("Error: unknown test %d\t", test);
	exit(EXIT_SUCCESS);
      }
  }

   if (all || test == 1) test1_set_create();
   if (all || test == 2) test2_set_create();
   if (all || test == 3) test1_set_add();
   if (all || test == 4) test2_set_add();
   if (all || test == 5) test1_set_dell();
   if (all || test == 6) test2_set_dell();
   if (all || test == 7) test3_set_dell();
   if (all || test == 8) test1_set_get_num();
   if (all || test == 9) test2_set_get_num();
   if (all || test == 10) test1_set_find_index();
   if (all || test == 11) test2_set_find_index();
   if (all || test == 12) test1_set_get_id_at_position();
   if (all || test == 13) test1_set_get_id_at_position();

  PRINT_PASSED_PERCENTAGE;
  return 0;
}

void test1_set_create() {
  int result = set_create()!=NULL ;
  PRINT_TEST_RESULT(result);
}

void test2_set_create() {
  Set* set = set_create() ;
  PRINT_TEST_RESULT(set_get_num(set)==0);
}

void test1_set_add() {
  Set *set = set_create();
  PRINT_TEST_RESULT(set_add(set, 1)==OK);
}

void test2_set_add() {
  Set *set = NULL;
  PRINT_TEST_RESULT(set_add(set, 1)==ERROR);
}

void test1_set_dell() {
  Set *set = set_create();
  set_add(set, 1);
  PRINT_TEST_RESULT(set_dell(set, 1)==OK);
}

void test2_set_dell() {
  Set *set = set_create();
  set_add(set, 1);
  PRINT_TEST_RESULT(set_dell(set, 2)==ERROR);
}

void test3_set_dell() {
  Set *set = NULL;
  PRINT_TEST_RESULT(set_dell(set, 1)==ERROR);
}

void test1_set_get_num() { 
  Set *set = set_create();
  set_add(set, 2);
  PRINT_TEST_RESULT(set_get_num(set)==1);
}

void test2_set_get_num() { 
  Set *set = NULL;
  PRINT_TEST_RESULT(set_get_num(set)==-1);
}

void test1_set_find_index() {
  Set *set = set_create();
  set_add(set, 2);
  PRINT_TEST_RESULT(set_find_index(set, 2)==0);
}

void test2_set_find_index() {
  Set *set = set_create();
  set_add(set, 2);
  PRINT_TEST_RESULT(set_find_index(set, 1)==-1);
}

void test1_set_get_id_at_position(){
  Set *set = set_create();
  set_add(set, 2);
  PRINT_TEST_RESULT(set_get_id_at_position(set, 0)==2);
}

void test2_set_get_id_at_position(){
  Set *set = set_create();
  set_add(set, 2);
  PRINT_TEST_RESULT(set_get_id_at_position(set, 1)==-1);
}
