/** 
 * @brief It defines the game interface
 * for each command
 * 
 * @file game.h
 * @author Profesores PPROG y David Teófilo Garitagoitia Romero
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
/**
* @brief The game structure
*
* It stores information of the game
*/
typedef struct _Game
{
  Player *player;                /*!< player of the game */
  Object *object;                /*!< object of the game */
  Space *spaces[MAX_SPACES + 1]; /*!< spaces of the game */
  T_Command last_cmd;            /*!< last command written by the user */
} Game;

/**
   Game interface implementation
*/
/**
*@brief Create the game, initialite the variables of the game
*
* game_create 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param game the strcture game we initialite
* @return ERROR if there is an error, otherwise return OK
*/
STATUS game_create(Game *game);
/**
*@brief Create the game from a file
*
* game_create_from_file 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param game the strcture game we initialite
* @param filename the name of the file we will use
* @return ERROR if there is an error, otherwise return OK
*/
STATUS game_create_from_file(Game *game, char *filename);
/**
* @brief update the game
*
* game_update  
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param game a game that has been created before
* @param cmd call to the structure cmd
* @return ERROR if there is an error, otherwise return OK
*/
STATUS game_update(Game *game, T_Command cmd);
/**
* @brief free the game
*
* game_destroy  
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param game a game that has been created before
* @return ERROR if there is an error, otherwise return OK
*/
STATUS game_destroy(Game *game);
/**
* @brief check if the game is over
*
* game_is_over 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param game a game that has been created before
* @return returns FALSE if the game is still going on and OK if the game is actually over
*/
BOOL game_is_over(Game *game);
/**
* @brief print the game data
*
* game_print_data 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param game a game that has been created before
* @return 
*/
void game_print_data(Game *game);
/**
* @brief get the space 
*
* game_get_space
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param game the game from which we will get the information
* @param id the id of the space
* @return the game spaces
*/
Space *game_get_space(Game *game, Id id);
/**
* @brief get the last command of the game
*
* game_get_last_command
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param game the game from which we will get the information
* @return game->last_cmd the last command
*/
T_Command game_get_last_command(Game *game);
/**
* @brief add a space in the game
*
* game_add_space
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param game the game in which we will add the space
* @param space the space which will be add in the game
* @return ERROR if there is an error, otherwise return OK
*/
STATUS game_add_space(Game *game, Space *space);
/**
*@brief get the location of an object 
*
* game_get_object_location 
*
* @date 09-02-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param object the object which we want to know the id
* @return space_get_id(game->spaces[i]) the id of the object
*/
Id game_get_object_location(Game *game, Id object);
#endif
