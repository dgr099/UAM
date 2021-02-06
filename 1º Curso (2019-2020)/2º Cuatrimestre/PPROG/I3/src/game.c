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
#include "../include/game_reader.h"
#include "../include/player.h"
#include "../include/object.h"
#include "../include/inventory.h"
#include "../include/link.h"
/*! \def N_CALLBACK
    \brief A macro that stores the number of callbacks
   
    Details.
*/
#define N_CALLBACK 11
/*! \def gp
    \brief A macro that stores the number of chars used on graphic description
   
    Details.
*/
#define gp 16
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
  Dice *dice;                   /*!< the dice of the game */
};
/**
 * Private function
 */
/**
* @brief function to get object id at their name
** game_get_object_id_at_name
*
* @date 06-03-2019
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @param name the name of the object
* @return the id of the object
*/
Id game_get_object_id_at_name(Game* game, char *name);
/**
* @brief function to get object at their name
** game_get_object_at_id
*
* @date 06-03-2019
* @author David Teófilo Garitagoitia Romero
* @param game Pointer to the game structure
* @param id the id of the object
* @return the object with taht id
*/
Object* game_get_object_at_id(Game* game, Id id);
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
void game_callback_right(Game *game);

static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_exit,
    game_callback_take,
    game_callback_drop,
    game_callback_roll,
    game_callback_move,
    game_callback_inspect,
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
  if (game_reader_load_spaces(game, filename) == ERROR || game_reader_load_objects(game, filename) == ERROR || game_reader_load_player(game, filename) == ERROR || game_reader_load_links(game, filename) == ERROR){ /*it's checked if there is an error*/
    return NULL;
  }
  if(!game_get_space(game, player_get_location(game_get_player(game))))
    return NULL;
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
  if (i > MAX_OBJECTS)
  { /*if i more than MAX_SPACES is an Error*/
    return ERROR;
  }
  game->objects[i] = object;
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
  return OK;
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
  int i=0, j, z;
  const char* aux=NULL;
  if(!space)
    return;
  names[0]='\0';
  for(i=0; i!=space_get_num(space); i++){
    aux=game_get_object_name_at_id(game, set_get_id_at_position(space_get_objects(space), i));
    if(aux!=NULL){
    strcat(names, aux);      
    }
    strcat(names, " ");
  }
  for(j=strlen(names); j<gp; j++){
    names[j]=' ';
  }
  z=strlen(names);
  if(z>gp){
    for(i=gp-3; i!=gp-6; i--)
      names[i]='.';
    names[gp-1]=' ';
    names[gp]='\0';
  }

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

