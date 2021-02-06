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
#define MAX_TESTS 45

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
    printf("Running all test for module command:\n");
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
  if (all || test == 17) test1_command_set_status();
  if (all || test == 18) test2_command_set_status();
  if (all || test == 19) test3_command_set_status();
  if (all || test == 20) test1_command_set_argument();
  if (all || test == 21) test2_command_set_argument();
  if (all || test == 22) test3_command_set_argument();
  if (all || test == 23) test1_command_destroy();
  if (all || test == 24) test2_command_destroy();
  if (all || test == 26) test1_command_get_user_input();
  if (all || test == 27) test2_command_get_user_input();
  if (all || test == 28) test3_command_get_user_input();
  if (all || test == 29) test4_command_get_user_input();
  if (all || test == 30) test5_command_get_user_input();
  if (all || test == 31) test6_command_get_user_input();
  if (all || test == 32) test7_command_get_user_input();
  if (all || test == 33) test8_command_get_user_input();
  if (all || test == 34) test9_command_get_user_input();
  if (all || test == 35) test10_command_get_user_input();
  if (all || test == 36) test11_command_get_user_input();
  if (all || test == 37) test12_command_get_user_input();
  if (all || test == 38) test13_command_get_user_input();
  if (all || test == 39) test14_command_get_user_input();
  if (all || test == 40) test15_command_get_user_input();
  if (all || test == 41) test16_command_get_user_input();
  if (all || test == 42) test17_command_get_user_input();
  if (all || test == 43) test18_command_get_user_input();
  if (all || test == 44) test19_command_get_user_input();
  if (all || test == 45) test20_command_get_user_input();
  if (all || test == 46) test21_command_get_user_input();
  if (all || test == 47) test22_command_get_user_input();
  if (all || test == 48) test23_command_get_user_input();
  



  PRINT_PASSED_PERCENTAGE;
  return 0;
}

void test1_command_init(){
  int result = command_init()!=NULL;
  PRINT_TEST_RESULT(result);
}

void test2_command_init(){
  Command *command;
  char *argumen;
  command = command_init();
  argumen=command_get_argument(command);
  PRINT_TEST_RESULT(strcmp(argumen, "\0")==0);
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