/** 
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 * 
 * @file game.c
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/game.h"
#include "../include/space.h"
#include "../include/game_managment.h"
#include "../include/player.h"
#include "../include/object.h"
#include "../include/inventory.h"
#include "../include/link.h"
#include "../include/command.h"
#include "../include/cmdAnswer.h"
#include "../include/npc.h"
/*! \def N_CALLBACK
    \brief A macro that stores the number of callbacks
   
    Details.
*/
#define N_CALLBACK 18
/*! \def gp
    \brief A macro that stores the number of chars used on graphic description
   
    Details.
*/
#define gp 16
/*! \def MAX_NPC
    \brief A macro that stores the max number of npc
   
    Details.
*/
#define MAX_NPC 30
/**
* @brief The game structure
*
* It stores information of a game
*/
struct _Game
{
  Player *player;                /*!< player of the game */
  Object *objects[MAX_OBJECTS + 1];                /*!< object of the game */
  Space *spaces[MAX_SPACES + 1]; /*!< spaces of the game */
  Link *links[MAX_LINKS + 1];  /*!< links of the game */
  Command *last_cmd;            /*!< last command written by the user */
  Dice *dice; /*!< dice of the game */
  CmdAnswer *CmdAnswer[N_CALLBACK + 1]; /*!< arraay of cmdAnswer */
  Npc *npc[MAX_NPC + 1];  /*!< the npc of the game */
  char tutorial[WORD_SIZE]; /*!< string with the tutorial/introduction of the game */
  char End[WORD_SIZE];  /*!< string with the end of the game */
};
/*Private funtions*/
/**
*@brief update the ilumination of the game
*
* game_update_ilumination
*
* @date 13-4-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @return ERROR if there is an error, otherwise return OK
*/
STATUS game_update_ilumination(Game *game);
/**
*@brief returns an array with all incompatible id from the player objects
*
* game_player_incompatible
*
* @date 5-5-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @return an array with all incompatibles id form the player objects
*/
Id* game_player_incompatible(Game *game);
/**
*@brief -1 if the object dasn't have parameters, -2 if there is an error in the parameters, otherwise, the id of the object with wich it has dependency
*
* game_can_take_dependency
*
* @date 5-5-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param object the id of the dependency object
* @return returns -1 if there is no problem, -2 if there is an error in the parameters, otherwise it returns the id of the object with which it has dependency*/
Id game_can_take_dependency(Game *game, Object *object);
/**
*@brief  -1 if there is no problem, -2 if there is an error in the parameters, otherwise it returns the id of the object with which it has incompatibility
*
* game_can_take_incompatible
*
* @date 6-5-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param object the object you want to know their incompatible
* @return returns -1 if there is no problem, -2 if there is an error in the parameters, otherwise it returns the id of the object with which it has incompatibility*/
Id game_can_take_incompatible(Game *game, Object *object);
/**
*@brief   returns -1 if there is no problem, -2 if there is an error in the parameters, otherwise it returns the id of the object with which it has incompatibility
*
* game_can_drop_incompatible
*
* @date 5-10-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the strcture game we initialite
* @param object the id of the object you want to know their id drop incompatible
* @return returns -1 if there is no problem, -2 if there is an error in the parameters, otherwise it returns the id of the object with which it has incompatibility*/
Id game_can_drop_incompatible(Game *game, Id object);

/**
   Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game *game);

/**
   List of callbacks for each command in the game 
*/
/**
* @brief the callback to unknow command
** game_callback_unknown
*
* @date 06-03-2019
* @author Instructor of PPROG
* @param game Pointer to the game structure
* @return
*/
void game_callback_unknown(Game *game);
/**
* @brief the callback to unknow command
** game_callback_unknown
*
* @date 06-03-2019
* @author Instructor of PPROG
* @param game Pointer to the game structure
* @return
*/
void game_callback_unknown(Game *game);
/**
* @brief the callback to exit command
** game_callback_exit
*
* @date 06-03-2019
* @author Instructor of PPROG
* @param game Pointer to the game structure
* @return
*/
void game_callback_exit(Game *game);
/**
* @brief the callback to take command
** game_callback_take
*
* @date  07-02-2019 
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @return
*/
void game_callback_take(Game *game);
/**
* @brief the callback to drop command
** game_callback_drop
*
* @date  07-02-2019 
* @author José Manuel García Giráldez
* @param game Pointer to the game structure
* @return
*/
void game_callback_drop(Game *game);
/**
* @brief the callback to roll command
** game_callback_roll
*
 * @date 20-02-2020 
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @return
*/
void game_callback_roll(Game *game);
/**
* @brief the callback to move command
** game_callback_roll
*
 * @date 21-02-2020 
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @return
*/
void game_callback_move(Game *game);
/**
* @brief the callback to inspect command
** game_callback_inspect
*
 * @date 22-02-2020 
* @author José Manuel García Giráldez
* @param game Pointer to the game structure
* @return
*/
void game_callback_inspect(Game *game);
/**
* @brief the callback to next command
** game_callback_next
*
 * @date 22-02-2020 
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @return
*/
void game_callback_next(Game *game);
/**
* @brief the callback to back command
** game_callback_back
*
 * @date 22-02-2020 
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @return
*/
void game_callback_back(Game *game);
/**
* @brief the callback to left command
** game_callback_left
*
 * @date 22-02-2020 
* @author José Manuel García Giráldez
* @param game Pointer to the game structure
* @return
*/
void game_callback_right(Game *game);
/**
* @brief the callback to turn on command
** game_callback_turnon
*
 * @date 3-06-2020 
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @return
*/
void game_callback_left(Game *game);
/**
* @brief the callback to right command
** game_callback_right
*
 * @date 22-02-2020 
* @author José Manuel García Giráldez
* @param game Pointer to the game structure
* @return
*/
void game_callback_turnon(Game *game);
/**
* @brief the callback to turn off command
** game_callback_turnoff
*
 * @date 3-06-2020 
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @return
*/
void game_callback_turnoff(Game *game);
/**
* @brief the callback to open
** game_callback_open
*
 * @date 3-06-2020 
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @return
*/
void game_callback_open(Game *game);
/**
* @brief the callback to save
** game_callback_save
*
 * @date 3-06-2020 
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @return
*/
void game_callback_save(Game *game);
/**
* @brief the callback to load command
** game_callback_load
*
 * @date 3-06-2020 
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @return
*/
void game_callback_load(Game *game);
/**
* @brief the callback to talk command
** game_callback_talk
*
 * @date 3-06-2020 
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @return
*/
void game_callback_talk(Game *game);
/**
* @brief the callback to accuse command
** game_callback_accuse
*
 * @date 3-06-2020 
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @return
*/
void game_callback_accuse(Game *game);
/**
* @brief the callback to left command
** game_callback_accuse
*
 * @date 3-06-2020 
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @return
*/
void game_callback_left(Game *game);
/**
* @brief the callback to right command
** game_callback_right
*
 * @date 3-06-2020 
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @return
*/
void game_callback_right(Game *game);

static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_exit,
    game_callback_take,
    game_callback_drop,
    game_callback_roll,
    game_callback_move,
    game_callback_inspect,
    game_callback_turnon,
    game_callback_turnoff,
    game_callback_open,
    game_callback_save,
    game_callback_load,
    game_callback_talk,
    game_callback_accuse,
    game_callback_next,
    game_callback_back,
    game_callback_right,
    game_callback_left
};

