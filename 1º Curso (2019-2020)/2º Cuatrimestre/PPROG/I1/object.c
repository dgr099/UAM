/** 
 * @brief Store and set all the information about an object that is created, also  
 * can release the object
 * 
 * @file object.c
 * @author David Teófilo Garitagoitia Romero y José Manuel García Giráldez
 * @version 1.0 
 * @date 07-02-2019 
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "object.h"
/**
* @brief The object structure
*
* It stores information of an object
*/
struct _Object
{
  Id id;                /*!< object identifier */
  char name[WORD_SIZE]; /*!< object name */
};

Object *object_create(Id id)
{
  /*
 first of all it's checked if there is an error,then memory is reserved for 
 newobject, finally the elements of the structure are initialited
*/
  Object *newObject = NULL;
  if (id == NO_ID) /*it's checked if there is an error*/
    return NULL;
  newObject = (Object *)malloc(sizeof(Object));
  if (newObject == NULL)
  { /*it's checked if there is an error*/
    return NULL;
  }
  newObject->id = id;
  newObject->name[0] = '\0';
  return newObject;
}

STATUS object_destroy(Object *object)
{
  /* 
 First it's checked if is something wrong with the object that we want to free,  if there is no error the object is released
*/
  if (!object)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  free(object);
  return OK;
}

STATUS object_set_name(Object *object, char *name)
{
  /* 
 First it's checked if is something wrong with the object, the name or with the process of copy,  if there is no error the name is set
*/
  if (!object || !name)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  if (!strcpy(object->name, name))
  { /*it's checked if there is an error*/
    return ERROR;
  }
  return OK;
}

STATUS object_set_id(Object *object, int id)
{
  /* First it's checked if is something wrong with the object, if there isnt the id is set */
  if (!object)
  {
    return ERROR;
  }
  object->id = id;
  return OK;
}

const char *object_get_name(Object *object)
{
  /* 
First it's checked if is something wrong with the object, if there is no error then the name of the object is returned
*/
  if (!object)
  { /*it's checked if there is an error*/
    return NULL;
  }
  return object->name;
}

Id object_get_id(Object *object)
{
  /* 
First it's checked if is something wrong with the object, if there is no error then the id of the object is returned
*/
  if (!object)
  { /*it's checked if there is an error*/
    return NO_ID;
  }
  return object->id;
}

STATUS object_print(Object *object)
{
  /* 
First it's checked if is something wrong with the object, if there is no error then the information of the object is printed on the screen
*/
  if (!object)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  printf("--> Object (Id: %ld; Name: %s)\n", object->id, object->name); /*print on screen the id, the location and the name of the object*/
  return OK;
}
