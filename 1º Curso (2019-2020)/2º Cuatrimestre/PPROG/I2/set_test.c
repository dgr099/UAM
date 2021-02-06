/** 
 * @brief test to see if set works correctly
 * 
 * @file set_test.c
 * @author David Teófilo Garitagoitia Romero
 * @version 1.0 
 * @date 7-3-2020
 * @copyright GNU Public License
 */
#include <stdio.h>
#include "set.h"
int main(){
  Set* set, *set_NULL=NULL;
  set=set_create();
  if(!set){
    printf("ERROR creacion de test 1\n");
    return 1;
  }
  if(set_add(set, 9)==ERROR){
    printf("ERROR set_add 1\n");
    return 1;
  }
  if(set_add(set, 120)==ERROR){
    printf("ERROR set_add 2\n");
    return 1;
  }
  if(set_add(set_NULL, 9)==OK){
    printf("ERROR set_add 3\n");
    return 1;
  }
  set_print(stdout, set);
  if(set_dell(set, 9)==ERROR){
    printf("ERROR set_dell 1\n");
    return 1;    
  }
  set_print(stdout, set);
  if(set_add(set, 15)==ERROR){
    printf("ERROR set_add 4\n");
    return 1;
  }
  if(set_dell(set, 120)==ERROR){
    printf("ERROR set_dell 2\n");
    return 1;    
  }
  set_print(stdout, set);
  if(set_dell(set, 15)==ERROR){
    printf("ERROR set_dell 3\n");
    return 1;    
  }
  if(set_dell(set, 15)==OK){
    printf("ERROR set_dell 4\n");
    return 1;    
  }
  set_print(stdout, set); /*test vacio*/
  if(set_destroy(set)==ERROR){
    printf("ERROR set_destroy\n");
    return 1;    
  }
  printf("Test superado\n");
  return 0;
}