Game* game_create()
{
  Game *game;
  int i;
  if(!(game=calloc(1, sizeof(Game)))){
    return ERROR;
  }
  game->dice=dice_create(0, 6, 1);
  if (!game->dice)
  { /*it's checked if there is an error*/
    return NULL;
  }
  for (i = 0; i <= MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }
  for (i = 0; i <= MAX_OBJECTS; i++)
  {
    game->objects[i] = NULL;
  }
  for (i = 0; i <= (MAX_OBJECTS*4); i++)
  {
    game->links[i] = NULL;
  }
  for(i=0; i<=N_CALLBACK; i++){
    game->CmdAnswer[i]=NULL;
  }
  for(i=0; i<=MAX_NPC; i++){
    game->npc[i]=NULL;
  }
  game->player=NULL;
  game->last_cmd=command_init();
  return game;
}

Game* game_create_from_file(char *filename)
{
  Game *game;
  /*First check if there is an error, if not then set the location of the player and set the object*/
  if (!(game=game_create())) /*it's checked if there is an error*/
    return NULL;
  if (game_managment_load_spaces(game, filename) == ERROR || game_managment_load_objects(game, filename) == ERROR || game_managment_load_player(game, filename) == ERROR || game_managment_load_links(game, filename) == ERROR || game_managment_load_CmdAnswers(game, filename) == ERROR || game_managment_load_npc(game, filename)==ERROR || game_managment_load_ending(game, filename)==ERROR || game_managment_load_tutorial(game, filename)==ERROR){ /*it's checked if there is an error*/
    return NULL;
  }
  if(!game_get_space(game, player_get_location(game_get_player(game))))
    return NULL;
  if(game_update_ilumination(game)==ERROR){
    return NULL;
  }
  return game;
}

Link* game_get_link_at_id(Game* game, Id id){
  int i; 
  if(!game || id==NO_ID){
    return NULL;
  }
  for(i=0; game->links[i]!=NULL; i++){
    if(link_get_id(game->links[i])==id){
      return game->links[i];
    }
  }
  return NULL;
}
/*Private funtions*/
/**
*@brief gate a link with a the name of that link
*
* game_get_link_id_at_name
*
* @date 15-4-2020
* @author: Jose Manuel García
*
* @param game the strcture game we initialite
* @param name the name we use
* @return Id the id of the link or NO_ID if there is an error or the isnt found
*/
Id game_get_link_id_at_name(Game* game, char* name){ 
  int i;
  if(!game || !name){
    return NO_ID;
  }
  for(i=0; game->links[i]!=NULL; i++){
    if(strcmp(link_get_name(game->links[i]), name)==0){
      return link_get_id(game->links[i]);
    }
  }
  return NO_ID;
}

Id game_get_south(Game* game, Space* space){
  Link* link;
  if(!game || !space){
    return NO_ID;
  }
  if(!(link=game_get_link_at_id(game, space_get_south(space)))){
    return NO_ID;
  }
  if(link_get_id2(link)!=space_get_id(space)){
    return link_get_id2(link);
  }
  return link_get_id1(link);
}

Id game_get_north(Game* game, Space* space){
  Link* link;
  if(!game || !space){
    return NO_ID;
  }
  if(!(link=game_get_link_at_id(game, space_get_north(space)))){
    return NO_ID;
  }
  if(link_get_id2(link)!=space_get_id(space)){
    return link_get_id2(link);
  }
  return link_get_id1(link);
}

Id game_get_east(Game* game, Space* space){
  Link* link;
  if(!game || !space){
    return NO_ID;
  }
  if(!(link=game_get_link_at_id(game, space_get_east(space)))){
    return NO_ID;
  }
  if(link_get_id2(link)!=space_get_id(space)){
    return link_get_id2(link);
  }
  return link_get_id1(link);
}

Id game_get_west(Game* game, Space* space){
  Link* link;
  if(!game || !space){
    return NO_ID;
  }
  if(!(link=game_get_link_at_id(game, space_get_west(space)))){
    return NO_ID;
  }
  if(link_get_id2(link)!=space_get_id(space)){
    return link_get_id2(link);
  }
  return link_get_id1(link);
}

Id game_get_up(Game* game, Space* space){
  Link* link;
  if(!game || !space){
    return NO_ID;
  }
  if(!(link=game_get_link_at_id(game, space_get_up(space)))){
    return NO_ID;
  }
  if(link_get_id2(link)!=space_get_id(space)){
    return link_get_id2(link);
  }
  return link_get_id1(link);
}

Id game_get_down(Game* game, Space* space){
  Link* link;
  if(!game || !space){
    return NO_ID;
  }
  if(!(link=game_get_link_at_id(game, space_get_down(space)))){
    return NO_ID;
  }
  if(link_get_id2(link)!=space_get_id(space)){
    return link_get_id2(link);
  }
  return link_get_id1(link);
}

STATUS game_add_object(Game *game, Object *object){
  /*First it's checked if is something wrong with the space, then add spaces in the game*/
  int i = 0;
  if (object == NULL)
  { /*it's checked if there is an error with space*/
    return ERROR;
  }
  while (game->objects[i] != NULL)
  { /*while there is no game spaces add 1 to i*/
    i++;
  }
  if (i >= MAX_OBJECTS)
  { /*if i more than MAX_SPACES is an Error*/
    return ERROR;
  }
  game->objects[i] = object;
  return OK;
}

STATUS game_add_npc(Game *game, Npc *npc){
  /*First it's checked if is something wrong with the npc, then add npc in the game*/
  int i = 0;
  if (npc == NULL)
  { /*it's checked if there is an error with space*/
    return ERROR;
  }
  while (game->npc[i] != NULL)
  { /*while there is no game npc add 1 to i*/
    i++;
  }
  if (i >= MAX_NPC)
  { /*if i more than MAX_NPC is an Error*/
    return ERROR;
  }
  game->npc[i] = npc;
  return OK;
}

