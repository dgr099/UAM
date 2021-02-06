/** 
 * @brief It defines the link interface
 * for each command
 * 
 * @file link.h
 * @author David Teófilo Garitagoitia Romero
 * @version 1.0 
 * @date 17-03-2020 
 * @copyright GNU Public License
 */
#ifndef LINK_H
#define LINK_H
#include "../include/types.h"
/*! \var typedef struct _Link Link
    \brief A type definition for a link.
    
    Details.
*/
typedef struct _Link Link;
/**
*@brief Create the link, initialite the variables of the link
*
* link_create 
*
* @date 17-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param id the id of the new link
* @return the link created
*/
Link* link_create(Id id);
/**
*@brief set the name of a link
*
* link_set_name
*
* @date 17-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param link the link in which we want to set the name
* @param name the name we want to set
* @return Ok if there is no error, error otherwise
*/
STATUS link_set_name(Link* link, char* name);
/**
*@brief set the id1 of a link
*
* link_set_id1
*
* @date 17-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param link the link in which we want to set the id1
* @param id the id1 we want to set
* @return Ok if there is no error, error otherwise
*/
STATUS link_set_id1(Link* link, Id id);
/**
*@brief set the id2 of a link
*
* link_set_id1
*
* @date 17-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param link the link in which we want to set the id2
* @param id the id2 we want to set
* @return Ok if there is no error, error otherwise
*/
STATUS link_set_id2(Link* link, Id id);
/**
*@brief set if the link is closed (1) or open (0)
*
* link_set_open
*
* @date 17-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param link the link in which we want to set the id1
* @param open if the link is open (0), otherwise 1
* @return Ok if there is no error, error otherwise
*/
STATUS link_set_open(Link* link, int open);
/**
*@brief destroy a link
*
* link_destroy
*
* @date 17-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param link the link we want to destroy
* @return Ok if there is no error, error otherwise
*/
STATUS link_destory(Link* link);
/**
*@brief returns the id of the link that recive
*
* link_get_id
*
* @date 17-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param link the link of which you want to know their id
* @return the id of the link that it recive
*/
Id  link_get_id(Link* link);
/**
*@brief returns the name of the link that recive
*
* link_get_name
*
* @date 17-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param link the link of which you want to know their name
* @return the name of the link that it recives
*/
char* link_get_name(Link* link);
/**
*@brief returns the id1 of the link that recive
*
* link_get_id1
*
* @date 17-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param link the link of which you want to know their id1
* @return the id1 of the link that it recives
*/
Id  link_get_id1(Link* link);
/**
*@brief returns the id2 of the link that recive
*
* link_get_id2
*
* @date 17-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param link the link of which you want to know their id2
* @return the id2 of the link that it recives
*/
Id  link_get_id2(Link* link);
/**
*@brief returns True in case that the link is open, False otherwise
*
* link_is_open
*
* @date 17-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param link the link of which you want to know if its open or not
* @return True in case that the link is open, False otherwise
*/
BOOL  link_is_open(Link* link);
/**
*@brief prints the information of a link
*
* link_print
*
* @date 17-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param link the link we want to print
* @param f the file in which we want to print
* @return Ok if there is no error, error otherwise
*/
STATUS link_print(FILE* f,Link* link);
#endif
