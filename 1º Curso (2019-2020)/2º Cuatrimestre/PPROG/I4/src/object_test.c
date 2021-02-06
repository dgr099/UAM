/** 
 * @brief test to see if object works correctly
 * 
 * @file object_test.c
 * @author Daniel Cerrato Sánchez
 * @version 2.0 
 * @date 10-06-2020
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/object.h"
#include "../include/test.h"
#include "../include/object_test.h"

/*! \def MAX_TESTS
    \brief maximum number of test
   
    Details.
*/
#define MAX_TESTS 34
/**
* @brief the main function of object_test
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
    printf("Running all test for module Object:\n");
  } else {
      test = atoi(argv[1]);
      all = 0;
      printf("Running test %d:\t", test);
      if (test < 1 && test > MAX_TESTS) {
        printf("Error: unknown test %d\t", test);
	exit(EXIT_SUCCESS);
      }
  }
  
  if (all || test == 1) test1_object_create();
  if (all || test == 3) test2_object_create();
  if (all || test == 4) test3_object_create();
  if (all || test == 5) test4_object_create();
  if (all || test == 6) test5_object_create();
  if (all || test == 7) test6_object_create();
  if (all || test == 8) test7_object_create();
  if (all || test == 9) test8_object_create();
  if (all || test == 10) test9_object_create();
  if (all || test == 11) test1_object_set_name();
  if (all || test == 12) test2_object_set_name();
  if (all || test == 13) test1_object_set_description();
  if (all || test == 14) test2_object_set_description();
  if (all || test == 15) test1_object_get_description();
  if (all || test == 16) test2_object_get_description();
  if (all || test == 17) test1_object_get_id();
  if (all || test == 18) test2_object_get_id();
  if (all || test == 19) test1_object_get_name();
  if (all || test == 20) test2_object_get_name();
  if (all || test == 20) test1_object_set_movable();
  if (all || test == 21) test2_object_set_movable();
  if (all || test == 22) test1_object_get_movable();
  if (all || test == 23) test2_object_get_movable();
  if (all || test == 24) test1_object_set_dependency();
  if (all || test == 25) test2_object_set_dependency();
  if (all || test == 26) test1_object_get_dependency();
  if (all || test == 27) test2_object_get_dependency();
  if (all || test == 28) test1_object_set_incompatible();
  if (all || test == 29) test2_object_set_incompatible();
  if (all || test == 30) test1_object_get_incompatible();
  if (all || test == 31) test2_object_get_incompatible();
  if (all || test == 32) test1_object_turned();
  if (all || test == 33) test2_object_turned();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_object_create(){
  int result = object_create(1)!=NULL;
  PRINT_TEST_RESULT(result);
}

void test2_object_create(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_get_id(object)==1);
}

void test3_object_create(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_get_movable(object)==TRUE);
}

void test4_object_create(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_get_hidden(object)==TRUE);
}

void test5_object_create(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_get_illuminate(object)==FALSE);
}

void test6_object_create(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_get_open(object)==NO_ID);
}

void test7_object_create(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_get_turned(object)==FALSE);
}

void test8_object_create(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_get_dependency(object)==NO_ID);
}

void test9_object_create(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_get_incompatible(object)==NO_ID);
}

void test1_object_set_name(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_set_name(object, "Libro")==OK);
}

void test2_object_set_name(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_set_name(object, NULL)==ERROR);
}

void test1_object_set_description(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_set_description(object, "Un libro de magia")==OK);
}

void test2_object_set_description(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_set_description(object, NULL)==ERROR);
}

void test1_object_get_description(){
  Object *object = object_create(1);
  object_set_description(object, "Un libro de magia");
  PRINT_TEST_RESULT(strcmp("Un libro de magia", object_get_description(object))==0);
}

void test2_object_get_description(){
  Object *object = NULL;
  PRINT_TEST_RESULT(object_get_description(object)==NULL);
}

void test1_object_get_id(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_get_id(object)==1);
}

void test2_object_get_id(){
  Object *object = NULL;
  PRINT_TEST_RESULT(object_get_id(object)==NO_ID);
}

void test1_object_get_name(){
  Object *object = object_create(1);
  object_set_name(object, "Libro");
  PRINT_TEST_RESULT(strcmp("Libro", object_get_name(object))==0);
}

void test2_object_get_name(){
  Object *object = NULL;
  PRINT_TEST_RESULT(object_get_name(object)==NULL);
}

void test1_object_set_movable(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_set_movable(object, TRUE)==OK);
}

void test2_object_set_movable(){
  Object *object = NULL;
  PRINT_TEST_RESULT(object_set_movable(object, TRUE)==ERROR);
}

void test1_object_get_movable(){
  Object *object = object_create(1);
  object_set_movable(object, TRUE);
  PRINT_TEST_RESULT(object_get_movable(object)==TRUE);  
}

void test2_object_get_movable(){
  Object *object = NULL;
  PRINT_TEST_RESULT(object_get_movable(object)==FALSE);  
}

void test1_object_set_dependency(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_set_dependency(object, 3)==OK);
}

void test2_object_set_dependency(){
  Object *object = NULL;
  PRINT_TEST_RESULT(object_set_dependency(object, 3)==ERROR);
}

void test1_object_get_dependency(){
  Object *object = object_create(1);
  object_set_dependency(object, 3);
  PRINT_TEST_RESULT(object_get_dependency(object)==3);
}

void test2_object_get_dependency(){
  Object *object = NULL;
  PRINT_TEST_RESULT(object_get_dependency(object)==NO_ID);
}

void test1_object_set_incompatible(){
  Object *object = object_create(1);
  PRINT_TEST_RESULT(object_set_incompatible(object, 3)==OK);
}

void test2_object_set_incompatible(){
  Object *object = NULL;
  PRINT_TEST_RESULT(object_set_incompatible(object, 3)==ERROR);
}

void test1_object_get_incompatible(){
  Object *object = object_create(1);
  object_set_incompatible(object, 3);
  PRINT_TEST_RESULT(object_get_incompatible(object)==3);
}

void test2_object_get_incompatible(){
  Object *object = NULL;
  PRINT_TEST_RESULT(object_get_incompatible(object)==NO_ID);
}

void test1_object_turned(){
  Object *object;
  object=object_create(3);
  PRINT_TEST_RESULT(object_turned(object, TRUE)==OK);
}

void test2_object_turned(){
  Object *object=NULL;
  PRINT_TEST_RESULT(object_turned(object, TRUE)==ERROR);
}

void test1_object_get_turned(){
  Object *object;
  object=object_create(5);
  object_turned(object, TRUE);
  PRINT_TEST_RESULT(object_get_turned(object)==TRUE);
}