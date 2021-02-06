/** 
 * @brief test to see if dice works correctly
 * 
 * @file command_test.c
* @author David Teófilo Garitagoitia Romero
 * @version 2.0 
 * @date 10-06-2020
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/test.h"
#include "../include/command.h"
#include "../include/command_test.h"
#include "../include/types.h"

/*! \def MAX_TESTS
    \brief maximum number of test
   
    Details.
*/
#define MAX_TESTS 63

/**
* @brief the main function of dice_test
** main
*
* @date 10-06-2020 
* @author David Teófilo Garitagoitia Romero
* @return
*/
int main(int argc, char **argv){

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Command:\n");
  } else {
      test = atoi(argv[1]);
      all = 0;
      printf("Running test %d:\t", test);
      if (test < 1 && test > MAX_TESTS) {
        printf("Error: unknown test %d\t", test);
	exit(EXIT_SUCCESS);
      }
  }

  if (all || test == 1) test1_command_init();
  if (all || test == 2) test2_command_init();
  if (all || test == 3) test3_command_init();
  if (all || test == 4) test4_command_init();
  if (all || test == 5) test1_command_set_principal_cmd();
  if (all || test == 6) test2_command_set_principal_cmd();
  if (all || test == 7) test3_command_set_principal_cmd();
  if (all || test == 8) test4_command_set_principal_cmd();
  if (all || test == 9) test5_command_set_principal_cmd();
  if (all || test == 10) test6_command_set_principal_cmd();
  if (all || test == 11) test7_command_set_principal_cmd();
  if (all || test == 12) test8_command_set_principal_cmd();
  if (all || test == 13) test9_command_set_principal_cmd();
  if (all || test == 14) test10_command_set_principal_cmd();
  if (all || test == 15) test11_command_set_principal_cmd();
  if (all || test == 16) test12_command_set_principal_cmd();
  if (all || test == 17) test13_command_set_principal_cmd();
  if (all || test == 18) test14_command_set_principal_cmd();
  if (all || test == 19) test15_command_set_principal_cmd();
  if (all || test == 20) test16_command_set_principal_cmd();
  if (all || test == 21) test17_command_set_principal_cmd();
  if (all || test == 22) test18_command_set_principal_cmd();
  if (all || test == 23) test1_command_set_status();
  if (all || test == 24) test2_command_set_status();
  if (all || test == 25) test3_command_set_status();
  if (all || test == 26) test1_command_set_argument();
  if (all || test == 27) test2_command_set_argument();
  if (all || test == 28) test3_command_set_argument();
  if (all || test == 29) test1_command_destroy();
  if (all || test == 30) test2_command_destroy();
  if (all || test == 30) test1_command_get_user_input();
  if (all || test == 31) test2_command_get_user_input();
  if (all || test == 32) test3_command_get_user_input();
  if (all || test == 33) test4_command_get_user_input();
  if (all || test == 34) test5_command_get_user_input();
  if (all || test == 35) test6_command_get_user_input();
  if (all || test == 36) test7_command_get_user_input();
  if (all || test == 37) test8_command_get_user_input();
  if (all || test == 38) test9_command_get_user_input();
  if (all || test == 39) test10_command_get_user_input();
  if (all || test == 40) test11_command_get_user_input();
  if (all || test == 41) test12_command_get_user_input();
  if (all || test == 42) test13_command_get_user_input();
  if (all || test == 43) test14_command_get_user_input();
  if (all || test == 44) test15_command_get_user_input();
  if (all || test == 45) test16_command_get_user_input();
  if (all || test == 46) test17_command_get_user_input();
  if (all || test == 47) test18_command_get_user_input();
  if (all || test == 48) test19_command_get_user_input();
  if (all || test == 49) test20_command_get_user_input();
  if (all || test == 50) test21_command_get_user_input();
  if (all || test == 51) test22_command_get_user_input();
  if (all || test == 52) test23_command_get_user_input();
  if (all || test == 53) test24_command_get_user_input();
  if (all || test == 54) test25_command_get_user_input();
  if (all || test == 55) test26_command_get_user_input();
  if (all || test == 56) test27_command_get_user_input();
  if (all || test == 57) test28_command_get_user_input();
  if (all || test == 58) test29_command_get_user_input();
  if (all || test == 59) test30_command_get_user_input();
  if (all || test == 60) test31_command_get_user_input();
  if (all || test == 61) test32_command_get_user_input();
  if (all || test == 62) test33_command_get_user_input();



  PRINT_PASSED_PERCENTAGE;
  return 0;
}

void test1_command_init(){
  int result = command_init()!=NULL;
  PRINT_TEST_RESULT(result);
}

void test2_command_init(){
  Command *command;
  char *argument;
  command = command_init();
  argument=command_get_argument(command);
  PRINT_TEST_RESULT(strcmp(argument, "/0")==0);
}

void test3_command_init(){
  Command *command;
  command=command_init();
  PRINT_TEST_RESULT(strcmp(command_get_status(command), "ERROR")==0);
}

void test4_command_init(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_get_principalcmd(command)==NO_CMD);
}

void test1_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, UNKNOWN)==OK);
}

void test2_command_set_principal_cmd(){
  Command *command = NULL;
  PRINT_TEST_RESULT(command_set_principalcmd(command, UNKNOWN)==ERROR);
}

void test3_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, EXIT)==OK);
}

void test4_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, TAKE)==OK);
}

