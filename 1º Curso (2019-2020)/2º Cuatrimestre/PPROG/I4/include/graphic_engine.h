/** 
 * @brief It defines a textual graphic engine
 * 
 * @file graphic_engine.h
 * @author Instructors of PPROG, David Teófilo Garitagoitia Romero
 * @version 1.0 
 * @date 18-01-2017
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "../include/game.h"
/*! \var typedef struct _Graphic_engine Graphic_engine
    \brief A type definition for a graphic engine.
    
    Details.
*/
typedef struct _Graphic_engine Graphic_engine;
/**
* @brief create graphic engine
*
* graphic_engine_create
*
* @date 13-01-2015
* @author: Instructors of PPROG
*@return the address of the graphic engine created
*/
Graphic_engine *graphic_engine_create();
/**
* @brief destroy graphic engine
*
* graphic_engine_destroy
*
* @date 13-01-2015
* @author: Instructors of PPROG
*@return
*/
void graphic_engine_destroy(Graphic_engine *ge);
/**
* @brief paint the game
*
* graphic_engine_paint_game
*
* @date 13-01-2015
* @param ge pointer to graphic_engine
* @param game pointer to game structure
* @param file pointer to the file
* @author: Instructors of PPROG
*@return
*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game, FILE *file);
/**
* @brief write the command 
*
* graphic_engine_write_command
*
* @date 13-01-2015
* @author: Instructors of PPROG
*@return
*/
void graphic_engine_write_command(Graphic_engine *ge, char *str);
/**
* @brief paint the intro
*
* graphic_engine_paint_intro
*
* @date 5-05-2020
* @param ge pointer to graphic_engine
* @param game pointer to game structure
* @param f file with the intro
* @author: David Teófilo Garitagoitia Romero
*@return
*/
void graphic_engine_paint_intro(Graphic_engine *ge, Game *game, char *f);
/**
* @brief paint the end
*
* graphic_engine_paint_intro
*
* @date 5-05-2020
* @param ge pointer to graphic_engine
* @param game pointer to game structure
* @param f file with the intro
* @author: David Teófilo Garitagoitia Romero
*@return
*/
void graphic_engine_paint_end(Graphic_engine *ge, Game *game, char *f);
#endif