STATUS game_add_cmda(Game *game, CmdAnswer *cmda){
  int i=0;
  if(!game || !cmda){
    return ERROR;
  }
  while(game->CmdAnswer[i]!=NULL){
    i++;
  }
  if( i>=N_CALLBACK){
    return ERROR;
  }
  game->CmdAnswer[i]=cmda;
  return OK;
}
Id game_get_object_location(Game *game, Id object)
{
  int i;
  for (i = 0; game->spaces[i] != NULL; i++)
  { /*check all the spaces*/ 
    if (space_is_object(game->spaces[i], object)==TRUE)
    { /*when is found the object we get the id*/
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID;
}
/*Private funtions*/
/**
*@brief check if the player have an object than can iluminate or not
*
* game_player_is_turned
*
* @date 15-4-2020
* @author: Jose Manuel García
*
* @param game the structure game we initialite
* @param player the structure player we use
* @return FALSE if there is an error or isnt turned or TRUE if is turned
*/
BOOL game_player_is_turned(Game *game, Player *player){
	int i, j;
	Set *set;
	Object *aux;
	if(!player || !game){
		return FALSE;
	}
	set=inventory_get_inside(player_get_inventory(player));
	
	for(i=0, j=set_get_num(set); i!=j; i++){
		if(!(aux=game_get_object_at_id(game, set_get_id_at_position(set, i)))){
      return FALSE;
    }
    if(object_get_turned(aux)==TRUE){
      return TRUE;
    }
	}
  return FALSE;
}

Id* game_player_incompatible(Game *game){
  int i, j;
  Id *d;
  if(!game){
    return NULL;
  }
  j=set_get_num(inventory_get_inside(player_get_inventory(game_get_player(game))));
  if(!(d=calloc(j, sizeof(Id))));
  for(i=0; i!=j; i++){
    d[i]=object_get_incompatible(game_get_object_at_id(game, set_get_id_at_position(inventory_get_inside(player_get_inventory(game_get_player(game))), i)));
  }
  return d;
}

Id game_can_take_dependency(Game *game, Object *object){
  Id dependecy_obj;
  int i, j;
  if(!game || !object){
    return -2;
  }
  dependecy_obj=object_get_dependency(object);
  if(dependecy_obj==NO_ID){
    return -1;
  }
  for(i=0, j=set_get_num(inventory_get_inside(player_get_inventory(game_get_player(game)))); i!=j; i++){
    if(set_get_id_at_position(inventory_get_inside(player_get_inventory(game_get_player(game))), i)==dependecy_obj){
      return -1;
    }
  }
  return dependecy_obj;
}

Id game_can_take_incompatible(Game *game, Object *object){
  Id incompatible_obj, id, *incompatible_pla;
  int i, j;
  if(!game || !object){
    return -2;
  }
  incompatible_obj=object_get_incompatible(object);
  incompatible_pla=game_player_incompatible(game);
  if(incompatible_obj==NO_ID){
    free(incompatible_pla);
    return -1;
  }
  for(i=0, j=set_get_num(inventory_get_inside(player_get_inventory(game_get_player(game)))); i!=j; i++){
    if((id=set_get_id_at_position(inventory_get_inside(player_get_inventory(game_get_player(game))), i))==incompatible_obj){
      free(incompatible_pla);
      return id;
    }
    if(incompatible_pla[i]==object_get_id(object)){
      free(incompatible_pla);
      return (object_get_id(object));
    }

  }
  free(incompatible_pla);
  return -1;
}

Id game_can_drop_incompatible(Game *game, Id object){
  int i, j, id;
  if(!game || !object){
    return -2;
  }
  for(i=0, j=set_get_num(space_get_objects(game_get_space(game, player_get_location(game_get_player(game))))); i!=j; i++){
    if((id=set_get_id_at_position(space_get_objects(game_get_space(game, player_get_location(game_get_player(game)))), i))==object){
      return id;
    }
  }
  return -1;
}
/*Private funtions*/
/**
*@brief drop all the objects in dependency with an object
*
* game_drop_all_dependencies
*
* @date 16-4-2020
* @author: Jose Manuel García
*
* @param game the structure game we initialite
* @param object the id of the object
* @return 
*/
void game_drop_all_dependencies(Game *game, Id object){
  int i, j;
  Object *aux;
  if(!game || object==NO_ID){
    return;
  }
  j=set_get_num(inventory_get_inside(player_get_inventory(game_get_player(game))));
  for(i=0; i!=j; i++){
    aux=game_get_object_at_id(game, set_get_id_at_position(inventory_get_inside(player_get_inventory(game_get_player(game))), i));
    if(object_get_dependency(aux)==object){
      if(space_add_object(game_get_space(game, player_get_location(game_get_player(game))), object_get_id(aux))==ERROR){
        return;
      }
      if(set_dell(inventory_get_inside(player_get_inventory(game_get_player(game))), object_get_id(aux))==ERROR){
        return;
      }
    }
  }
  return;
}
/*Private funtions*/
/**
*@brief check if the room is turned or not
*
* game_space_is_turned
*
* @date 15-4-2020
* @author: Jose Manuel García
*
* @param game the structure Game we initialite
* @param space the structure Space we use
* @return FALSE if there is an error or isnt turned or TRUE if is turned
*/
BOOL game_space_is_turned(Game *game, Space *space){
  int i, j;
  Set *set;
  Object *aux;
  if(!game || !space){
    return FALSE;
  }
  set=space_get_objects(space);
  for(i=0, j=set_get_num(set); i!=j; i++){
    if(!(aux=game_get_object_at_id(game, set_get_id_at_position(set, i)))){
      return FALSE;
    }
    if(object_get_turned(aux)==TRUE){
      return TRUE;
    }
  }
  return FALSE;
}

STATUS game_destroy(Game *game)
{
  /* 
 the game is free
*/
  int i = 0;
  /*call functions to free player and object*/
  player_destroy(game->player);
  dice_destroy(game->dice);
  command_destroy(game->last_cmd);
  for (i = 0; game->spaces[i] != NULL; i++)
  { /*free the space one for one*/
    space_destroy(game->spaces[i]);
  }
  for (i = 0; game->objects[i] != NULL && i<MAX_OBJECTS; i++)
  { /*free the objects one for one*/
    object_destroy(game->objects[i]);
  }
  for (i = 0; game->links[i] != NULL; i++)
  { /*free the links one for one*/
    link_destory(game->links[i]);
  }
  for(i=0; game->CmdAnswer[i]; i++){
    CmdAnswer_destroy(game->CmdAnswer[i]);
  }
  for(i=0; game->npc[i]; i++){
    npc_destroy(game->npc[i]);
  }
  free(game);
  return OK;
}

STATUS game_update(Game *game, T_Command command, char *argument)
{
if(!game)
return ERROR;
  /*match the previous command with the current one, updating the previous one*/
  if(command_set_principalcmd(game->last_cmd,command)==ERROR)
    return ERROR;
  command_set_argument(game->last_cmd, argument);

  (*game_callback_fn_list[command])(game);
  if(game_update_ilumination(game)==ERROR){
    return ERROR;
  }
  return OK;
}

STATUS game_update_ilumination(Game *game){
  Space *s_pl=NULL, *s_n=NULL, *s_s=NULL;
  /*check whether or not it has any object that can illuminate the space, if it is the case, set the illuminated variable of the space to true*/
  /*if neither the space nor the player has any object on, then the lighting is set to false*/
  /*update the player position light*/
  s_pl=game_get_space(game, player_get_location(game_get_player(game)));
  s_n=game_get_space(game, game_get_north(game, s_pl));
  s_s=game_get_space(game, game_get_south(game, s_pl));
  if(game_space_is_turned(game, s_pl)==FALSE && game_player_is_turned(game, game_get_player(game))==FALSE && s_pl){
    if(space_set_ilumination(s_pl, FALSE)==ERROR){
      return ERROR;
    }
  }
  /*otherwise, set the lighting to true*/
  else if(space_set_ilumination(s_pl, TRUE)==ERROR && s_pl)
    return ERROR;

  /*update the north player position light*/
  if(game_space_is_turned(game, s_n)==FALSE && s_n){
    if(space_set_ilumination(s_n, FALSE)==ERROR){
      return ERROR;
    }
  }
  /*otherwise, set the lighting to true*/
  else if(space_set_ilumination(s_n, TRUE)==ERROR && s_n)
    return ERROR;


  /*update the south player position light*/
  if(game_space_is_turned(game, s_s)==FALSE && s_s){
    if(space_set_ilumination(s_s, FALSE)==ERROR){
      return ERROR;
    }
  }
  /*otherwise, set the lighting to true*/
  else if(space_set_ilumination(s_s, TRUE)==ERROR && s_s)
    return ERROR;
  return OK;
}

int game_get_num_spaces(Game *game){
  int i;
  if(!game){
    return -1;
  }
  for(i=0; game->spaces[i]; i++);
  return i;
}

Space* game_get_space_at_position(Game *game, int position){
  if(!game || position<0 || position>=game_get_num_spaces(game)){
    return NULL;
  }
  return game->spaces[position];
}

int game_get_num_links(Game *game){
  int i;
  if(!game){
    return -1;
  }
  for(i=0; game->links[i]; i++);
  return i;
}

Link* game_get_link_at_postion(Game *game, int position){
  if(!game || position<0 || position>=game_get_num_links(game)){
    return NULL;
  }
  return game->links[position];
}

int game_get_num_objects(Game *game){
  int i;
  if(!game){
    return -1;
  }
  for(i=0; game->objects[i]; i++);
  return i;
}

Object* game_get_object_at_position(Game *game, int position){
  if(!game || position<0 || position>=game_get_num_objects(game))
    return NULL;
  return game->objects[position];
}

STATUS game_add_space(Game *game, Space *space)
{
  /*First it's checked if is something wrong with the space, then add spaces in the game*/
  int i = 0;
  if (!game || !space)
  { /*it's checked if there is an error with space*/
    return ERROR;
  }
  while (game->spaces[i] != NULL)
  { /*while there is no game spaces add 1 to i*/
    i++;
  }
  if (i >= MAX_SPACES)
  { /*if i more than MAX_SPACES is an Error*/
    return ERROR;
  }
  game->spaces[i] = space;
  return OK;
}

STATUS game_add_link(Game *game, Link *link)
{
  /*First it's checked if is something wrong with the space, then add spaces in the game*/
  int i = 0;
  if (!link || !game)
  { /*it's checked if there is an error with space*/
    return ERROR;
  }
  while (game->links[i] != NULL)
  { /*while there is no game spaces add 1 to i*/
    i++;
  }
  if (i >= (MAX_SPACES*4))
  { /*if i more than MAX_SPACES is an Error*/
    return ERROR;
  }
  game->links[i] = link;
  return OK;
}



STATUS game_set_player(Game* game, Player* player){
  if(!game || !player){
    return ERROR;
  }
  if(game->player!=NULL){
    player_destroy(game->player);
  }
  game->player=player;
  return OK;
}

Id game_get_space_id_at(Game *game, int position)
{
  /*First it's checked if is something wrong with the position, if isnt return the position*/
  if (position < 0 || position >= MAX_SPACES)
  { /*check if the position isnt more, or less than the limits*/
    return NO_ID;
  }
  return space_get_id(game->spaces[position]);
}

Space *game_get_space(Game *game, Id id)
{
  /*First it's checked if is something wrong with the id, if isnt return the game spaces*/
  int i = 0;

  if (id == NO_ID)
  { /*check if there is an error with the id*/
    return NULL;
  }
  for (i = 0; game->spaces[i] != NULL; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    { /*as long as there is space it will return that game space*/
      return game->spaces[i];
    }
  }
  return NULL;
}

T_Command game_get_last_principal_command(Game *game)
{
if(!game)
return NO_CMD;


  return command_get_principalcmd(game->last_cmd);
}

Command* game_get_last_command(Game *game)
{
if(!game)
return NULL;


  return (game->last_cmd);
}

char * game_get_last_argument(Game *game)
{
  if(!game)
  return FALSE;


  return command_get_argument(game->last_cmd);
}
/**
*@brief get the if of an object at the id
*
* game_get_object_id_at_name
*
* @date 10-4-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the structure Game we initialite
* @param name the name of the object
* @return Id the id of the object or NO_ID if there is an error
*/
Id game_get_object_id_at_name(Game* game, char *name){
  int i=0;
  const char* name2;
  if(!game || !name){
    return -1;
  }
  for(i=0; i!=MAX_OBJECTS && game->objects[i]!=NULL; i++){
    name2=object_get_name(game->objects[i]);
    if(strcmp(name, name2)==0){
      return object_get_id(game->objects[i]);
    }
  }
  return -1;
}

Object* game_get_object_at_id(Game* game, Id id){
  int i;
  if(!game || id==NO_ID){
    return NULL;
  }
  for(i=0; game->objects[i]!=NULL; i++){
    if (object_get_id(game->objects[i])==id){
      return game->objects[i];
    }
  }
  return NULL;
}

const char* game_get_object_name_at_id(Game* game, Id id){
  int i=0;
  if(id==NO_ID || !game ){
    return NULL;
  }
  for(i=0; i!=MAX_OBJECTS || game->objects[i]==NULL; i++){
    if(object_get_id(game->objects[i])==id){
      return object_get_name(game->objects[i]);
    }
  }
  return NULL;
}

void game_get_objects_name_at_space(Space *space, Game *game, char *names){
  int i=0, j, d;
  Object *object;
  const char* aux=NULL;
  if(!space)
    return;
  names[0]='\0';
  d=space_get_num(space);
  for(i=0; i!=d; i++){
    object=game_get_object_at_id(game, set_get_id_at_position(space_get_objects(space), i));
    if(object_get_hidden(object)==TRUE){
      continue;
    }
    aux=object_get_name(object);
    if(aux!=NULL){
    strcat(names, aux);      
    }
    strcat(names, " ");
  }
  for(j=strlen(names); j<gp; j++){
    names[j]=' ';
  }
  if(j!=gp){
    for(i=gp-3; i!=gp-6; i--)
      names[i]='.';
    names[gp-1]=' ';
    names[gp-2]=' ';
  }
  names[gp-1]='\0';
}
void  game_get_player_objects(Game* game,char *names){
  int i;
  names[0]='\0';
  for(i=0; game->objects[i]!=NULL; i++){
    if(inventory_is_object(player_get_inventory(game_get_player(game)), object_get_id(game->objects[i]))==TRUE){
      strcat(names, object_get_name(game->objects[i]));
      strcat(names, " ");
    }
  }
  return;
}

char game_get_npc_initial(Game *game, Space *space){
  Id position;
  int i;
  if(!game || !space){
    return ' ';
  }
  position=space_get_id(space);
  for(i=0; game->npc[i]; i++){
    if(npc_get_position(game->npc[i])==position){
      return npc_get_initial(game->npc[i]);
    }
  }
  return ' ';
}

Npc* game_get_npc_at_name(Game *game, char *name){
  int i=0;
  if(!game || !name)
    return NULL;
  for(i=0; game->npc[i]; i++){
    if(strcmp(name, npc_get_name(game->npc[i]))==0){
      return game->npc[i];
    }
  }
  return NULL;
}

void game_get_full_npc_name(Game *game, char *nombre){
  int i;
  Id position;
  if(!game || !nombre){
    return;
  }
  position=player_get_location(game_get_player(game));
  for(i=0; game->npc[i]; i++){
    if(npc_get_position(game->npc[i])==position){
      sprintf(nombre," %s", npc_get_name(game->npc[i]));      
      return;
    }
  }
  sprintf(nombre, " ");
}  

Npc* game_get_npc(Game *game){
  Id position;
  int i;
  if(!game){
    return NULL;
  }
  position=player_get_location(game_get_player(game));
  for(i=0; game->npc[i]; i++){
    if(npc_get_position(game->npc[i])==position){     
      return game->npc[i];
    }
  }
  return NULL;
}
void game_get_objects_location(Game* game, char *names){
  int i, j;
  names[0]='\0';
  char z[3];
  for(i=0; game->objects[i]!=NULL && i<MAX_OBJECTS; i++){
    if(object_get_hidden(game->objects[i])==TRUE){
      continue;
    }
    for(j=0; game->spaces[j]!=NULL; j++){
      if(space_is_object(game->spaces[j], object_get_id(game->objects[i]))==TRUE){
        strcat(names, object_get_name(game->objects[i]));
        strcat(names, ":");
        sprintf(z, "%ld", space_get_id(game->spaces[j]));
        strcat(names, z);
        strcat(names, ", ");
        break;
      }
    }  
  }
  names[strlen(names)-2]='\0';
}


void game_print_data(Game *game)
{
  int i = 0;
  printf("\n\n-------------\n\n");
  printf("=> Spaces: \n");
  for (i = 0; game->spaces[i] != NULL; i++)
  {
    space_print(game->spaces[i]);
  }
  /*printf("=> Object location: %d\n", (int)game_get_object_location(game, object_get_id(game->object)));*/
  printf("=> Player location: %d\n", (int)player_get_location(game->player));
  printf("prompt:> ");
}

Player* game_get_player(Game *game){
  if(!game){
    return NULL;
  }
  return game->player;
}
/**
*@brief all objects in space become visible
*
* game_search_space
*
* @date 11-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param space the space that you want to search
* @param game the strcture game we initialite
* @return Ok if there is no error
*/
STATUS game_search_space(Game *game, Space *space){
  int i, j;
  Object *object;
  if(!game || !space){
    return ERROR;
  }
  for(i=0, j=space_get_num(space); i!=j; i++){
    if(!(object=game_get_object_at_id(game, set_get_id_at_position(space_get_objects(space), i)))){
      return ERROR;
    }
    object_set_hidden(object, FALSE);
  }
  return OK;
}
char* game_get_tutorial(Game *game){
  if(!game){
    return NULL;
  }
  return game->tutorial;
}

STATUS game_add_tutorial(Game *game, char *tutorial){
  if(!tutorial || !game){
    return ERROR;
  }
  strcpy(game->tutorial, tutorial);
  return OK;
}

STATUS game_add_end(Game *game, char *end){
  if(!end || !game){
    return ERROR;
  }
  strcpy(game->End, end);
  return OK;
}


char* game_get_end(Game *game){
  if(!game){
    return NULL;
  }
  return game->End;
}

Dice* game_get_dice(Game *game){
  if(!game){
    return NULL;
  }
  return game->dice;  
}

BOOL game_is_over(Game *game)
{
  if(game_get_last_principal_command(game)==ACCUSE && strncmp(command_get_status(game_get_last_command(game)), "OK", 2)==0){
    return TRUE;
  }
  return FALSE;
}

/**
   Callbacks implementation for each action 
*/

void game_callback_unknown(Game *game)
{
  char *aux=NULL;
  aux=CmdAnswer_get_random_error(game->CmdAnswer[UNKNOWN], 0);
  command_set_status(game_get_last_command(game), aux);
  free(aux);
  return;
}

void game_callback_exit(Game *game)
{
  char *aux=NULL;
  aux=CmdAnswer_get_random_ok(game->CmdAnswer[EXIT]);
  command_set_status(game_get_last_command(game),aux);
  free(aux);
  return;
}

void game_callback_take(Game *game)
{
  Id object, obj;
  int i=0;
  char* object_name, st[WORD_SIZE], *aux=NULL, aux2[WORD_SIZE], *tok=NULL;
  if(!game){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TAKE], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;    
  }

  object_name=game_get_last_argument(game);  
  object=game_get_object_id_at_name(game, object_name);
    i++;  
  if(!object_name|| object_name[0]=='\0'){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TAKE], i);
    command_set_status(game_get_last_command(game), aux);
    goto fin;
  }
  i++;
  if(object==-1){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TAKE], i);
    command_set_status(game_get_last_command(game), aux);
    goto fin;
  }
  i++;
  if(space_get_num(game_get_space(game, player_get_location(game->player)))<=0 || space_is_object(game_get_space(game, player_get_location(game->player)), object)==FALSE){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TAKE], i);
    command_set_status(game_get_last_command(game), aux);
    goto fin;
  }
  i++;
  if(inventory_is_full(player_get_inventory(game_get_player(game)))==TRUE){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TAKE], i);
    command_set_status(game_get_last_command(game), aux);
    goto fin;
  }
  i++;
  if(object_get_movable(game_get_object_at_id(game, object))==FALSE){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TAKE], i);
    command_set_status(game_get_last_command(game), aux);
    goto fin;
  }
  i++;
  if((obj=game_can_take_incompatible(game, game_get_object_at_id(game, object)))!=-1){
    if(obj==-2){
    command_set_status(game_get_last_command(game), "ERROR");
    goto fin;      
    }
    else{
      aux=CmdAnswer_get_random_error(game->CmdAnswer[TAKE], i);
      strcpy(aux2, aux);
      tok=strtok(aux2, "[");
      sprintf(st, "%s", tok);
      strcat(st, game_get_last_argument(game));
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "[");
      strcat(st, tok);
      strcat(st, object_get_name(game_get_object_at_id(game, obj)));
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "\n\t");
      if(tok)    
        strcat(st, tok);  
      command_set_status(game_get_last_command(game), st);
      goto fin;
    } 
  }
  i++;
  if((obj=game_can_take_dependency(game, game_get_object_at_id(game, object)))!=-1){
    if(obj==-2){
    command_set_status(game_get_last_command(game), "ERROR");
    goto fin;      
    }
    else{
      aux=CmdAnswer_get_random_error(game->CmdAnswer[TAKE], i);
      strcpy(aux2, aux);
      tok=strtok(aux2, "[");
      sprintf(st, "%s", tok);
      strcat(st, object_get_name(game_get_object_at_id(game, obj)));
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "\n\t");
      if(tok)
        strcat(st, tok);
      command_set_status(game_get_last_command(game), st);
      goto fin; 
    } 
  }
  else{
    aux=CmdAnswer_get_random_ok(game->CmdAnswer[TAKE]);
    player_add_object(game->player, game_get_object_at_id(game, object));
    object_set_hidden(game_get_object_at_id(game, object), FALSE);
    space_dell_object(game_get_space(game, player_get_location(game->player)), game_get_object_id_at_name(game, command_get_argument(game->last_cmd)));
    command_set_status(game->last_cmd, aux);
  }
  fin:
  if(aux)
    free(aux); 
  return;
}

