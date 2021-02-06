/**
* @brief It implements the set interface
*
* @file set.c
* @author David Teófilo Garitagoitia Romero
* @version 1.0
* @date 18-02-2020
* @copyright GNU Public License
*/
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "set.h"
/*! \def MAX_ID
    \brief maimum number of id of the set
   
    Details.
*/
#define MAX_ID 10
/**
* @brief The set structure
*
* It stores information of an object
*/
struct _Set
{
  Id tabla[MAX_ID]; /*!< array of identifiers */
  int num;   /*!< number of identifiers */
};

Set *set_create()
{
  int i;
  Set *set;
  set = malloc(sizeof(Set));
   if (!set)
  {
    return NULL;
  }
  set->num = 0;
  for(i=0; i!=set->num; i++){
    set->tabla[i]=NO_ID;
  }
  return set;
}

STATUS set_destroy(Set *set)
{
  if (!set)
  {
    return ERROR;
  }
  free(set);
  return OK;
}

STATUS set_add(Set *set, Id id)
{
  if(!set || set->num>=MAX_ID){
    return ERROR;
  }
  set->tabla[set->num]=id;
  set->num++;
  return OK;
}

STATUS set_dell(Set *set, Id id){
  int i=set_find_index(set, id);
  if(i==-1){
    return ERROR;
  }
  if(!set || set->num<=0){
    return ERROR;
  }
  if(set_find_index(set, id)==-1){
    return ERROR;
  }
  set->tabla[set_find_index(set, id)]=NO_ID;
  for( ; i!=set_get_num(set)-1; i++){
    set->tabla[i]=set->tabla[i+1];
  }
  set->num--;
  return OK;
}

int set_get_num(Set *set){
  if(!set){
    return -1;
  }
  return set->num;
}

int set_find_index(Set *set, Id id){
  int i=0;
  if(!set){
    return -1;
  }
  for(i=0; i!=set->num; i++){
    if(set->tabla[i]==id)
      return i;
  }
  return -1;
}

Id  set_get_id_at_position(Set* set, int position){
  if(!set || position>=set_get_num(set)){
    return -1;
  }
  return set->tabla[position];
}

void set_print(FILE *f, Set *set)
{
  int i;
  fprintf(f, "   %d \n", set->num);
  for (i = 0; i < set->num; i++)
  {
    printf(" %ld ", set->tabla[i]);
  }
  printf("\n");
 return;
}