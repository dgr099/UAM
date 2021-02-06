/** 
 * @brief It defines a space
 * 
 * @file space.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
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
* @brief set the object
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @param id the id that the object will have
* @return ERROR if there is an error, otherwise return OK
*/
STATUS space_set_object(Space *space, Id object);
/**
* @brief get the object of this space
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param space one space that has been created before
* @return sapace->object the object int the space we enter
*/
Id space_get_object(Space *space);
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
#endif
