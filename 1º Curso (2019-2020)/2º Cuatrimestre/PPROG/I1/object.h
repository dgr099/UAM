/** 
 * @brief It defines the object interface
 * for each command
 * 
 * @file object.h
 * @author David Teófilo Garitagoitia Romero y José Manuel García Giráldez
 * @version 1.0 
 * @date 9-02-2020 
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H
#include "types.h"

typedef struct _Object Object;
/**
*@brief Create the object
*
* object_create Create a object with a specific Id
*
* @date 07-02-2019
* @author: José Manuel García Giráldez
*
* @param id the id of the new object
* @return the new object that has been created
*/
Object *object_create(Id id);
/**
* @brief free an object
*
* object_destroy free a especific object 
*
* @date 07-02-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @return ERROR if there is an error, otherwise return OK
*/
STATUS object_destroy(Object *object);
/**
* @brief name the object 
*
* object_set_name
*
* @date 07-02-2019
* @author: José Manuel García Giráldez
*
* @param object one object that has been created before
* @param name the name that the object will have
* @return ERROR if there is an error, otherwise return OK
*/
STATUS object_set_name(Object *object, char *name);
/**
* @brief set the id
*
* object_set_id
*
* @date 07-02-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @param id the id that the object will have
* @return ERROR if there is an error, otherwise return OK
*/
STATUS object_set_id(Object *object, int id);
/**
* @brief get the name of the object
*
* object_get_name
*
* @date 07-02-2019
* @author: José Manuel García Giráldez
*
* @param object one object that has been created before
* @return object->name the name of the object we enter
*/
const char *object_get_name(Object *object);
/**
* @brief get the id of the object
*
* object_get_id
*
* @date 07-02-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @return object->id the id of the object we enter
*/
Id object_get_id(Object *object);
/**
* @brief print the information of the object on the screen
*
* object_print
*
* @date 07-02-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @return ERROR if there is an error, otherwise return OK
*/
STATUS object_print(Object *object);
#endif
