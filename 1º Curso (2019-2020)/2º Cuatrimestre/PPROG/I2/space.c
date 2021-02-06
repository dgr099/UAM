/** 
 * @brief Store, set all the information about a space that is created, also  
 * can realed the space
 * 
 * @file game.c
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "game.h"
#include "set.h"
/**
* @brief  The space structure
*
* It stores information of the different spaces managed by the sytem
*/
struct _Space
{
  Id id;                    /*!< Id of the space */
  char name[WORD_SIZE + 1]; /*!< Name of the space */
  Id north;                 /*!< Id of the north space */
  Id south;                 /*!< Id of the south space */
  Id east;                  /*!< Id of the east space */
  Id west;                  /*!< Id of the weast space */
  char gdesc[NUM_STRINGS][NUM_CHARACTS];  /*the string with thediferents drawings*/         
  Set *objects;              /*!< Id of the object in that space */
};

Space *space_create(Id id)
{
  /*
 first of all it's checked if there is an error,then memory is reserved for 
 newspace, finally values are assigned to the elements of the structure
*/
  int i,j;
  Space *newSpace = NULL;

  if (id == NO_ID) /*it's checked if there is an error*/
    return NULL;

  if(!(newSpace = (Space *)malloc(sizeof(Space)))){ /*reserve memory for newspace*/
    return NULL;
  } 
  newSpace->objects=set_create();
  if (newSpace == NULL)
  { /*it's checked if there is an error*/
    return NULL;
  }
  newSpace->id = id;

  newSpace->name[0] = '\0';

  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
for (i=0;i<NUM_STRINGS; i++){
	for(j=0;j<NUM_CHARACTS; j++){
    newSpace->gdesc[i][j]='0';
  }
}

  return newSpace;
}

STATUS space_destroy(Space *space)
{
  /* 
 First it's checked if is something wrong with the space that we want to free,  if there is no error the space is released
*/
  if (!space)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  set_destroy(space->objects);
  free(space); /*release the space*/

  return OK;
}

STATUS space_set_name(Space *space, char *name)
{
  /* 
 First it's checked if is something wrong with the space, the name or with the process of copy,  if there is no error the name is set
*/
  if (!space || !name)
  { /*it's checked if there is an error*/
    return ERROR;
  }

  if (!strcpy(space->name, name))
  { /*it's checked if there is an error*/
    return ERROR;
  }

  return OK;
}

STATUS space_set_north(Space *space, Id id)
{
  /* 
 First it's checked if is something wrong with the space or with the id, if there is no error the north is set
*/
  if (!space || id == NO_ID)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  space->north = id;
  return OK;
}

STATUS space_set_south(Space *space, Id id)
{
  /* 
 First it's checked if is something wrong with the space or with the id, if there is no error the south is set
*/
  if (!space || id == NO_ID)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  space->south = id;
  return OK;
}

STATUS space_set_east(Space *space, Id id)
{
  /* 
 First it's checked if is something wrong with the space or with the id, if there is no error the east is set
*/
  if (!space || id == NO_ID)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  space->east = id;
  return OK;
}

STATUS space_set_west(Space *space, Id id)
{
  /* 
 First it's checked if is something wrong with the space or with the id, if there is no error the weast is set
*/
  if (!space || id == NO_ID)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  space->west = id;
  return OK;
}

STATUS space_add_object(Space *space, Id object)
{
  /* 
 First it's checked if is something wrong with the space, if there is no error then the object is set
*/
  if (!space)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  if(set_add(space->objects, object)==ERROR){
    return ERROR;
  }
  return OK;
}

STATUS space_dell_object(Space *space, Id object){
  /* 
 First it's checked if is something wrong with the space, if there is no error then the object is set
  */
  if (!space)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  if(set_dell(space->objects, object)==ERROR){
    return ERROR;
  }
  return OK;
}
const char *space_get_name(Space *space)
{
  /* 
 First it's checked if is something wrong with the space, if there is no error then the name of the space is returned
*/
  if (!space)
  { /*it's checked if there is an error*/
    return NULL;
  }
  return space->name;
}

int space_get_num(Space *space){
  if(!space){
    return -1;
  }
  return set_get_num(space->objects);
}

Id space_get_id(Space *space)
{
  /* 
 First it's checked if is something wrong with the space, if there is no error then the id of the space is returned
*/
  if (!space)
  { /*it's checked if there is an error*/
    return NO_ID;
  }
  return space->id;
}

Id space_get_north(Space *space)
{
  /* 
 First it's checked if is something wrong with the space, if there is no error then the north of the space is returned
*/
  if (!space)
  { /*it's checked if there is an error*/
    return NO_ID;
  }
  return space->north;
}

Id space_get_south(Space *space)
{
  /* 
 First it's checked if is something wrong with the space, if there is no error then the south of the space is returned
*/
  if (!space)
  { /*it's checked if there is an error*/
    return NO_ID;
  }
  return space->south;
}

Id space_get_east(Space *space)
{
  /* 
 First it's checked if is something wrong with the space, if there is no error then the east of the space is returned
*/
  if (!space)
  { /*it's checked if there is an error*/
    return NO_ID;
  }
  return space->east;
}

Id space_get_west(Space *space)
{
  /* 
 First it's checked if is something wrong with the space, if there is no error then the west of the space is returned
*/
  if (!space)
  { /*it's checked if there is an error*/
    return NO_ID;
  }
  return space->west;
}

Set* space_get_objects(Space *space)
{
  /* 
 First it's checked if is something wrong with the space, if there is no error then the object in this space is returned
*/
  if (!space)
  { /*it's checked if there is an error*/
    return FALSE;
  }
  return space->objects;
}

BOOL space_is_object(Space *space, Id object){
  if(!space){
    return FALSE;
  }
  if(set_find_index(space->objects, object)!=-1){
    return TRUE;
  }
  return FALSE;
}
STATUS space_print(Space *space)
{
int i,j;
  /* 
 First it's checked if is something wrong with the space, if there is no error then the space is printed on the screen
*/
  Id idaux = NO_ID;
  if (!space)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name); /*print on screen the id and name of the space*/
  idaux = space_get_north(space);
  if (NO_ID != idaux)
  {
    /*print on screen if there is north or not in case there isnt an error*/
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (NO_ID != idaux)
  {
    /*print on screen if there is south or not in case there isnt an error*/
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (NO_ID != idaux)
  {
    /*print on screen if there is east or not in case there isnt an error*/
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (NO_ID != idaux)
  {
    /*print on screen if there is weast or not in case there isnt an error*/
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No west link.\n");
  }
  if (set_get_num(space->objects)>0)
  {
    /*print on screen if there is object in this space or not in case there isnt an error*/
    fprintf(stdout, "---> Objects in the space.\n");
  }
  else
  {
    fprintf(stdout, "---> No objects in the space.\n");
  }
for (i=0; i<NUM_STRINGS; i++){
   fprintf(stdout,"\"");
    for(j=0; j<NUM_CHARACTS; j++){
      fprintf(stdout,"%c",space->gdesc[i][j]);
    }
   fprintf(stdout,"\"\n");
  }
  return OK;
}
char space_get_gdesc_at(Space *space, int position1, int position2){
	if(space==NULL)
          return FALSE;
        else
          return space->gdesc[position1][position2];
}

STATUS space_set_gdesc_at(Space *space, int position1, int position2, char element){
	if(space==NULL)
 	 return ERROR;
        else
	  space->gdesc[position1][position2]=element;
	 return OK;
}