void game_callback_drop(Game *game)
{
  Id object; /*id;*/
  int n=0;
  char *object_name, *aux;
  if(!game){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[DROP], n);
    command_set_status(game_get_last_command(game),aux);
    free(aux);
    return;
  }
  object=game_get_object_id_at_name(game, command_get_argument(game->last_cmd));
  object_name=game_get_last_argument(game);
  n++;
  if(!object_name|| object_name[0]=='\0'){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[DROP], n);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  n++;
  if(inventory_is_object(player_get_inventory(game->player), object) == FALSE || inventory_is_emty(player_get_inventory(game_get_player(game)))==TRUE){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[DROP], n);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  n++;
  if(space_get_num(game_get_space(game, player_get_location(game->player)))>4){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[DROP], n);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  /*las incompatibilidades solo son para el take*/
  /*else if((id=game_can_drop_incompatible(game, object))!=-1){
    if(id==-2){
    command_set_status(game_get_last_command(game), "ERROR");
    return;      
    }
    else{
      sprintf(st, "ERROR, the object you want to drop is incompatible with %s", object_get_name(game_get_object_at_id(game, id)));
      command_set_status(game_get_last_command(game), st);       
    }
  }*/
  else{
    /*if(space_is_iluminated(game_get_space(game, player_get_location(game_get_player(game))))==FALSE){
      object_set_hidden(game_get_object_at_id(game, game_get_object_id_at_name(game, command_get_argument(game->last_cmd))), TRUE);
    }*/
    game_drop_all_dependencies(game, object);    
    space_add_object(game_get_space(game, player_get_location(game->player)), game_get_object_id_at_name(game, command_get_argument(game->last_cmd)));
    player_dell_object(game->player, game_get_object_at_id(game, object));
    aux=CmdAnswer_get_random_ok(game->CmdAnswer[DROP]);
    command_set_status(game->last_cmd, aux);
    free(aux);

  }
  return;
}

