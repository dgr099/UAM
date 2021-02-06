/** 
 * @brief It defines the player interface
 * for each command
 * 
 * @file player.h
 * @author David Teófilo Garitagoitia Romero y José Manuel García Giráldez
 * @version 1.0 
 * @date 5-02-2020 
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "../include/types.h"
#include "../include/inventory.h"
/*! \var typedef struct _Player Player
    \brief A type definition for a player.
    
    Details.
*/
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
* @param max the maximum number of objects that he can store
* @return the new player that has been created
*/
Player *player_create(Id id, int max);
/**
* @brief free a player
*
* player_destroy free a especific player 
*
* @date 07-02-2019
* @author: José Manuel García Giráldez
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
* @param player the player you want to set id
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
* player_add_object
*
* @date 07-02-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param player a player that has been created before
* @param objeto a object that will be having by the player 
* @return ERROR if there is an error, otherwise return OK
*/
STATUS player_add_object(Player *player, Object* objeto);
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
* @param player the player you want to get their id
* @return player->id the id of the player we enter
*/
Id player_get_id(Player *player);
/**
* @brief get the location of the player
*
* player_get_location
*
* @date 07-02-2019
* @author: José Manuel García Giráldez
*
* @param player a player that has been created before
* @return player->location the location of the object we enter
*/
Id player_get_location(Player *player);
/**
* @brief get the inventory that have the player
*
* player_get_inventory
*
* @date 14-02-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param player one player that has been created before
* @return  the inventory of the player we enter
*/
Inventory* player_get_inventory(Player* player);
/**
* @brief print the information of the player on the screen
*
* player_print
*
* @date 07-02-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param player the player whose info you wnat to print
* @return ERROR if there is an error, otherwise return OK
*/
STATUS player_print(Player *player);
/**
* @brief remove of an object that have the player
*
* player_dell_object
*
* @date 10-3-2020
* @author: David Teófilo Garitagoitia Romero
* 
* @param player the player that have the object
* @param objeto the object that we want to delete from player
* @return ERROR if there is an error, otherwise return OK
*/
STATUS player_dell_object(Player *player, Object* objeto);
#endif
