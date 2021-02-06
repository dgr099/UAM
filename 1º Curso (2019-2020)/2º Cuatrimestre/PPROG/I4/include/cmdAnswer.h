/** 
 * @brief It implements the command answer interpreter
 * 
 * @file cmdAnswer.h
 * @author Daniel Cerrato Sanchez 
 * @version 1.0 
 * @date 15-04-2020 
 * @copyright GNU Public License
 */

#ifndef CMDANSWER_H
#define CMDANSWER_H
/*! \def MAX_ERROR
    \brief A macro that stores the number of diferents error
   
    Details.
*/
#define MAX_ERROR 10
#include "../include/types.h"
/*! \def MAX_F
    \brief A macro that stores the number of diferents strings that can be stored in ok/error answer
   
    Details.
*/
#define MAX_F 10
/*! \var typedef struct  _CmdAnswer CmdAnswer
    \brief A type definition for a CmdAnswer.
    
    Details.
*/
typedef struct  _CmdAnswer CmdAnswer;
/**
* @brief used to init a cmd answer
*
* @date 10-04-2020
* @author: Daniel Cerrato Sanchez
*
* @return a new cmd 
*/
CmdAnswer *CmdAnswer_init();
/**
* @brief used to add new error level
*
* @date 10-04-2020
* @author: Daniel Cerrato Sanchez
*
* @param cmda the cmd answer in which you want to add a new error level
* @return Ok if there is no error, error otherwise
*/
STATUS CmdAnswer_add_new_error(CmdAnswer *cmda);
/**
* @brief used to add new error level
*
* @date 10-04-2020
* @author: Daniel Cerrato Sanchez
*
* @param cmda the cmd answer in which you want to add a new error level
* @param awns the awnser you want to add
* @param n the level of the error
* @return Ok if there is no error, error otherwise
*/
STATUS CmdAnswer_add_error_at(CmdAnswer *cmda ,char *awns, int n);
/**
* @brief used to add ok answer
*
* @date 10-04-2020
* @author: Diego Grande Camarero
*
* @param cmda the cmd answer in which you want to add a new ok answer
* @param awns the new correct awnser that you want to add
* @return Ok if there is no error, error otherwise
*/
STATUS CmdAnswer_add_ok(CmdAnswer *cmda, char *awns);
/**
* @brief used to get a random error at n level
*
* @date 10-04-2020
* @author: Daniel Cerrato Sanchez
*
* @param cmda the cmd answer which contains the errors
* @param n the level of the error
* @return the random error at level n
*/
char* CmdAnswer_get_random_error(CmdAnswer *cmda, int n);
/**
* @brief used to get a random ok answer
*
* @date 10-04-2020
* @author: Diego Grande Camarero
* @param cmda the cmd answer which contains the errors
* @return the random ok answer
*/
char* CmdAnswer_get_random_ok(CmdAnswer* cmda);
/**
* @brief used to destroy releasing their memory
*
* @date 10-04-2020
* @author: Diego Grande Camarero
*
* @param cmda the cmd answer that you want to destroy
* @return Ok if there is no error, error otherwise
*/
STATUS CmdAnswer_destroy(CmdAnswer *cmda);

#endif