void game_get_objects_location(Game* game, char *names){
  int i, j;
  names[0]='\0';
  char z[3];
  for(i=0; game->objects[i]!=NULL && i<MAX_OBJECTS; i++){
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

Dice* game_get_dice(Game *game){
  if(!game){
    return NULL;
  }
  return game->dice;  
}

BOOL game_is_over(Game *game)
{
  return FALSE;
}

/**
   Callbacks implementation for each action 
*/

void game_callback_unknown(Game *game)
{
  command_set_status(game_get_last_command(game), "OK, unknown command");
}

void game_callback_exit(Game *game)
{
  command_set_status(game_get_last_command(game), "OK, leaving the game");
}

void game_callback_take(Game *game)
{
  Id object;
  char* object_name;
  if(!game){
    command_set_status(game_get_last_command(game), "ERROR, game==NULL");    
  }
  object=game_get_object_id_at_name(game, command_get_argument(game->last_cmd));
  object_name=game_get_last_argument(game);
  if(!object_name|| object_name[0]=='\0'){
    command_set_status(game_get_last_command(game), "ERROR, missing the objet name");
  }
  else if(object==-1){
    command_set_status(game_get_last_command(game), "ERROR, the object doesn't exist");
  }
  else if(space_get_num(game_get_space(game, player_get_location(game->player)))<=0 || space_is_object(game_get_space(game, player_get_location(game->player)), object)==FALSE){
    command_set_status(game_get_last_command(game), "ERROR, the object is not in this space");
  }
  else if(inventory_is_full(player_get_inventory(game_get_player(game)))==TRUE){
    command_set_status(game_get_last_command(game), "ERROR, the backpack is full");
  }
  else{
    player_add_object(game->player, game_get_object_at_id(game, object));
    space_dell_object(game_get_space(game, player_get_location(game->player)), game_get_object_id_at_name(game, command_get_argument(game->last_cmd)));
    command_set_status(game->last_cmd, "OK, taking the object");
  }
  return;
}

void game_callback_drop(Game *game)
{
  Id object;
  char *object_name;
  if(!game){
  command_set_status(game_get_last_command(game), "ERROR, game==NULL");
    return;
  }
  object=game_get_object_id_at_name(game, command_get_argument(game->last_cmd));
  object_name=game_get_last_argument(game);
  if(!object_name|| object_name[0]=='\0'){
    command_set_status(game_get_last_command(game), "ERROR, missing the objet name");
  }

  else if(inventory_is_object(player_get_inventory(game->player), object) == FALSE || inventory_is_emty(player_get_inventory(game_get_player(game)))==TRUE){
    command_set_status(game_get_last_command(game), "ERROR, you can't throw an object that you don't own");
    return;
  }
  
  else if(space_get_num(game_get_space(game, player_get_location(game->player)))>4){
    command_set_status(game_get_last_command(game), "ERROR, maximum number of objects in the space reached");
    return;
  }
  
  else{
    space_add_object(game_get_space(game, player_get_location(game->player)), game_get_object_id_at_name(game, command_get_argument(game->last_cmd)));
    player_dell_object(game->player, game_get_object_at_id(game, object));
    command_set_status(game->last_cmd, "OK, dropping the object");
  }
  return;
}

void game_callback_roll(Game *game){
  if(!game || !game->dice){
    command_set_status(game->last_cmd, "ERROR, no game or dice");
    return;
  }
  dice_roll(game->dice);
  command_set_status(game->last_cmd, "OK, rolling the dice");
  return;
}

void game_callback_move(Game *game){
  Id next_id = NO_ID;
  Id space_id = NO_ID;
  char* argument;
  if(!game){
    command_set_status(game_get_last_command(game), "ERROR, no game");
    return;
  }
  space_id = player_get_location(game->player);
  argument=game_get_last_argument(game);
  if(!argument || argument[0]=='\0'){
    command_set_status(game_get_last_command(game), "ERROR, need to specify the direction");
    return;
  }
  if( !strcmp(argument, "south") || !strcmp(argument, "s")){  
    if((next_id=game_get_south(game, game_get_space(game, space_id)))==NO_ID){
      command_set_status(game_get_last_command(game), "ERROR, no south space");
      return;
    }
    if(link_is_open(game_get_link_at_id(game, space_get_south(game_get_space(game, space_id))))==FALSE){
      command_set_status(game_get_last_command(game), "ERROR, the link is closed");
      return;      
    }
  }

  else if(!strcmp(argument, "north") || !strcmp(argument, "n")){
    if((next_id=game_get_north(game, game_get_space(game, space_id)))==NO_ID){
      command_set_status(game_get_last_command(game), "ERROR, no north id");
      return;
    }
    if(link_is_open(game_get_link_at_id(game, space_get_north(game_get_space(game, space_id))))==FALSE){
      command_set_status(game_get_last_command(game), "ERROR, the link is closed");
      return;      
    }    
  }

  else if(!strcmp(argument, "east") || !strcmp(argument, "e")){
    if((next_id=game_get_east(game, game_get_space(game, space_id)))==NO_ID){
      command_set_status(game_get_last_command(game), "ERROR, no east space");
      return;
    }
    if(link_is_open(game_get_link_at_id(game, space_get_east(game_get_space(game, space_id))))==FALSE){
      command_set_status(game_get_last_command(game), "ERROR, the link is closed");
      return;      
    }    
  }

  else if(!strcmp(argument, "west") || !strcmp(argument, "w")){
    if((next_id=game_get_west(game, game_get_space(game, space_id)))==NO_ID){
      command_set_status(game_get_last_command(game), "ERROR, no west space");
      return;
    }
    if(link_is_open(game_get_link_at_id(game, space_get_west(game_get_space(game, space_id))))==FALSE){
      command_set_status(game_get_last_command(game), "ERROR, the link is closed");
      return;      
    }    
  }
  else{
    command_set_status(game_get_last_command(game), "ERROR, position change problems");
    return;
  }
  player_set_location(game_get_player(game), next_id);
  command_set_status(game_get_last_command(game), "OK, moving position");
}

void game_callback_inspect(Game *game){
  char* object_name;
  const char* description;
  char status[WORD_SIZE];
  Id id; 
  if(!game){
    command_set_status(game_get_last_command(game), "ERROR, no game");
    return;
  }
  object_name=game_get_last_argument(game);
  if(!object_name|| object_name[0]=='\0'){
    command_set_status(game_get_last_command(game), "ERROR, missing the second argument");
    return;
  }
  if(!strcmp(object_name, "s")|| !strcmp(object_name, "space")){
    description=space_get_description(game_get_space(game, player_get_location(game_get_player(game))));
    if(!description || description[0]=='\0' || description[0]==' '){
    command_set_status(game_get_last_command(game), "ERROR, The space has no description");
    return;
    }
    goto status;
  }
  else if((id=game_get_object_id_at_name(game, object_name))==-1){
    command_set_status(game_get_last_command(game), "ERROR, the object doesn't exist");
    return;
  }
  else if(inventory_is_object(player_get_inventory(game_get_player(game)), id)==FALSE && space_is_object(game_get_space(game, player_get_location(game_get_player(game))), id)==FALSE){
    command_set_status(game_get_last_command(game), "ERROR, Object not found in space or inventory");
    return;
  }
  description=object_get_description(game_get_object_at_id(game, id));
  if(!description || description[0]=='\0' || description[0]==' '){
    command_set_status(game_get_last_command(game), "ERROR, The object has no description");
    return;
  }
  status:
  strcpy(status, "OK, ");
  strcat(status, description);
  command_set_status(game_get_last_command(game), status);
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
  command_set_argument(game_get_last_command(game), "e"); /*the back of the previous iteration is equivalent to moving north*/
  game_callback_move(game);
  command_set_argument(game_get_last_command(game), "");
  return;  
}

void game_callback_left(Game *game){
  command_set_argument(game_get_last_command(game), "w"); /*the back of the previous iteration is equivalent to moving north*/
  game_callback_move(game);
  command_set_argument(game_get_last_command(game), "");
  return;  
}

