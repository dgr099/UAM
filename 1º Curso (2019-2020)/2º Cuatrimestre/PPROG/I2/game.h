/** 
 * @brief It defines the game interface
 * for each command
 * 
 * @file game.h
 * @author Profesores PPROG, David Teófilo Garitagoitia Romero y José Manuel García Giráldez
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
#include "dice.h"
/*! \def MAX_OBJECTS
    \brief A macro that stores the maximum objects of a game
   
    Details.
*/
#define MAX_OBJECTS 4
/*! \var typedef struct _Game Game
    \brief A type definition for a game.
    
    Details.
*/
typedef struct _Game
{
  Player *player;                /*!< player of the game */
  Object *objects[MAX_OBJECTS + 1];                /*!< object of the game */
  Space *spaces[MAX_SPACES + 1]; /*!< spaces of the game */
  Command *last_cmd;            /*!< last command written by the user */
  Dice *dice;
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
STATUS game_update(Game *game, T_Command command, char *argument);
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
* game_get_last_principal_command
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param game the game from which we will get the information
* @return game->last_cmd the last command
*/
T_Command game_get_last_principal_command(Game *game);
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
/**
*@brief return the id of an space form their position
*
* game_get_space_id_at 
*
* @date 6-03-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param postion the position of the space
* @return NO_ID if there is an error, otherwise return the id of the space
*/
Id game_get_space_id_at(Game *game, int position);
/**
*@brief add a new object to the game
*
* game_add_object
*
* @date 01-03-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param object the addres to the object that we want to add
* @return ERROR if there is an error, otherwise return OK
*/
STATUS game_add_object(Game *game, Object *object);
/**
*@brief return the name of an object from his id
*
* game_get_object_name_at_id
*
* @date 01-03-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param id the id of the object that we want to know his name
* @return NULL if there is an error, otherwise return the name
*/
const char* game_get_object_name_at_id(Game* game, Id id);
/**
*@brief save a string with the name of all objects of an space in the names argument
*
* game_get_object_name_at_space
*
* @date 01-03-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space the space that you want to recive their objects name
* @param game the strcture game we initialite
* @param names the addres of an string in which the names will be allocated
* @return
*/
void game_get_objects_name_at_space(Space *space, Game *game, char *names);
/**
*@brief save a string with the name of all objects of the game and their locations in the names argument
*
* game_get_objects_location
*
* @date 01-03-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param names the addres of an string in which the names of the objects and their location will be allocated
* @return
*/
void game_get_objects_location(Game* game, char *names);
/**
*@brief get the argument insert by the user 
*
* game_get_last_argument 
*
* @date 05-03-2020
* @author José Manuel García Giráldez
*
* @param game the strcture game we initialite
* @return the argument
*/
char * game_get_last_argument(Game *game);
/**
*@brief get the comand insert by the user 
*
* game_get_last_command 
*
* @date 02-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @return the command
*/
Command* game_get_last_command(Game *game);
/**
*@brief get the player of the game
*
* game_get_player
*
* @date 02-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @return the player
*/
Player* game_get_player(Game *game);
/**
*@brief get the dice of the game
*
* game_get_player
*
* @date 02-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @return the dice
*/
Dice* game_get_dice(Game *game);

#endif
