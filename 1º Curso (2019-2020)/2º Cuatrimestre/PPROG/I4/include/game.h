/** 
 * @brief It defines the game interface
 * for each command
 * 
 * @file game.h
 * @author Instructors of PPROG, David Teófilo Garitagoitia Romero, José Manuel García Giráldez
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "../include/command.h"
#include "../include/cmdAnswer.h"
#include "../include/space.h"
#include "../include/player.h"
#include "../include/object.h"
#include "../include/dice.h"
#include "../include/link.h"
#include "../include/npc.h"
/*! \def MAX_OBJECTS
    \brief A macro that stores the maximum objects of a game
   
    Details.
*/
#define MAX_OBJECTS 30
/*! \var typedef struct _Game Game
    \brief A type definition for a game.
    
    Details.
*/
typedef struct _Game Game;

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
* @return the game created
*/
Game* game_create();
/**
*@brief Create the game from a file
*
* game_create_from_file 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param filename the name of the file we will use
* @return ERROR if there is an error, otherwise return OK
*/
Game* game_create_from_file(char *filename);
/**
* @brief update the game
*
* game_update  
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param game a game that has been created before
* @param command call to the structure cmd
* @param argument the argument of the cmd
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
* @brief add a npc in the game
*
* game_add_npc
*
* @date 1-05-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the game in which we will add the space
* @param npc the npc which will be add in the game
* @return ERROR if there is an error, otherwise return OK
*/
STATUS game_add_npc(Game *game, Npc *npc);
/**
*@brief get the location of an object 
*
* game_get_object_location 
*
* @date 09-02-2020
* @author David Garitagoitia Romero
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
* @param position the position of the space
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
* @date 14-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @return the addres of the player
*/
Player* game_get_player(Game *game);
/**
*@brief get the dice of the game
*
* game_get_player
*
* @date 13-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @return the addres of the dice
*/
Dice* game_get_dice(Game *game);
/**
*@brief get the player objects of the game
*
* game_get_player_objects
*
* @date 13-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param names the string in which the objects will be written
*/
void  game_get_player_objects(Game* game,char *names);
/**
*@brief set the player of the game
*
* game_set_player
*
* @date 13-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param player the addres of the player we want to set
* @return Ok if there is no error, ERROR otherwise
*/
STATUS game_set_player(Game* game, Player* player);
/**
*@brief add a link to the game
*
* game_add_link
*
* @date 13-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param link the link that we want to add to the game
* @return Ok if there is no error, ERROR otherwise
*/
STATUS game_add_link(Game *game, Link *link);
/**
*@brief return a link pointer from their id
*
* game_get_link_at_id
*
* @date 13-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param id the id of the link we want to get
* @return a pointer to the link that have that id
*/
Link* game_get_link_at_id(Game* game, Id id);
/**
*@brief returns the id of the souther link of the space
*
* game_get_south
*
* @date 13-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param space the space we want to know about its south link 
* @return the id of the south link of the space
*/
Id game_get_south(Game* game, Space* space);
/**
*@brief returns the id of the north link of the space
*
* game_get_north
*
* @date 13-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param space the space we want to know about its north link 
* @return the id of the north link of the space
*/
Id game_get_north(Game* game, Space* space);
/**
*@brief returns the id of the east of the space
*
* game_get_east
*
* @date 13-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param space the space we want to know about its east link 
* @return the id of the east link of the space
*/
Id game_get_east(Game* game, Space* space);
/**
*@brief returns the id of the west of the space
*
* game_get_west
*
* @date 13-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param space the space we want to know about its west link 
* @return the id of the west link of the space
*/
Id game_get_west(Game* game, Space* space);
/**
*@brief returns the id of the up of the space
*
* game_get_up
*
* @date 13-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param space the space we want to know about its west link 
* @return the id of the west link of the space
*/
Id game_get_up(Game* game, Space* space);
/**
*@brief returns the id of the down of the space

* game_get_down
*
* @date 13-03-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param space the space we want to know about its west link 
* @return the id of the west link of the space
*/
Id game_get_down(Game* game, Space* space);
/**
*@brief returns the object at id

* game_get_object_at_id
*
* @date 13-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param id the object id 
* @return the object with that id
*/
Object* game_get_object_at_id(Game* game, Id id);
/**
*@brief returns the num of spaces

* game_get_object_at_id
*
* @date 13-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @return the num of spaces
*/
int game_get_num_spaces(Game *game);
/**
*@brief returns a space at position

* game_get_object_at_id
*
* @date 13-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param position the position of the space
* @return the space at that position
*/
Space* game_get_space_at_position(Game *game, int position);
/**
*@brief returns the number of links

* game_get_num_links
*
* @date 13-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @return the num of links
*/
int game_get_num_links(Game *game);
/**
*@brief returns a link at position

* game_get_link_at_position
*
* @date 13-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param position the position of the space
* @return the link at that position
*/
Link* game_get_link_at_postion(Game *game, int position);
/**
*@brief returns the number of objects

* game_get_num_objects
*
* @date 13-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @return the num of objects
*/
int game_get_num_objects(Game *game);
/**
*@brief returns a object at position

* game_get_object_at_position
*
* @date 13-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param position the position of the space
* @return the object at that position
*/
Object* game_get_object_at_position(Game *game, int position);
/**
*@brief allow you to add a new cmd answer

* game_add_cmda
*
* @date 13-04-2020
* @author Daniel Cerrato Sanchez
*
* @param game the strcture game we initialite
* @param cmda the cmda you want to add
* @return Error in case there was an error, ok otherwise
*/
STATUS game_add_cmda(Game *game, CmdAnswer *cmda);
/**
*@brief return the initial of the npc name in the space

* game_get_npc_initial
*
* @date 13-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param space the position of the npc
* @return the initial of the npc
*/
char game_get_npc_initial(Game *game, Space *space);
/**
*@brief It is used to save the name of an npc

* game_get_full_npc_name
*
* @date 13-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param nombre the string in which the name will be saved
* @return
*/
void game_get_full_npc_name(Game *game, char *nombre);
/**
*@brief returns the npc in player position

* game_get_npc
*
* @date 13-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @return the npc in player position
*/
Npc* game_get_npc(Game *game);
/**
*@brief returns an npc at his name

* game_get_npc
*
* @date 18-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param name the name of the npc
* @return the npc with that name
*/
Npc* game_get_npc_at_name(Game *game, char *name);
/**
*@brief returns the tutorial

* game_get_tutorial
*
* @date 18-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @return the tutorial
*/
char* game_get_tutorial(Game *game);
/**
*@brief returns the end

* game_get_end
*
* @date 18-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @return the end
*/
char* game_get_end(Game *game);
/**
*@brief allows you to add a tutorial

* game_add_tutorial
*
* @date 18-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param tutorial the tutorial you want to add
* @return Ok if there is no error, error otherwise
*/
STATUS game_add_tutorial(Game *game, char *tutorial);
/**
*@brief allows you to add a end

* game_add_end
*
* @date 18-04-2020
* @author David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param end the end you want to add
* @return Ok if there is no error, error otherwise
*/
STATUS game_add_end(Game *game, char *end);
#endif