void game_callback_roll(Game *game){
  int n=0;
  char *aux;
  if(!game || !game->dice){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[ROLL], n);
    command_set_status(game->last_cmd, aux);
    free(aux);
    return;
  }
  dice_roll(game->dice);
  aux=CmdAnswer_get_random_ok(game->CmdAnswer[ROLL]);
  command_set_status(game->last_cmd, aux);
  return;
}

void game_callback_move(Game *game){
  Id next_id = NO_ID;
  Id space_id = NO_ID;
  char *aux, aux2[WORD_SIZE], *tok=NULL;
  int n=0;
  char* argument;
  char* link;
  char st[WORD_SIZE]=" ";
  if(!game){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  space_id = player_get_location(game->player);
  argument=game_get_last_argument(game);
  n++;
  if(!argument || argument[0]=='\0'){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  n++;
  if( !strcmp(argument, "south") || !strcmp(argument, "s")){  
    if((next_id=game_get_south(game, game_get_space(game, space_id)))==NO_ID){
      aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);
      strcpy(aux2, aux);
      tok=strtok(aux2, "[");
      sprintf(st, "%s", tok);
      strcat(st, "south");
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "\n\t");
      if(tok)
        strcat(st, tok);
      command_set_status(game_get_last_command(game), st);
      free(aux);
      return;
    }
    n++;
    if(link_is_open(game_get_link_at_id(game, space_get_south(game_get_space(game, space_id))))==FALSE){
      link= link_get_name(game_get_link_at_id(game, space_get_south(game_get_space(game, space_id))));
      aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);
      strcpy(aux2, aux);
      tok=strtok(aux2, "[");
      sprintf(st, "%s", tok);
      strcat(st, link);
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "\n\t");
      if(tok)
        strcat(st, tok);
      command_set_status(game_get_last_command(game), st);
      free(aux);
      return;    
    }
  }

  else if(!strcmp(argument, "north") || !strcmp(argument, "n")){
    if((next_id=game_get_north(game, game_get_space(game, space_id)))==NO_ID){
      aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);
      strcpy(aux2, aux);
      tok=strtok(aux2, "[");
      sprintf(st, "%s", tok);
      strcat(st, "north");
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "\n\t");
      if(tok)
        strcat(st, tok);
      command_set_status(game_get_last_command(game), st);
      free(aux);
      return;
    }
    n++;
    if(link_is_open(game_get_link_at_id(game, space_get_north(game_get_space(game, space_id))))==FALSE){
      link= link_get_name(game_get_link_at_id(game, space_get_north(game_get_space(game, space_id))));
      aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);
      strcpy(aux2, aux);
      tok=strtok(aux2, "[");
      sprintf(st, "%s", tok);
      strcat(st, link);
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "\n\t");
      if(tok)
        strcat(st, tok);
      command_set_status(game_get_last_command(game), st);
      free(aux);
      return;  
    } 
  }

  else if(!strcmp(argument, "east") || !strcmp(argument, "e")){
    if((next_id=game_get_east(game, game_get_space(game, space_id)))==NO_ID){
      aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);
      strcpy(aux2, aux);
      tok=strtok(aux2, "[");
      sprintf(st, "%s", tok);
      strcat(st, "east");
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "\n\t");
      if(tok)
        strcat(st, tok);
      command_set_status(game_get_last_command(game), st);
      free(aux);
      return;
    }
    if(link_is_open(game_get_link_at_id(game, space_get_east(game_get_space(game, space_id))))==FALSE){
      link= link_get_name(game_get_link_at_id(game, space_get_east(game_get_space(game, space_id))));
      aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);
      strcpy(aux2, aux);
      tok=strtok(aux2, "[");
      sprintf(st, "%s", tok);
      strcat(st, link);
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "\n\t");
      if(tok)
        strcat(st, tok);
      command_set_status(game_get_last_command(game), st);
      free(aux);
      return;   
    }  
  }

  else if(!strcmp(argument, "west") || !strcmp(argument, "w")){
    if((next_id=game_get_west(game, game_get_space(game, space_id)))==NO_ID){
      aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);
      strcpy(aux2, aux);
      tok=strtok(aux2, "[");
      sprintf(st, "%s", tok);
      strcat(st, "west");
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "\n\t");
      if(tok)
        strcat(st, tok);
      command_set_status(game_get_last_command(game), st);
      free(aux);
      return;
    }
    if(link_is_open(game_get_link_at_id(game, space_get_west(game_get_space(game, space_id))))==FALSE){
      link= link_get_name(game_get_link_at_id(game, space_get_west(game_get_space(game, space_id))));
      aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);
      strcpy(aux2, aux);
      tok=strtok(aux2, "[");
      sprintf(st, "%s", tok);
      strcat(st, link);
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "\n\t");
      if(tok)
        strcat(st, tok);
      command_set_status(game_get_last_command(game), st);
      free(aux);
      return;  
    }
  }
  else if( !strcmp(argument, "up") || !strcmp(argument, "u")){  
    if((next_id=game_get_up(game, game_get_space(game, space_id)))==NO_ID){
      aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);
      strcpy(aux2, aux);
      tok=strtok(aux2, "[");
      sprintf(st, "%s", tok);
      strcat(st, "up");
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "\n\t");
      if(tok)
        strcat(st, tok);
      command_set_status(game_get_last_command(game), st);
      free(aux);
      return;
    }
    n++;
    if(link_is_open(game_get_link_at_id(game, space_get_up(game_get_space(game, space_id))))==FALSE){
      link= link_get_name(game_get_link_at_id(game, space_get_up(game_get_space(game, space_id))));
      aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);
      strcpy(aux2, aux);
      tok=strtok(aux2, "[");
      sprintf(st, "%s", tok);
      strcat(st, link);
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "\n\t");
      if(tok)
        strcat(st, tok);
      command_set_status(game_get_last_command(game), st);
      free(aux);
      return;    
    }
  }  
  else if( !strcmp(argument, "down") || !strcmp(argument, "d")){  
    if((next_id=game_get_down(game, game_get_space(game, space_id)))==NO_ID){
      aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);
      strcpy(aux2, aux);
      tok=strtok(aux2, "[");
      sprintf(st, "%s", tok);
      strcat(st, "down");
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "\n\t");
      if(tok)
        strcat(st, tok);
      command_set_status(game_get_last_command(game), st);
      free(aux);
      return;
    }
    n++;
    if(link_is_open(game_get_link_at_id(game, space_get_down(game_get_space(game, space_id))))==FALSE){
      link= link_get_name(game_get_link_at_id(game, space_get_down(game_get_space(game, space_id))));
      aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);
      strcpy(aux2, aux);
      tok=strtok(aux2, "[");
      sprintf(st, "%s", tok);
      strcat(st, link);
      tok=strtok(NULL, "]");
      tok=strtok(NULL, "\n\t");
      if(tok)
        strcat(st, tok);
      command_set_status(game_get_last_command(game), st);
      free(aux);
      return;    
    }
  }
  else{
    n++;
    n++;
    aux=CmdAnswer_get_random_error(game->CmdAnswer[MOVE], n);;
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }  
  aux=CmdAnswer_get_random_ok(game->CmdAnswer[MOVE]);
  player_set_location(game_get_player(game), next_id);
  command_set_status(game_get_last_command(game), aux);
  free(aux);
  return;
}

