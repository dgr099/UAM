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
#define MAX_TESTS 12
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
  if (all || test == 2) test2_object_create();
  if (all || test == 3) test1_object_set_name();
  if (all || test == 4) test2_object_set_name();
  if (all || test == 5) test1_object_set_description();
  if (all || test == 6) test2_object_set_description();
  if (all || test == 7) test1_object_get_description();
  if (all || test == 8) test2_object_get_description();
  if (all || test == 9) test1_object_get_id();
  if (all || test == 10) test2_object_get_id();
  if (all || test == 11) test1_object_get_name();
  if (all || test == 12) test2_object_get_name();

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

