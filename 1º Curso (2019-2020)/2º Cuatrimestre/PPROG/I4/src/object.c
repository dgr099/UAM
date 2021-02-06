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
#include "../include/types.h"
#include "../include/object.h"
/**
* @brief The object structure
*
* It stores information of an object
*/
struct _Object
{
  Id id;                /*!< object identifier */
  char name[WORD_SIZE]; /*!< object name */
  char description[WORD_SIZE];   /*!< description of the object */
  BOOL movable; /*!< the ability to move the object */
  BOOL hidden;  /*!< if the object is hidden  */
  Id open; /*!< the id of the link that the object can open */
  BOOL illuminate; /*!< the ability to illuminate an space */
  BOOL turnedon; /*!< if the object is turned (it iluminates) or not */
  Id dependency; /*!< saves the id of the object necessary to be able to get this object */
  Id incompatible; /*!< stores the id of an object that cannot be joined */
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
  newObject->description[0] = '\0';
  newObject->movable = TRUE;
  newObject->hidden = TRUE;
  newObject->illuminate = FALSE;
  newObject->open = NO_ID;
  newObject->turnedon = FALSE;
  newObject->dependency = NO_ID;
  newObject->incompatible = NO_ID;
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

STATUS object_set_dependency(Object *object, Id dependecy){
  if(!object){
    return ERROR;
  }
  object->dependency=dependecy;
  return OK;
}

Id object_get_dependency(Object *object){
  if(!object){
    return NO_ID;
  }
  return object->dependency;
}

STATUS object_set_incompatible(Object *object, Id id){
  if(!object){
    return ERROR;
  }
  object->incompatible=id;
  return OK;
}

Id object_get_incompatible(Object *object){
  if(!object){
    return NO_ID;
  }
  return object->incompatible;
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

STATUS object_turned(Object *object, BOOL bool){
  if(!object){
    return ERROR;
  }
  object->turnedon=bool;
  return OK;
}

BOOL object_get_turned(Object *object){
  if(!object){
    return FALSE;
  }
  return object->turnedon;
}

STATUS object_set_description(Object *object, char *description){
  if(!object || !description){
    return ERROR;
  }
  strcpy(object->description, description);
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

STATUS object_set_movable(Object *object, BOOL bool){
  if(!object){
    return ERROR;
  }
  object->movable=bool;
  return OK;
}

BOOL object_get_movable(Object *object){
  if(!object){
    return FALSE;
  }
  return object->movable;
}

STATUS object_set_illuminate(Object *object, BOOL bool){
  if(!object){
    return ERROR;
  }
  object->illuminate=bool;
  return OK;
}

BOOL object_get_illuminate(Object *object){
  if(!object){
    return FALSE;
  }
  return object->illuminate;
}

STATUS object_set_hidden(Object *object, BOOL bool){
  if(!object){
    return ERROR;
  }
  object->hidden=bool;
  return OK;
}

BOOL object_get_hidden(Object *object){
  if(!object){
    return ERROR;
  }
  return object->hidden;
}

STATUS object_set_open(Object *object, Id id){
  if(!object){
    return ERROR;
  }
  object->open=id;
  return OK;
}

Id object_get_open(Object *object){
  if(!object){
    return NO_ID;
  }
  return object->open;
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

const char *object_get_description(Object *object){
  if(!object){
    return NULL;
  }
  return object->description;
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