void game_callback_inspect(Game *game){
  char* object_name, *aux, aux2[WORD_SIZE], *tok, *lnk;
  int n=0;
  Id open;
  const char* description;
  char status[WORD_SIZE];
  Id id; 
  if(!game){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[INSPECT], n);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  n++;
  object_name=game_get_last_argument(game);
  if(!object_name|| object_name[0]=='\0'){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[INSPECT], n);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  n++;
  if(!strcmp(object_name, "s")|| !strcmp(object_name, "space")){
    description=space_get_description2(game_get_space(game, player_get_location(game_get_player(game))));
    if (space_is_iluminated(game_get_space(game, player_get_location(game_get_player(game))))==FALSE){
      aux=CmdAnswer_get_random_error(game->CmdAnswer[INSPECT], n);
      command_set_status(game_get_last_command(game), aux);
      free(aux);
      return;
    }
    game_search_space(game, game_get_space(game, player_get_location(game_get_player(game))));  
    n++;
    if(!description || description[0]=='\0' || description[0]==' '){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[INSPECT], n);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
    }
    goto status;
  }
  n++;
  n++;
  if((id=game_get_object_id_at_name(game, object_name))==-1){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[INSPECT], n);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  n++;
  if(inventory_is_object(player_get_inventory(game_get_player(game)), id)==FALSE && space_is_object(game_get_space(game, player_get_location(game_get_player(game))), id)==FALSE){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[INSPECT], n);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  n++;
  description=object_get_description(game_get_object_at_id(game, id));
  if(!description || description[0]=='\0' || description[0]==' '){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[INSPECT], n);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  status:
  aux=CmdAnswer_get_random_ok(game->CmdAnswer[INSPECT]);
  strcpy(aux2, aux);
  tok=strtok(aux2, "[");
  sprintf(status, "%s", tok);
  strcat(status, description);
  if(!strcmp(object_name, "s")|| !strcmp(object_name, "space")){
    command_set_status(game_get_last_command(game), status);
    free(aux);
    return;    
  }
  tok=strtok(NULL, "]");
  tok=strtok(NULL, "[");
  if(tok)
    strcat(status, tok);
  else{
    free(aux);
    command_set_status(game_get_last_command(game), status);
    return;    
  }
  if(object_get_movable(game_get_object_at_id(game, game_get_object_id_at_name(game, object_name)))==TRUE)
    strcat(status, " movable ");
  else
    strcat(status, " immovable ");
  if(object_get_open(game_get_object_at_id(game, game_get_object_id_at_name(game, object_name)))!=NO_ID){
    open=object_get_open(game_get_object_at_id(game, game_get_object_id_at_name(game, object_name)));
    lnk=link_get_name(game_get_link_at_id(game, open));
    if(lnk){
      strcat(status, " can open ");
      strcat(status, lnk);      
    }
  }
  if(object_get_illuminate(game_get_object_at_id(game, game_get_object_id_at_name(game, object_name)))==TRUE){
    strcat(status, " can be illuminated");
  }
  if(object_get_turned(game_get_object_at_id(game, game_get_object_id_at_name(game, object_name)))==TRUE)
    strcat(status, " is turned on ");
  tok=strtok(NULL, "]");
  tok=strtok(NULL, "\n\t");
  if(tok)
    strcat(status, tok);
  command_set_status(game_get_last_command(game), status);
  free(aux);
  return;
}

