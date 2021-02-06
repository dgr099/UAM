/** 
 * @brief It defines the player interface
 * for each command
 * 
 * @file player.h
 * @author José Manuel García Giráldez y David Teófilo Garitagoitia Romero
 * @version 1.0 
 * @date 5-02-2020 
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "types.h"

typedef struct _Player Player;
/**
*@brief Create the player
*
* player_create Create a player with a specific Id
*
* @date 07-02-2019
* @author: José Manuel García Giráldez
*
* @param id the id of the new player
* @return the new player that has been created
*/
Player *player_create(Id id);
/**
* @brief free a player
*
* player_destroy free a especific player 
*
* @date 07-02-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param player a player that has been created before
* @return ERROR if there is an error, otherwise return OK
*/
STATUS player_destroy(Player *player);
/**
* @brief name the player 
*
* player_set-name
*
* @date 07-02-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param player a player that has been created before
* @param name the name that the player will have
* @return ERROR if there is an error, otherwise return OK
*/
STATUS player_set_name(Player *player, char *name);
/**
* @brief set the id of the player
*
* player_set_id
*
* @date 07-02-2019
* @author: José Manuel García Giráldez
*
* @param object one object that has been created before
* @param id the id that the object will have
* @return ERROR if there is an error, otherwise return OK
*/
STATUS player_set_id(Player *player, int id);
/**
* @brief set the location of the player
*
* player_set_location
*
* @date 07-02-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param player a player that has been created before
* @param location the location that the player will have
* @return ERROR if there is an error, otherwise return OK
*/
STATUS player_set_location(Player *player, Id location);
/**
* @brief set the object that have the player
*
* player_set_object
*
* @date 07-02-2019
* @author: José Manuel García Giráldez
*
* @param player a player that has been created before
* @param objeto a object that have the player 
* @return ERROR if there is an error, otherwise return OK
*/
STATUS player_set_object(Player *player, Id objeto);
/**
* @brief get the name of the player
*
* player_get_name
*
* @date 07-02-2019
* @author: José Manuel García Giráldez
*
* @param player a player that has been created before
* @return player->name the name of the object we enter
*/
const char *player_get_name(Player *player);
/**
* @brief get the id of the player
*
* player_get_id
*
* @date 07-02-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param object one object that has been created before
* @return player->id the id of the player we enter
*/
Id player_get_id(Player *player);
/**
* @brief get the object that have the player
*
* player_get_object
*
* @date 07-02-2019
* @author: José Manuel García Giráldez
*
* @param player one player that has been created before
* @return player->object the object of the player we enter
*/
Id player_get_object(Player *player);
/**
* @brief get the location of the player
*
* player_get_location
*
* @date 07-02-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param player a player that has been created before
* @return player->location the location of the object we enter
*/
Id player_get_location(Player *player);
/**
* @brief print the information of the player on the screen
*
* player_print
*
* @date 07-02-2019
* @author: José Manuel García Giráldez
*
* @param object one object that has been created before
* @return ERROR if there is an error, otherwise return OK
*/
STATUS player_print(Player *player);
#endif
