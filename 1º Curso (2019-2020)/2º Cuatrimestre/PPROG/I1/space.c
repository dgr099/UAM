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
  Id object;                /*!< Id of the object in that space */
};

Space *space_create(Id id)
{
  /*
 first of all it's checked if there is an error,then memory is reserved for 
 newspace, finally values are assigned to the elements of the structure
*/
  Space *newSpace = NULL;

  if (id == NO_ID) /*it's checked if there is an error*/
    return NULL;

  newSpace = (Space *)malloc(sizeof(Space)); /*reserve memory for newspace*/

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

  newSpace->object = NO_ID;

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

STATUS space_set_object(Space *space, Id object)
{
  /* 
 First it's checked if is something wrong with the space, if there is no error then the object is set
*/
  if (!space)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  space->object = object;
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

Id space_get_object(Space *space)
{
  /* 
 First it's checked if is something wrong with the space, if there is no error then the object in this space is returned
*/
  if (!space)
  { /*it's checked if there is an error*/
    return FALSE;
  }
  return space->object;
}

STATUS space_print(Space *space)
{
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
  if (space_get_object(space))
  {
    /*print on screen if there is object in this space or not in case there isnt an error*/
    fprintf(stdout, "---> Object in the space.\n");
  }
  else
  {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}
