/** 
 * @brief test to see if dice works correctly
 * 
 * @file dice_test.c
 * @author David Teófilo Garitagoitia Romero
 * @version 1.0 
 * @date 7-3-2020
 * @copyright GNU Public License
 */
#include <stdio.h>
#include "dice.h"
/**
* @brief the main function of dice_test
** main
*
* @date 7-3-2020 
* @author David Teófilo Garitagoitia Romero
* @return
*/
int main(){
  Dice *dado;
  int tirada[3], i;
  if(!(dado=dice_create(4, 6, 6))){
  printf("Error creación dado 1\n");
    return 1;
  }
  if((tirada[0]=dice_roll(dado))<6 || tirada[0]>6){
    printf("Error dado 1 roll 1\n");
    return 1;
  }
  if((tirada[1]=dice_roll(dado))<6 || tirada[0]>6){
    printf("Error dado 1 roll 2\n");
    return 1;
  }
  if((tirada[2]=dice_roll(dado))<6 || tirada[0]>6){
    printf("Error dado 1 roll 3\n");
    return 1;
  }
  for(i=0; i!=3; i++){
    printf("%d\n", tirada[i]);
  }
  printf("Test 1 del dado superado\n");
  dice_print(dado);
  dice_destroy(dado);

  if(!(dado=dice_create(4, 6, 0))){
    printf("Error creación dado 2\n");
    return 1;
  }
  if((tirada[0]=dice_roll(dado))<0 || tirada[0]>6){
    printf("Error dado 2 roll 1\n");
    return 1;
  }
  if((tirada[1]=dice_roll(dado))<0 || tirada[0]>6){
    printf("Error dado 2 roll 2\n");
    return 1;
  }
  if((tirada[2]=dice_roll(dado))<0 || tirada[0]>6){
    printf("Error dado 2 roll 3\n");
    return 1;
  }
  for(i=0; i!=3; i++){
    printf("%d\n", tirada[i]);
  }
  dice_print(dado);
  dice_destroy(dado);
  printf("Test 2 del dado superado\n");
  if(!(dado=dice_create(4, 6, 3))){
    printf("Error creación dado 3\n");
    return 1;
  }
  if((tirada[0]=dice_roll(dado))<3 || tirada[0]>6){
    printf("Error dado 3 roll 1\n");
    return 1;
  }
  if((tirada[1]=dice_roll(dado))<3 || tirada[0]>6){
    printf("Error dado 3 roll 2\n");
    return 1;
  }
  if((tirada[2]=dice_roll(dado))<3 || tirada[0]>6){
    printf("Error dado 3 roll 3\n");
    return 1;
  }
  for(i=0; i!=3; i++){
    printf("%d\n", tirada[i]);
  }
  dice_print(dado);
  dice_destroy(dado);
  printf("Test 3 del dado superado\n");
  if((dado=dice_create(4, 0, 3))){
    printf("Error creación dado 4 (deberia ser NULL al ser el min>max)\n");
    return 1;
  }
  printf("Test 4 del dado superado\n");
  printf("Test superado\n");
  return 0;
}