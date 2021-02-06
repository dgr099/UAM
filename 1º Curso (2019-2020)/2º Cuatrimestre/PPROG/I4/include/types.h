/**
 * @brief It defines common types
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H
/*! \def WORD_SIZE
    \brief A macro that stores the word size.
   
    Details.
*/
#define WORD_SIZE 1000
/*! \def NO_ID
    \brief A macro that define no id.
   
    Details.
*/
#define NO_ID -1
/*! \var typedef long Id
    \brief A type definition for a id.
    
    Details.
*/
typedef long Id;
/**
* @brief  The Boolean enum
*/
typedef enum
{
  FALSE,/*FALSE*/
  TRUE  /*TRUE*/
} BOOL;
/**
* @brief  The Status enum
*/
typedef enum
{
  ERROR,  /*ERROR*/
  OK      /*OK*/
} STATUS;
/**
* @brief  The direction enum
*/
typedef enum
{
  N,  /*North*/
  S,  /*South*/
  E,  /*East*/
  W   /*West*/
} DIRECTION;

#endif
