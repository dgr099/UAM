/** 
 * @brief test to see if set works correctly
 * 
 * @file cmdAnswer_test.c
 * @author David Teófilo Garitagoitia Romero
 * @version 1.0 
 * @date 7-5-2020
 * @copyright GNU Public License
 */
#include "../include/cmdAnswer.h"
#include "../include/test.h"
#include "../include/cmdAnswer_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*! \def MAX_TESTS
    \brief maximum number of test
   
    Details.
*/
#define MAX_TESTS 14

/**
* @brief the main function of cmdAnswer_test
** main
*
* @date 20-03-2020 
* @author David Teófilo Garitagoitia Romero
* @return
*/
int main(int argc, char **argv){

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module cmdAnswer:\n");
  } else {
      test = atoi(argv[1]);
      all = 0;
      printf("Running test %d:\t", test);
      if (test < 1 && test > MAX_TESTS) {
        printf("Error: unknown test %d\t", test);
	exit(EXIT_SUCCESS);
      }
  }

  if (all || test == 1) test1_CmdAnswer_init();
  if (all || test == 2) test1_CmdAnswer_add_error_at();
  if (all || test == 3) test2_CmdAnswer_add_error_at();
  if (all || test == 4) test3_CmdAnswer_add_error_at();
  if (all || test == 5) test4_CmdAnswer_add_error_at();
  if (all || test == 6) test1_CmdAnser_add_ok();
  if (all || test == 7) test2_CmdAnser_add_ok();
  if (all || test == 8) test3_CmdAnser_add_ok();
  if (all || test == 9) test1_CmdAnswer_get_random_error();
  if (all || test == 10) test2_CmdAnswer_get_random_error();
  if (all || test == 11) test3_CmdAnswer_get_random_error();
  if (all || test == 12) test1_CmdAnswer_get_random_ok();
  if (all || test == 13) test2_CmdAnswer_get_random_ok();



  PRINT_PASSED_PERCENTAGE;
  return 0;
}

void test1_CmdAnswer_init(){
  CmdAnswer *cmda;
  cmda=CmdAnswer_init();
  PRINT_TEST_RESULT(cmda!=NULL);
}

void test1_CmdAnswer_add_new_error(){
  CmdAnswer *cmda;
  cmda=CmdAnswer_init();
  PRINT_TEST_RESULT(CmdAnswer_add_new_error(cmda)==OK);
}

void test2_CmdAnswer_add_new_error(){
  CmdAnswer *cmda=NULL;
  PRINT_TEST_RESULT(CmdAnswer_add_new_error(cmda)==ERROR);
}

void test1_CmdAnswer_add_error_at(){
  CmdAnswer *cmda=NULL;
  PRINT_TEST_RESULT(CmdAnswer_add_error_at(cmda, "ERROR", 0)==ERROR);
}

void test2_CmdAnswer_add_error_at(){
  CmdAnswer *cmda=NULL;
  cmda=CmdAnswer_init();
  PRINT_TEST_RESULT(CmdAnswer_add_error_at(cmda,"Te pasas", 1)==ERROR);
}

void test3_CmdAnswer_add_error_at(){
  CmdAnswer *cmda=NULL;
  cmda=CmdAnswer_init();
  PRINT_TEST_RESULT(CmdAnswer_add_error_at(cmda,"OK", 0)==OK);
}

void test4_CmdAnswer_add_error_at(){
  CmdAnswer *cmda=NULL;
  cmda=CmdAnswer_init();
  PRINT_TEST_RESULT(CmdAnswer_add_error_at(cmda,NULL, 0)==ERROR);
}

void test1_CmdAnser_add_ok(){
  CmdAnswer *cmda=NULL;
  PRINT_TEST_RESULT(CmdAnswer_add_ok(cmda, "Esto no")==ERROR);
}

void test2_CmdAnser_add_ok(){
  CmdAnswer *cmda=NULL;
  cmda=CmdAnswer_init();
  PRINT_TEST_RESULT(CmdAnswer_add_ok(cmda, "Esto si")==OK);
}

void test3_CmdAnser_add_ok(){
  CmdAnswer *cmda=NULL;
  cmda=CmdAnswer_init();
  PRINT_TEST_RESULT(CmdAnswer_add_ok(cmda, NULL)==ERROR);
}

void test1_CmdAnswer_get_random_error(){
  CmdAnswer *cmda;
  char *error;
  cmda=CmdAnswer_init();
  CmdAnswer_add_error_at(cmda, "ERROR", 0);
  CmdAnswer_add_error_at(cmda, "ERROR_2", 0);
  error=CmdAnswer_get_random_error(cmda, 0);
  PRINT_TEST_RESULT((strcmp(error, "ERROR")==0 || strcmp(error, "ERROR_2")==0));
}

void test2_CmdAnswer_get_random_error(){
  CmdAnswer *cmda;
  cmda=CmdAnswer_init();
  CmdAnswer_add_error_at(cmda, "ERROR", 0);
  CmdAnswer_add_error_at(cmda, "ERROR_2", 0);
  PRINT_TEST_RESULT(CmdAnswer_get_random_error(cmda, 1)==NULL);
}

void test3_CmdAnswer_get_random_error(){
  CmdAnswer *cmda=NULL;
  cmda=CmdAnswer_init();
  PRINT_TEST_RESULT(CmdAnswer_get_random_error(cmda, 1)==NULL);
}


void test1_CmdAnswer_get_random_ok(){
  CmdAnswer *cmda;
  cmda=CmdAnswer_init();
  CmdAnswer_add_ok(cmda, "OK");
  CmdAnswer_add_ok(cmda, "OK_2");
  PRINT_TEST_RESULT(CmdAnswer_get_random_ok(cmda)!=NULL);
}

void test2_CmdAnswer_get_random_ok(){
  CmdAnswer *cmda=NULL;
  PRINT_TEST_RESULT(CmdAnswer_get_random_ok(cmda)==NULL);
}