void test5_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, DROP)==OK);
}

void test6_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, ROLL)==OK);
}

void test7_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, MOVE)==OK);
}

void test8_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, INSPECT)==OK);
}

void test9_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, NEXT)==OK);
}

void test10_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, BACK)==OK);
}

void test11_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, RIGHT)==OK);
}

void test12_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, LEFT)==OK);
}


void test13_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, TURNON)==OK);
}

void test14_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, TURNOFF)==OK);
}

void test15_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, LOAD)==OK);
}

void test16_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, SAVE)==OK);
}

void test17_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, TALK)==OK);
}

void test18_command_set_principal_cmd(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_principalcmd(command, ACCUSE)==OK);
}

void test1_command_set_status(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_status(command, "OK")==OK);
}

void test2_command_set_status(){
  Command *command=NULL;
  PRINT_TEST_RESULT(command_set_status(command, "OK")==ERROR);
}

void test3_command_set_status(){
  Command *command;
  command = command_init();
  PRINT_TEST_RESULT(command_set_status(command, NULL)==ERROR);
}

void test1_command_set_argument(){
  Command *command;
  command=command_init();
  PRINT_TEST_RESULT(command_set_argument(command, "argument")==OK);
}

void test2_command_set_argument(){
  Command *command=NULL;
  PRINT_TEST_RESULT(command_set_argument(command, "argument")==ERROR);
}

void test3_command_set_argument(){
  Command *command;
  command=command_init();
  PRINT_TEST_RESULT(command_set_argument(command, NULL)==ERROR);
}

void test1_command_destroy(){
  Command *command;
  command=command_init();
  PRINT_TEST_RESULT(command_destroy(command)==OK); 
}

void test2_command_destroy(){
  Command *command=NULL;
  PRINT_TEST_RESULT(command_destroy(command)==ERROR); 
}
void test1_command_get_user_input(){
  Command *command;
  command=command_init();
  command_get_user_input(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==UNKNOWN);
}

void test2_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(strcmp(arguemnt, "\0")==0);
}

void test3_command_get_user_input(){
  Command *command;
  command=command_init();
  command_get_user_input(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==EXIT);
}

void test4_command_get_user_input(){
  Command *command;
  command=command_init();
  command_get_user_input(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==EXIT);
}

void test5_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(strcmp(arguemnt, "\0")==0);
}

void test6_command_get_user_input(){
  Command *command;
  command=command_init();
  command_get_user_input(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==TAKE);
}

void test7_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==TAKE && strcmp(arguemnt, "2")==0);
}

void test8_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==INSPECT && strcmp(arguemnt, "space")==0);
}

void test9_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==INSPECT && strcmp(arguemnt, "object")==0);
}

void test10_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==MOVE && strcmp(arguemnt, "n")==0);
}

void test11_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==MOVE && strcmp(arguemnt, "south")==0);
}

void test12_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==NEXT && strcmp(arguemnt, "\0")==0);
}

void test13_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==NEXT && strcmp(arguemnt, "\0")==0);
}

void test14_command_get_user_input(){
  Command *command;
  command=command_init();
  command_get_user_input(command);;
  PRINT_TEST_RESULT(command_get_principalcmd(command)==BACK);
}

void test15_command_get_user_input(){
  Command *command;
  command=command_init();
  command_get_user_input(command);;
  PRINT_TEST_RESULT(command_get_principalcmd(command)==BACK);
}

void test16_command_get_user_input(){
  Command *command;
  command=command_init();
  command_get_user_input(command);;
  PRINT_TEST_RESULT(command_get_principalcmd(command)==RIGHT);
}

void test17_command_get_user_input(){
  Command *command;
  command=command_init();
  command_get_user_input(command);;
  PRINT_TEST_RESULT(command_get_principalcmd(command)==RIGHT);
}

void test18_command_get_user_input(){
  Command *command;
  command=command_init();
  command_get_user_input(command);;
  PRINT_TEST_RESULT(command_get_principalcmd(command)==LEFT);
}

void test19_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==LEFT && strcmp(arguemnt, "\0")==0);
}

void test20_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==ROLL && strcmp(arguemnt, "\0")==0);
}

void test21_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==ROLL && strcmp(arguemnt, "\0")==0);
}

void test22_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==DROP && strcmp(arguemnt, "Pep")==0);
}

void test23_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==DROP && strcmp(arguemnt, "Pep")==0);
}

void test24_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==TURNON && strcmp(arguemnt, "O")==0);
}

void test25_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==TURNON && strcmp(arguemnt, "O")==0);
}

void test26_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==TURNOFF && strcmp(arguemnt, "O")==0);
}

void test27_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==TURNOFF && strcmp(arguemnt, "O")==0);
}

void test28_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==OPEN && strcmp(arguemnt, "LNK with O")==0);
}

void test29_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==OPEN && strcmp(arguemnt, "lnk")==0);
}

void test30_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==TALK && strcmp(arguemnt, "with Pep")==0);
}

void test31_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==TALK && strcmp(arguemnt, "with Jhon")==0);
}

void test32_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==ACCUSE && strcmp(arguemnt, "Pep")==0);
}

void test33_command_get_user_input(){
  Command *command;
  char *arguemnt;
  command=command_init();
  command_get_user_input(command);
  arguemnt=command_get_argument(command);
  PRINT_TEST_RESULT(command_get_principalcmd(command)==ACCUSE && strcmp(arguemnt, "P")==0);
}








