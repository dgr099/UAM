/** 
 * @brief It defines the set interface
 * for each command
 * 
 * @file set.h
 * @author David Teófilo Garitagoitia Romero
 * @version 1.0 
 * @date 20-02-2020 
 * @copyright GNU Public License
 */
#ifndef SET_H
#define SET_H
#include "../include/types.h"
/*! \var typedef struct _Set Set
    \brief A type definition for a set.
    
    Details.
*/
typedef struct _Set Set;
/**
*@brief Create the set
*
* set_create Create a new set
*
* @date 20-02-2020
* @author David Teófilo Garitagoitia Romero
*
* @return the new set that has been created
*/
Set *set_create();
/**
*@brief Destroy the set
*
* set_destroy a set
*
* @date 20-02-2020
* @author David Teófilo Garitagoitia Romero
*
* @param set the addres of the set which you want to print
* @return Ok if there was no problem,
*/
STATUS set_destroy(Set *set);
/**
*@brief Add element to the set
*
* set_add add an element to the set
*
* @date 20-02-2020
* @author David Teófilo Garitagoitia Romero
*
* @param set the addres os the set in which you want to add an element
* @param id the id of the element you want to add
* @return Ok if there was no problem,
*/
STATUS set_add(Set *set, Id id);
/**
*@brief print the elements of the set
*
* set_print
*
* @date 20-02-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param set the set you want to print
* @param f in which you want to print and set which have the elements
* @return
*/
void set_print(FILE *f, Set *set);
/**
*@brief return the namber of id allocated in a set
*
* set_get_num
*
* @date 20-02-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param set the set that you want to know their number of ids
* @return
*/
int set_get_num(Set *set);
/**
*@brief return the index of and id
*
* set_find_index
*
* @date 26-02-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param set the set which contains the id
* @param id the id that you want to know their position
* @return
*/
int set_find_index(Set *set, Id id);
/**
*@brief remove or delete an id in a set
*
* set_dell
*
* @date 22-02-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param set the set which contains the id
* @param id the id that you want to delete
* @return
*/
STATUS set_dell(Set *set, Id id);
/**
*@brief returns the id of the indicated position
*
* set_get_id_at_position
*
* @date 26-02-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param set the set which contains the id
* @param position the position of the id
* @return
*/
Id  set_get_id_at_position(Set* set, int position);
#endif