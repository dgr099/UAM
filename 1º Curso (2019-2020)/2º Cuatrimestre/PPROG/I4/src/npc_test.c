/** 
 * @brief test to see if set works correctly
 * 
 * @file npc_test.c
 * @author David Teófilo Garitagoitia Romero
 * @version 1.0 
 * @date 7-5-2020
 * @copyright GNU Public License
 */
#include "../include/npc.h"
#include "../include/test.h"
#include "../include/npc_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*! \def MAX_TESTS
    \brief maximum number of test
   
    Details.
*/
#define MAX_TESTS 32
/**
* @brief the main function of npc_test
** main
*
* @date 20-02-2020 
* @author David Teófilo Garitagoitia Romero
* @return
*/
int main(int argc, char **argv){

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module for Npc:\n");
  } else {
      test = atoi(argv[1]);
      all = 0;
      printf("Running test %d:\t", test);
      if (test < 1 && test > MAX_TESTS) {
        printf("Error: unknown test %d\t", test);
	exit(EXIT_SUCCESS);
      }
  }

  if (all || test == 1) test1_npc_init();
  if (all || test == 2) test2_npc_init();
  if (all || test == 3) test3_npc_init();
  if (all || test == 4) test4_npc_init();
  if (all || test == 5) test1_npc_set_name();
  if (all || test == 6) test2_npc_set_name();
  if (all || test == 7) test3_npc_set_name();
  if (all || test == 8) test1_npc_add_dialogue();
  if (all || test == 9) test2_npc_add_dialogue();
  if (all || test == 10) test3_npc_add_dialogue();
  if (all || test == 11) test1_npc_set_culpability();
  if (all || test == 12) test2_npc_set_culpability();
  if (all || test == 13) test1_npc_get_random_dialogue();
  if (all || test == 14) test2_npc_get_random_dialogue();
  if (all || test == 15) test1_npc_get_name();
  if (all || test == 16) test2_npc_get_name();
  if (all || test == 17) test1_npc_get_guilty();
  if (all || test == 18) test2_npc_get_guilty();
  if (all || test == 19) test3_npc_get_guilty();
  if (all || test == 20) test1_npc_destroy();
  if (all || test == 21) test2_npc_destroy();
  if (all || test == 22) test1_npc_set_position();
  if (all || test == 23) test2_npc_set_position();
  if (all || test == 24) test1_npc_get_initial();
  if (all || test == 25) test2_npc_get_initial();
  if (all || test == 26) test1_npc_set_number_dialogues();
  if (all || test == 27) test2_npc_set_number_dialogues();
  if (all || test == 28) test1_npc_set_description();
  if (all || test == 29) test2_npc_set_description();
  if (all || test == 30) test3_npc_set_description();
  if (all || test == 31) test1_npc_get_description();
  PRINT_PASSED_PERCENTAGE;
  return 0;
  
}

void test1_npc_init(){
  Npc *npc;
  npc=npc_init(1); 
  PRINT_TEST_RESULT((npc)!=NULL);
}

void test2_npc_init(){
  Npc *npc;
  npc=npc_init(1); 
  PRINT_TEST_RESULT(npc_get_id(npc)==1);
}

void test3_npc_init(){
  Npc *npc;
  npc=npc_init(1); 
  PRINT_TEST_RESULT(npc_get_guilty(npc)==FALSE);
}

void test4_npc_init(){
  Npc *npc;
  npc=npc_init(1); 
  PRINT_TEST_RESULT(npc_get_position(npc)==NO_ID);
}

void test1_npc_set_name(){
  Npc *npc;
  npc=npc_init(5);
  PRINT_TEST_RESULT(npc_set_name(npc, "PEP")==OK);
}

void test2_npc_set_name(){
  Npc *npc;
  npc=npc_init(5);
  PRINT_TEST_RESULT(npc_set_name(npc, NULL)==ERROR);
}

void test3_npc_set_name(){
  Npc *npc=NULL;
  PRINT_TEST_RESULT(npc_set_name(npc, "ESTO_NO")==ERROR);
}

void test1_npc_add_dialogue(){
  Npc *npc;
  npc=npc_init(1);
  PRINT_TEST_RESULT(npc_add_dialogue(npc, "HOLA")==OK);
}

void test2_npc_add_dialogue(){
  Npc *npc;
  npc=npc_init(1);
  PRINT_TEST_RESULT(npc_add_dialogue(npc, NULL)==ERROR);
}

