/** 
 * @brief It implements the npc interpreter
 * 
 * @file npc.h
 * @author David teófilo Garitagoitia Romero
 * @version 1.0 
 * @date 1-05-2020 
 * @copyright GNU Public License
 */

#ifndef NPC_H
#define NPC_H
#include <stdio.h>
#include "../include/types.h"
/*! \def MAX_DIALOGUES
    \brief A macro that stores the maximum dialogues of a npc
   
    Details.
*/
#define MAX_DIALOGUES 10
/*! \var typedef struct _Npc Npc
    \brief A type definition for a npc.
    
    Details.
*/
typedef struct _Npc Npc;
/**
*@brief Create a npc
*
* npc_init
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param id the id of the new npc
* @return the new npc that has been created
*/
Npc* npc_init(Id id);
/**
*@brief set the name of an npc
*
* npc_set_name
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param npc the npc
* @param name the name we want to give it
* @return ok if there is no error, error otherwise
*/
STATUS npc_set_name(Npc *npc, char* name);
/**
*@brief add a new dialogue to a npc
*
* npc_add_dialogue
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param npc the npc
* @param dialogue the dialogue we want to give it
* @return ok if there is no error, error otherwise
*/
STATUS npc_add_dialogue(Npc *npc, char *dialogue);
/**
*@brief set the culpability of an npc
*
* npc_set_culpability
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param npc the npc
* @param g 1 if its guilty 0 otherwise
* @return ok if there is no error, error otherwise
*/
STATUS npc_set_culpability(Npc *npc, BOOL g);
/**
*@brief return a random dialogue of the npc
*
* npc_get_random_dialogue
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param npc the npc
* @return a random dialogue
*/
char* npc_get_random_dialogue(Npc *npc);
/**
*@brief return 1 if the npc is guilty
*
* npc_get_guilty
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param npc the npc
* @return 1 if its guilty, 0 otherwise
*/
BOOL npc_get_guilty(Npc *npc);
/**
*@brief destroy an npc
*
* npc_destroy
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param npc the npc
* @return ok if there is no error
*/
STATUS npc_destroy(Npc *npc);
/**
*@brief used to set the position of an npc
*
* npc_set_position
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param npc the npc
* @param position the position you wnat to set
* @return Ok if there is no error
*/
STATUS npc_set_position(Npc *npc, Id position);
/**
*@brief return the position of an npc
*
* npc_get_position
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param npc the npc
* @return the position of an npc
*/
Id npc_get_position(Npc *npc);
/**
*@brief return the initial of an npc
*
* npc_get_initial
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param npc the npc
* @return the initial of the npc
*/
char npc_get_initial(Npc *npc);
/**
*@brief set the max number of dialogues
*
* npc_set_dialogues
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param npc the npc
* @param n the number of dialogues
* @return ok uf there is no error
*/
STATUS npc_set_number_dialogues(Npc *npc, int n);
/**
*@brief return the name of an npc
*
* npc_get_na,e
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param npc the npc
* @return the name of the npc
*/
char* npc_get_name(Npc *npc);
/**
*@brief set the description
*
* npc_set description
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param npc the npc
* @param descr the description of the npc
* @return ok if there is no error
*/
STATUS npc_set_description(Npc *npc, char *descr);
/**
*@brief return the description of the npc
*
* npc_get_description
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param npc the npc
* @return the description of the npc
*/
char* npc_get_description(Npc *npc);
/**
*@brief return the id of the npc
*
* npc_get_id
*
* @date 1-05-2020
* @author David Teófilo Garitagoitia Romero
*
* @param npc the npc
* @return the id of the npc
*/
Id npc_get_id(Npc *npc);

#endif