void game_callback_turnon(Game *game){
  Id obje;
  char *aux, aux2[WORD_SIZE], *tok, st[WORD_SIZE]=" ";
  const char *obj_name=NULL;
  int i=0;
  if(!game){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TURNON], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  i++;
  obje=game_get_object_id_at_name(game, game_get_last_argument(game));
  obj_name=object_get_name(game_get_object_at_id(game, obje));
  if(obje==-1){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TURNON], i);
    strcpy(aux2, aux);
    tok=strtok(aux2, "[");
    sprintf(st, "%s", tok);
    strcat(st, obj_name);
    tok=strtok(NULL, "]");
    tok=strtok(NULL, "\n\t|");
    if(tok)
      strcat(st, tok);
    command_set_status(game_get_last_command(game), st);
    free(aux);
    return;   
  } 
  i++; 
  if(inventory_is_object(player_get_inventory(game_get_player(game)), obje)==FALSE && space_is_object(game_get_space(game, player_get_location(game_get_player(game))), obje)==FALSE){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TURNON], i);
    strcpy(aux2, aux);
    tok=strtok(aux2, "[");
    sprintf(st, "%s", tok);
    strcat(st, obj_name);
    tok=strtok(NULL, "]");
    tok=strtok(NULL, "\n\t|");
    if(tok)
      strcat(st, tok);
    command_set_status(game_get_last_command(game), st);
    free(aux);
    return;  
  }
  i++;
  if(object_get_illuminate(game_get_object_at_id(game, obje))==FALSE){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TURNON], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;    
  }
  i++;
  if(object_get_turned(game_get_object_at_id(game, obje))==TRUE){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TURNON], i);
    strcpy(aux2, aux);
    tok=strtok(aux2, "[");
    sprintf(st, "%s", tok);
    strcat(st, obj_name);
    tok=strtok(NULL, "]");
    tok=strtok(NULL, "\n\t|");
    if(tok)
      strcat(st, tok);
    command_set_status(game_get_last_command(game), st);
    free(aux);
    return;  
  }
  aux=CmdAnswer_get_random_ok(game->CmdAnswer[TURNON]);
  object_turned(game_get_object_at_id(game, obje), TRUE);
  command_set_status(game_get_last_command(game), aux);
  free(aux);
  return;
}