void test3_npc_add_dialogue(){
  Npc *npc=NULL;
  PRINT_TEST_RESULT(npc_add_dialogue(npc, "HOLA")==ERROR);
}

void test1_npc_set_culpability(){
  Npc *npc;
  npc=npc_init(5);
  PRINT_TEST_RESULT(npc_set_culpability(npc, TRUE)==OK);
}


void test2_npc_set_culpability(){
  Npc *npc=NULL;
  PRINT_TEST_RESULT(npc_set_culpability(npc, FALSE)==ERROR);
}

void test1_npc_get_random_dialogue(){
  Npc *npc;
  char *dialogue;
  npc=npc_init(1);
  npc_add_dialogue(npc, "HOLA");
  npc_add_dialogue(npc, "HOLA_2");
  dialogue=npc_get_random_dialogue(npc);
  PRINT_TEST_RESULT((strcmp(dialogue, "HOLA")==0 || strcmp(dialogue, "HOLA_2")==0));
}

void test2_npc_get_random_dialogue(){
  Npc *npc=NULL;
  PRINT_TEST_RESULT(npc_get_random_dialogue(npc)==NULL);
}

void test1_npc_get_name(){
  Npc *npc;
  char *nom;
  npc=npc_init(5);
  nom=npc_get_name(npc);
  npc_set_name(npc, "PEP");
  PRINT_TEST_RESULT(strcmp("PEP", nom)==0);
}

void test2_npc_get_name(){
  Npc *npc=NULL;
  PRINT_TEST_RESULT(npc_get_name(npc)==NULL);
}

void test1_npc_get_guilty(){
  Npc *npc;
  npc=npc_init(3);
  npc_set_culpability(npc, TRUE);
  PRINT_TEST_RESULT(npc_get_guilty(npc)==TRUE);
}

void test2_npc_get_guilty(){
  Npc *npc;
  npc=npc_init(3);
  npc_set_culpability(npc, TRUE);
  npc_set_culpability(npc, FALSE);
  PRINT_TEST_RESULT(npc_get_guilty(npc)==FALSE);
}

void test3_npc_get_guilty(){
  Npc *npc=NULL;
  PRINT_TEST_RESULT(npc_get_guilty(npc)==FALSE);
}

void test1_npc_destroy(){
  Npc *npc=NULL;
  npc=npc_init(5);
  PRINT_TEST_RESULT(npc_destroy(npc)==OK);
}

void test2_npc_destroy(){
  Npc *npc=NULL;
  PRINT_TEST_RESULT(npc_destroy(npc)==ERROR);
}

void test1_npc_set_position(){
  Npc *npc=NULL;
  PRINT_TEST_RESULT(npc_set_position(npc, 5)==ERROR);
}

void test2_npc_set_position(){
  Npc *npc=NULL;
  npc=npc_init(6);
  PRINT_TEST_RESULT(npc_set_position(npc, 5)==OK);
}

void test1_npc_get_initial(){
  Npc *npc=NULL;
  npc=npc_init(6);
  npc_set_name(npc, "PEP");
  PRINT_TEST_RESULT(npc_get_initial(npc)=='P');
}

void test2_npc_get_initial(){
  Npc *npc=NULL;
  PRINT_TEST_RESULT(npc_get_initial(npc)==' ');
}

void test1_npc_set_number_dialogues(){
  Npc *npc=NULL;
  PRINT_TEST_RESULT(npc_set_number_dialogues(npc, 5)==ERROR);
}

void test2_npc_set_number_dialogues(){
  Npc *npc=NULL;
  npc=npc_init(3);
  PRINT_TEST_RESULT(npc_set_number_dialogues(npc, 5)==OK);
}

void test1_npc_set_description(){
  Npc *npc;
  npc=npc_init(4);
  PRINT_TEST_RESULT(npc_set_description(npc, "NPC_PRUEBA")==OK);
}

void test2_npc_set_description(){
  Npc *npc;
  npc=npc_init(4);
  PRINT_TEST_RESULT(npc_set_description(npc, NULL)==ERROR);
}

void test3_npc_set_description(){
  Npc *npc=NULL;
  PRINT_TEST_RESULT(npc_set_description(npc, "ESTO_DEBERIA_GENERAR_UN_ERROR")==ERROR);
}

void test1_npc_get_description(){
  Npc *npc;
  char *descripion;
  npc=npc_init(4);
  npc_set_description(npc, "NPC_PRUEBA");
  descripion=npc_get_description(npc);
  PRINT_TEST_RESULT(strcmp(descripion, "NPC_PRUEBA")==0);
}

