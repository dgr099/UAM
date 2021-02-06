/** 
 * @brief It defines a space
 * 
 * @file space.h
 * @author Profesores PPROG, David Teófilo Garitagoitia Romero, José Manuel García Giráldez
 * @version 1.0 
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

/*#include "../include/game.h"*/
#include "../include/types.h"
#include "../include/set.h"
/*! \var typedef struct _Space Space
    \brief A type definition for a space.
    
    Details.
*/
typedef struct _Space Space;
/*! \def MAX_SPACES
    \brief A macro that stores the maximum number of spaces
   
    Details.
*/
#define MAX_SPACES 100
/*! \def FIRST_SPACE
    \brief A macro that stores the id of the first id
   
    Details.
*/
#define FIRST_SPACE 1
/*! \def NUM_STRINGS
    \brief the number of strings of a gdesc
   
    Details.
*/
#define NUM_STRINGS 3
/*! \def NUM_CHARACTS
    \brief A macro that stores the number of chars per string of a gdesc
   
    Details.
*/
#define NUM_CHARACTS 7

/**
*@brief Create the space
*
* space_create Create a space with a specific Id
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param id the id of the new space
* @return the new space that has been created
*/
Space *space_create(Id id);
/**
* @brief free a space
*
* space_destroy free a especific space 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @return ERROR if there is an error, otherwise return OK
*/
STATUS space_destroy(Space *space);
/**
* @brief get the id of the space
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @return sapace->id the id of the space we enter
*/
Id space_get_id(Space *space);
/**
* @brief name the space 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @param name the name that space will have
* @return ERROR if there is an error, otherwise return OK
*/
STATUS space_set_name(Space *space, char *name);
/**
* @brief get the name of the space
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @return sapace->name the name of the space we enter
*/
const char *space_get_name(Space *space);
/**
* @brief set the north 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @param id the id that north will have
* @return ERROR if there is an error, otherwise return OK
*/
STATUS space_set_north(Space *space, Id id);
/**
* @brief get the north of the space
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @return sapace->north the north of the space we enter
*/
Id space_get_north(Space *space);
/**
* @brief set the south
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @param id the id that south will have
* @return ERROR if there is an error, otherwise return OK
*/
STATUS space_set_south(Space *space, Id id);
/**
* @brief get the south of the space
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @return sapace->south the south of the space we enter
*/
Id space_get_south(Space *space);
/**
* @brief set the east
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @param id the id that east will have
* @return ERROR if there is an error, otherwise return OK
*/
STATUS space_set_east(Space *space, Id id);
/**
* @brief get the east of the space
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @return sapace->east the east of the space we enter
*/
Id space_get_east(Space *space);
/**
* @brief set the west
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @param id the id that west will have
* @return ERROR if there is an error, otherwise return OK
*/
STATUS space_set_west(Space *space, Id id);
/**
* @brief get the west of the space
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @return sapace->west the west of the space we enter
*/
Id space_get_west(Space *space);
/**
* @brief set the down
*
* @date 11-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space one space that has been created before
* @param id the id that down will have
* @return ERROR if there is an error, otherwise return OK
*/
STATUS space_set_down(Space *space, Id id);
/**
* @brief get the down of the space
*
* @date 11-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space one space that has been created before
* @return sapace->down the down of the space we enter
*/
Id space_get_down(Space *space);
/**
* @brief set the up
*
* @date 11-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space one space that has been created before
* @param id the id that up will have
* @return ERROR if there is an error, otherwise return OK
*/
STATUS space_set_up(Space *space, Id id);
/**
* @brief get the up of the space
*
* @date 11-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space one space that has been created before
* @return sapace->up the up of the space we enter
*/
Id space_get_up(Space *space);
/**
* @brief set the object
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @param object the id that the object will have
* @return ERROR if there is an error, otherwise return OK
*/
STATUS space_add_object(Space *space, Id object);
/**
* @brief get the object of this space
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @return sapace->object the object int the space we enter
*/
Set* space_get_objects(Space *space);
/**
* @brief printf the space on the screen
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @return ERROR if there is an error, otherwise return OK
*/
STATUS space_print(Space *space);
/**
* @brief get an especific element of the array of string 
*
* @date 13-01-2015
* @author: José Manuel García Giráldez
*
* @param space one space that has been created before
* @param position1 select the string we want
* @param position2 select the element of the string we want
* @return the element we search for
*/
char space_get_gdesc_at(Space *space, int position1, int position2);
/**
* @brief get an especific element of the array of string 
*
* @date 13-01-2015
* @author: José Manuel García Giráldez
*
* @param space one space that has been created before
* @param position1 select the string we want
* @param position2 select the element of the string we want
* @param element the element that we want in an especific position
* @return ERROR if there is an error, otherwise return OK
*/
STATUS space_set_gdesc_at(Space *space, int position1, int position2, char element);
/**
* @brief used to know if an object is in a space or not
*
* @date 20-02-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space one space that has been created before
* @param object the object that you want to know if is in the space or not
* @return ERROR if there is an error, otherwise return OK
*/
BOOL space_is_object(Space *space, Id object);
/**
* @brief used to dell an object in an space
*
* @date 20-02-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space one space that has been created before
* @param object the object that you want to remove
* @return ERROR if there is an error, otherwise return OK
*/
STATUS space_dell_object(Space *space, Id object);
/**
* @brief used to know the amount of obects in the space
*
* @date 2-03-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space one space that has been created before
* @return the amount of objects
*/
int space_get_num(Space *space);
/**
* @brief used to know the description of an space no matter if the space is lit or not
*
* @date 10-03-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space one space that has been created before
* @return the description
*/
const char* space_get_description1(Space *space);
/**
* @brief used to know the description of an space if the space is lit
*
* @date 10-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space one space that has been created before
* @return the most exact description
*/
const char* space_get_description2(Space *space);
/**
* @brief used to set the description which you can see no matter if the space is lit or not
*
* @date 10-03-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space one space that has been created before
* @param description the description
* @return Ok if there is no error, error otherwise
*/
STATUS space_set_description1(Space *space, char *description);
/**
* @brief used to set the description which you can see no matter if the space is lit
*
* @date 10-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space one space that has been created before
* @param description the description
* @return Ok if there is no error, error otherwise
*/
STATUS space_set_description2(Space *space, char *description);
/**
* @brief used to see if an space is iluminated or not
*
* @date 20-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space one space that has been created before
* @return True if its iluminate, false otherwise
*/
BOOL space_is_iluminated(Space *space);
/**
* @brief used to set the ilumination of an space
*
* @date 10-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space one space that has been created before
* @param bool true or false
* @return Ok if there is no error, error otherwise
*/
STATUS space_set_ilumination(Space *space, BOOL bool);

#endif