void game_callback_turnoff(Game *game){
  Id obje;
  int i=0;
  char *aux, aux2[WORD_SIZE], st[WORD_SIZE], *tok; 
  const char *obj_name;
  if(!game){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TURNOFF], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  i++;
  obje=game_get_object_id_at_name(game, game_get_last_argument(game));
  obj_name=object_get_name(game_get_object_at_id(game, obje));
  if(obje==-1){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TURNOFF], i);
    strcpy(aux2, aux);
    tok=strtok(aux2, "[");
    sprintf(st, "%s", tok);
    strcat(st, obj_name);
    tok=strtok(NULL, "]");
    tok=strtok(NULL, "\n\t|");
    if(tok)
      strcat(st, tok);
    command_set_status(game_get_last_command(game), st);
    free(aux);
    return;     
  }
  i++;
  if(inventory_is_object(player_get_inventory(game_get_player(game)), obje)==FALSE && space_is_object(game_get_space(game, player_get_location(game_get_player(game))), obje)==FALSE){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TURNOFF], i);
    strcpy(aux2, aux);
    tok=strtok(aux2, "[");
    sprintf(st, "%s", tok);
    strcat(st, obj_name);
    tok=strtok(NULL, "]");
    tok=strtok(NULL, "\n\t|");
    if(tok)
      strcat(st, tok);
    command_set_status(game_get_last_command(game), st);
    free(aux);
    return;  
  }
  i++;
  if(object_get_illuminate(game_get_object_at_id(game, obje))==FALSE){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TURNOFF], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;  
  }
  i++;
  if(object_get_turned(game_get_object_at_id(game, obje))==FALSE){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TURNOFF], i);
    strcpy(aux2, aux);
    tok=strtok(aux2, "[");
    sprintf(st, "%s", tok);
    strcat(st, obj_name);
    tok=strtok(NULL, "]");
    tok=strtok(NULL, "\n\t|");
    if(tok)
      strcat(st, tok);
    command_set_status(game_get_last_command(game), st);
    free(aux);
    return;  
  }
  aux=CmdAnswer_get_random_ok(game->CmdAnswer[TURNOFF]);
  object_turned(game_get_object_at_id(game, obje), FALSE);
  command_set_status(game_get_last_command(game), aux);
  free(aux);
  return;
}
void game_callback_open(Game *game){
  char *toks, *aux;
  char link[WORD_SIZE], object[WORD_SIZE], aux_str[WORD_SIZE];
  int i=0;
  Id id_object, id_link, id_open;
  if(!game){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[OPEN], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  i++;
  if(!(strcpy(aux_str, game_get_last_argument(game)))){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[OPEN], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }

  if((!(toks=strtok(aux_str, " \n"))) || toks[0]=='\0' || toks[0]==' '){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[OPEN], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  i++;
  strcpy(link, toks);
  if((!(toks=strtok(NULL, " \n"))) || toks[0]=='\0' || toks[0]==' ' || strcmp(toks, "with")!=0){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[OPEN], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  i++;
  if((!(toks=strtok(NULL, " \n"))) || toks[0]=='\0' || toks[0]==' '){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[OPEN], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  strcpy(object, toks);
  i++;
  if((id_object=game_get_object_id_at_name(game, object))==-1){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[OPEN], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  i++;
  if(inventory_is_object(player_get_inventory(game_get_player(game)), id_object)==FALSE){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[OPEN], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;   
  }
  i++;
  if((id_link=game_get_link_id_at_name(game, link))==-1){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[OPEN], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  i++;
  if(space_get_down(game_get_space(game, player_get_location(game_get_player(game))))!=id_link && space_get_up(game_get_space(game, player_get_location(game_get_player(game))))!=id_link && space_get_east(game_get_space(game, player_get_location(game_get_player(game))))!=id_link && space_get_west(game_get_space(game, player_get_location(game_get_player(game))))!=id_link && space_get_north(game_get_space(game, player_get_location(game_get_player(game))))!=id_link && space_get_south(game_get_space(game, player_get_location(game_get_player(game))))!=id_link){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[OPEN], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;     
  }
  i++;
  if(link_is_open(game_get_link_at_id(game, id_link))==TRUE){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[OPEN], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;   
  }
  i++;  
  id_open=object_get_open(game_get_object_at_id(game, id_object));
  if(id_open!=id_link){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[OPEN], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  link_set_open(game_get_link_at_id(game, id_link), 0);
  aux=CmdAnswer_get_random_ok(game->CmdAnswer[OPEN]);
  command_set_status(game_get_last_command(game), aux);
  free(aux);
  return;
}

void game_callback_save(Game *game){
  STATUS st;
  char *aux;
  int i=0;
  if(!(game_get_last_argument(game))){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[SAVE], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  st=game_managment_save(game, game_get_last_argument(game));
  i++;
  if(st==ERROR){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[SAVE], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;       
  }   
  aux=CmdAnswer_get_random_ok(game->CmdAnswer[SAVE]);
  command_set_status(game_get_last_command(game), aux);
  free(aux);
  return;  
}

void game_callback_load(Game *game){
  STATUS st;
  int i=0;
  char *aux;
  if(!(game_get_last_argument(game))){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[LOAD], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;       
  }
  st=game_managment_load(game, game_get_last_argument(game));
  i++;
  if(st==ERROR){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[LOAD], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;     
  }   
  aux=CmdAnswer_get_random_ok(game->CmdAnswer[LOAD]);
  command_set_status(game_get_last_command(game), aux);
  free(aux);
  return;  
}

void game_callback_talk(Game *game){
  int i=0, j;
  char *aux, *aux2;;
  char *toks, st[WORD_SIZE]= "";
  char aux_str[WORD_SIZE]="";
  char initial;
  char *name;
  Npc *npc=NULL;
  if(!game){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TALK], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  i++;
  if(!strcpy(aux_str, game_get_last_argument(game))){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TALK], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  if((!(toks=strtok(aux_str, " \n"))) || toks[0]=='\0' || toks[0]==' '){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TALK], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  i++;
  if(strcmp(toks, "with")!=0){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TALK], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return; 
  }
  i++;
  if((!(toks=strtok(NULL, "\n"))) || toks[0]=='\0' || toks[0]==' '){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TALK], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  if(strlen(toks)==1){ /*You can use just the initial*/
    for(j=0; game->npc[j]; j++){
      initial=npc_get_initial(game->npc[j]);
      if(initial==*toks){
        npc=game->npc[j];
        break;
      }
    }
  }
  else{ /*or you can use the full name*/
    for(j=0; game->npc[j]; j++){
      name=npc_get_name(game->npc[j]);
      if(strcmp(name, toks)==0){
        npc=game->npc[j];
        break;
      }
    }
  }
  if(!npc){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TALK], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  i++;
  if(npc_get_position(npc)!=player_get_location(game_get_player(game))){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[TALK], i);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  aux2=npc_get_random_dialogue(npc);
  sprintf(st, "OK, ");
  strcat(st, aux2);
  command_set_status(game_get_last_command(game), st);
  free(aux2);
  return;
}

void game_callback_accuse(Game *game){
  int n=0, j;
  char *aux, *guilty;
  if(!game){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[ACCUSE], n);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  n++;
  if(!(guilty=game_get_last_argument(game))){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[ACCUSE], n);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  n++;
  for(j=0; game->npc[j]; j++){
    if(strcmp(npc_get_name(game->npc[j]), guilty)==0){
      break;
    }
  }
  if(!game->npc[j]){
    aux=CmdAnswer_get_random_error(game->CmdAnswer[ACCUSE], n);
    command_set_status(game_get_last_command(game), aux);
    free(aux);
    return;
  }
  aux=CmdAnswer_get_random_ok(game->CmdAnswer[ACCUSE]);
  command_set_status(game_get_last_command(game), aux);
  free(aux);
  return;
}

void game_callback_next(Game *game){
  command_set_argument(game_get_last_command(game), "s"); /*the next of the previous iteration is equivalent to moving south*/
  game_callback_move(game);
  command_set_argument(game_get_last_command(game), "");
  return;
}

void game_callback_back(Game *game){
  command_set_argument(game_get_last_command(game), "n"); /*the back of the previous iteration is equivalent to moving north*/
  game_callback_move(game);
  command_set_argument(game_get_last_command(game), "");
  return;  
}

void game_callback_right(Game *game){
  command_set_argument(game_get_last_command(game), "e"); /*the right of the previous iteration is equivalent to moving east*/
  game_callback_move(game);
  command_set_argument(game_get_last_command(game), "");
  return;  
}

void game_callback_left(Game *game){
  command_set_argument(game_get_last_command(game), "w"); /*the left of the previous iteration is equivalent to moving west*/
  game_callback_move(game);
  command_set_argument(game_get_last_command(game), "");
  return;  
}

