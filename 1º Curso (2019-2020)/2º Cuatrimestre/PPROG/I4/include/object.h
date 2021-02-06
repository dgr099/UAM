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
#include "../include/types.h"
/*! \var typedef struct _Object Object
    \brief A type definition for a object.
    
    Details.
*/
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
* @author: José Manuel García Giráldez
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
* @author: David Teófilo Garitagoitia Romero
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
* @author: David Teófilo Garitagoitia Romero
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
* @author: José Manuel García Giráldez
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
/**
* @brief set the description of an object
*
* object_set_description
*
* @date 17-02-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @param description the description we want to insert in the object
* @return ERROR if there is an error, otherwise return OK
*/
STATUS object_set_description(Object *object, char *description);
/**
* @brief returns the description of an object
*
* object_get_description
*
* @date 17-02-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @return the description of an object
*/
const char *object_get_description(Object *object);
/**
* @brief set the mavable of an object
*
* object_set_movable
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @param bool true or false
* @return Ok if there is no error, false otherwise
*/
STATUS object_set_movable(Object *object, BOOL bool);
/**
* @brief get the mavable of an object
*
* object_get_movable
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @return return the movable of an object
*/
BOOL object_get_movable(Object *object);
/**
* @brief set the hidden of an object
*
* object_set_hidden
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @param bool true or false
* @return Ok if there is no error, false otherwise
*/
STATUS object_set_hidden(Object *object, BOOL bool);
/**
* @brief get the mavable of an object
*
* object_get_movable
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @return the hidden of an object
*/
BOOL object_get_hidden(Object *object);
/**
* @brief set the id of the link to open with an object
*
* object_set_opem
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @param id the id of the link that can open
* @return Ok if there is no error, false otherwise
*/
STATUS object_set_open(Object *object, Id id);
/**
* @brief get the id of the link that this object can open
*
* object_get_open
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @return the id of the link
*/
Id object_get_open(Object *object);
/**
* @brief set the hability to iluminate of an object
*
* object_set_iluminate
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @param bool true or false
* @return Ok if there is no error, false otherwise
*/
STATUS object_set_illuminate(Object *object, BOOL bool);
/**
* @brief get the ilumination capacity of an object
*
* object_get_ilumination
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @return true if the object can iluminate, false otherwise
*/
BOOL object_get_illuminate(Object *object);
/**
* @brief set if the object is turned or not
*
* object_turned
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @param bool true or false
* @return Ok if there is no error, false otherwise
*/
STATUS object_turned(Object *object, BOOL bool);
/**
* @brief used to know if the object is turned or not
*
* object_get_turned
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @return True if the object is turned on
*/
BOOL object_get_turned(Object *object);
/**
* @brief set the dependency of an object
*
* object_set_dependency
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @param dependency the id of the dependency
* @return Ok if there is no error, false otherwise
*/
STATUS object_set_dependency(Object *object, Id dependency);
/**
* @brief get the dependency of an object
*
* object_get_dependency
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @return Ok the dependency of the object
*/
Id object_get_dependency(Object *object);
/**
* @brief set the incompatible of an object
*
* object_set_incompatible
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @param id the id of the incompatible object
* @return Ok if there is no error, false otherwise
*/
STATUS object_set_incompatible(Object *object, Id id);
/**
* @brief get the incompatible id of an object
*
* object_get_incompatible
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @return the id of the incompatible id
*/
Id object_get_incompatible(Object *object);

#endif
