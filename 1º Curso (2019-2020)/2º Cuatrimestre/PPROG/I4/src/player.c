/** 
 * @brief Store and set all the information about a player that is created, also  
 * can released the player
 * 
 * @file object.c
 * @author David Teófilo Garitagoitia Romero y José Manuel García Giráldez
 * @version 1.0 
 * @date 07-02-2019 
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/types.h"
#include "../include/player.h"
#include "../include/inventory.h"
#include "../include/game.h"
 
/** 
* @brief  The oplayer structure
*
* It stores information of the different players managed by the sytem
*/
struct _Player
{
	Id id;								/*!< Id of the player */
	char name[WORD_SIZE]; /*!< name of the player */
	Id location;					/*!< location of the player */
	Inventory* inventory;						/*!< objects in possesion of the player */
};

Player *player_create(Id id, int max)
{
	/*
 first of all it's checked if there is an error,then memory is reserved for 
 newplayer, finally the elements of the structure are initialited
*/
	Player *newPlayer = NULL;
	if (id == NO_ID) /*it's checked if there is an error*/
		return NULL;
	newPlayer = (Player *)malloc(sizeof(Player)); /*reserve memory for newsplayer*/
	if (newPlayer == NULL)
	{ /*it's checked if there is an error*/
		return NULL;
	}
	newPlayer->id = id;
	newPlayer->name[0] = '\0';
	newPlayer->inventory = inventory_create(0, max);
	return newPlayer;
}

STATUS player_destroy(Player *player)
{
	/* 
 First it's checked if is something wrong with the player that we want to free,  if there is no error the player is released
*/
	if (!player)
	{ /*it's checked if there is an error*/
		return ERROR;
	}
	inventory_destroy(player->inventory);
	free(player); /*release the player created*/
	return OK;
}

STATUS player_set_name(Player *player, char *name)
{
	/* 
 First it's checked if is something wrong with the player, the name or with the process of copy,  if there is no error the name is set
*/
	if (!player || !name)
	{ /*it's checked if there is an error*/
		return ERROR;
	}
	if (!strcpy(player->name, name))
	{ /*it's checked if there is an error*/
		return ERROR;
	}
	return OK;
}

STATUS player_set_id(Player *player, int id)
{
	/* First it's checked if is something wrong with the player, if there isnt the id is set */
	if (!player)
	{ /*it's checked if there is an error*/
		return ERROR;
	}
	player->id = id;
	return OK;
}

STATUS player_set_location(Player *player, Id location)
{
	/* First it's checked if is something wrong with the player, if there isnt the location is set */
	if (!player)
	{ /*it's checked if there is an error*/
		return ERROR;
	}
	player->location = location;
	return OK;
}

Id player_get_location(Player *player)
{
	/* 
 First it's checked if is something wrong with the player, if there is no error then the location of the player is returned
*/
	if (!player)
	{ /*it's checked if there is an error*/
		return NO_ID;
	}
	return player->location;
}

STATUS player_add_object(Player *player, Object* objeto)
{
	/* First it's checked if is something wrong with the player, if there isnt the the object is set */

	if (!player || !objeto)
	{ /*it's checked if there is an error*/
		return ERROR;
	}
	inventory_add(player_get_inventory(player), object_get_id(objeto));
	return OK;
}

STATUS player_dell_object(Player *player, Object* objeto){
	if(!player){
		return ERROR;
	}
	return inventory_dell(player_get_inventory(player), object_get_id(objeto));
}

const char *player_get_name(Player *player)
{
	/* 
 First it's checked if is something wrong with the player, if there is no error then the name of the player is returned
*/
	if (!player)
	{ /*it's checked if there is an error*/
		return NULL;
	}
	return player->name;
}

Id player_get_id(Player *player)
{
	/* 
 First it's checked if is something wrong with the player, if there is no error then the id of the player is returned
*/
	if (!player)
	{ /*it's checked if there is an error*/
		return NO_ID;
	}
	return player->id;
}

Inventory* player_get_inventory(Player* player){
	if(!player){
		return NULL;
	}
	return player->inventory;
}

STATUS player_print(Player *player)
{
	/* 
 First it's checked if is something wrong with the player, if there is no error then the information of the player is printed on the screen
*/

	if (!player)
	{ /*it's checked if there is an error*/
		return ERROR;
	}
	printf("(Id: %ld; Name: %s; Location: %ld)\n", player->id, player->name, player->location); /*print on screen the id, the location, the object and the name of the player*/
	inventory_print(stdout, player_get_inventory(player));

	return OK;
}
