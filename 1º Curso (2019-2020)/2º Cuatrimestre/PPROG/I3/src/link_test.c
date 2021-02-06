/** 
 * @brief test to see if links works correctly
 * 
 * @file link_test.c
 * @author Daniel Cerrato Sánchez
 * @version 2.0
 * @date 10-06-2020
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/link.h"
#include "../include/test.h"
#include "../include/link_test.h"

/*! \def MAX_TESTS
    \brief maximum number of test
   
    Details.
*/
#define MAX_TESTS 22

/**
* @brief the main function of link_test
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
    printf("Running all test for module Link:\n");
  } else {
      test = atoi(argv[1]);
      all = 0;
      printf("Running test %d:\t", test);
      if (test < 1 && test > MAX_TESTS) {
        printf("Error: unknown test %d\t", test);
	exit(EXIT_SUCCESS);
      }
  }

  if (all || test == 1) test1_link_create();
  if (all || test == 2) test2_link_create();
  if (all || test == 3) test1_link_set_name();
  if (all || test == 4) test2_link_set_name();
  if (all || test == 5) test1_link_set_id1();
  if (all || test == 6) test2_link_set_id1();
  if (all || test == 7) test1_link_set_id2();
  if (all || test == 8) test2_link_set_id2();
  if (all || test == 9) test1_link_set_open();
  if (all || test == 10) test2_link_set_open();
  if (all || test == 11) test3_link_set_open();
  if (all || test == 12) test1_link_get_id();
  if (all || test == 13) test2_link_get_id();
  if (all || test == 14) test1_link_is_open();
  if (all || test == 15) test2_link_is_open();
  if (all || test == 16) test3_link_is_open();
  if (all || test == 17) test1_link_get_id1();
  if (all || test == 18) test2_link_get_id1();
  if (all || test == 19) test1_link_get_id2();
  if (all || test == 20) test2_link_get_id2();
  if (all || test == 21) test1_link_get_name();
  if (all || test == 22) test2_link_get_name();

  PRINT_PASSED_PERCENTAGE;
  return 0;
}

void test1_link_create(){
  int result = link_create(1)!=NULL;
  PRINT_TEST_RESULT(result);
}

void test2_link_create(){
  Link *link = link_create(1);
  PRINT_TEST_RESULT(link_get_id(link)==1);
}

void test1_link_set_name(){
  Link *link = link_create(1);
  PRINT_TEST_RESULT(link_set_name(link, "enlace de prueba")==OK);
}

void test2_link_set_name(){
  Link *link = link_create(1);
  PRINT_TEST_RESULT(link_set_name(link, NULL)==ERROR);
}

void test1_link_set_id1(){
  Link *link = link_create(1);
  PRINT_TEST_RESULT(link_set_id1(link, 2)==OK);
}

void test2_link_set_id1(){
  Link *link = NULL;
  PRINT_TEST_RESULT(link_set_id1(link, 2)==ERROR);
}

void test1_link_set_id2(){
  Link *link = link_create(1);
  PRINT_TEST_RESULT(link_set_id2(link, 3)==OK);
}

void test2_link_set_id2(){
  Link *link = NULL;
  PRINT_TEST_RESULT(link_set_id2(link, 3)==ERROR);
}

void test1_link_set_open(){
  Link *link = link_create(1);
  PRINT_TEST_RESULT(link_set_open(link, 0)==OK);
}

void test2_link_set_open(){
  Link *link = link_create(1);
  PRINT_TEST_RESULT(link_set_open(link, 1)==OK);
}

void test3_link_set_open(){
  Link *link = NULL;
  PRINT_TEST_RESULT(link_set_open(link, 0)==ERROR);
}

void test1_link_get_id(){
  Link *link = link_create(1);
  PRINT_TEST_RESULT(link_get_id(link)==1);
}

void test2_link_get_id(){
  Link *link = NULL;
  PRINT_TEST_RESULT(link_get_id(link)==NO_ID);
}

void test1_link_is_open(){
  Link *link = link_create(1);
  link_set_open(link,0);
  PRINT_TEST_RESULT(link_is_open(link)==TRUE);
}

void test2_link_is_open(){
  Link *link = link_create(1);
  link_set_open(link,1);
  PRINT_TEST_RESULT(link_is_open(link)==FALSE);
}

void test3_link_is_open(){
  Link *link = NULL;
  PRINT_TEST_RESULT(link_is_open(link)==FALSE);
}

void test1_link_get_id1(){
  Link *link = link_create(1);
  link_set_id1(link,2);
  PRINT_TEST_RESULT(link_get_id1(link)==2);
}

void test2_link_get_id1(){
  Link *link = NULL;
  PRINT_TEST_RESULT(link_get_id1(link)==NO_ID);
}

void test1_link_get_id2(){
  Link *link = link_create(1);
  link_set_id2(link,3);
  PRINT_TEST_RESULT(link_get_id2(link)==3);
}

void test2_link_get_id2(){
  Link *link = NULL;
  PRINT_TEST_RESULT(link_get_id2(link)==NO_ID);
}

void test1_link_get_name(){
  Link *link = link_create(1);
  link_set_name(link,"Libro");
  PRINT_TEST_RESULT(strcmp("Libro",link_get_name(link))==0);
}

void test2_link_get_name(){
  Link *link = NULL;
  PRINT_TEST_RESULT(link_get_name(link)==NULL);
}
