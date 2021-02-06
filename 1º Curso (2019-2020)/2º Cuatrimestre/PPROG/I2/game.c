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
#include "game.h"
#include "space.h"
#include "game_reader.h"
#include "player.h"
#include "object.h"
/*! \def N_CALLBACK
    \brief A macro that stores the number of callbacks
   
    Details.
*/
#define N_CALLBACK 9
/*! \def gp
    \brief A macro that stores the number of chars used on graphic description
   
    Details.
*/
#define gp 16

/**
   Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game *game);

/**
   List of callbacks for each command in the game 
*/
void game_callback_unknown(Game *game);
void game_callback_exit(Game *game);
void game_callback_next(Game *game);
void game_callback_back(Game *game);
void game_callback_take(Game *game);
void game_callback_drop(Game *game);
void game_callback_roll(Game *game);
void game_callback_left(Game *game);
void game_callback_right(Game *game);

static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_exit,
    game_callback_next,
    game_callback_back,
    game_callback_take,
    game_callback_drop,
    game_callback_roll,
    game_callback_left,
    game_callback_right};

/**
   Private functions
*/

/**
* @brief get the ids from the game spaces
*
* game_get_space_id_at
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param game the game from which we will get the information
* @param position the position of the game space that we want
* @return the position
*/

STATUS game_create(Game *game)
{
  int i;
  game->dice=dice_create(0, 6, 1);
  if (!game->dice)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  game->player = player_create(0);
  if (!game->player)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  for (i = 0; i <= MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }
    for (i = 0; i <= MAX_OBJECTS; i++)
  {
    game->objects[i] = NULL;
  }
  game->last_cmd=command_init();
  return OK;
}

STATUS game_create_from_file(Game *game, char *filename)
{
  /*First check if there is an error, if not then set the location of the player and set the object*/
  if (game_create(game) == ERROR) /*it's checked if there is an error*/
    return ERROR;
  if (game_reader_load_spaces(game, filename) == ERROR || game_reader_load_objects(game, filename) == ERROR) /*it's checked if there is an error*/
    return ERROR;
  /*call the functions*/

  player_set_location(game->player, game_get_space_id_at(game, 0));
  /*space_add_object(game_get_space(game, 1), object_get_id(game->object));*/
  return OK;
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
  { /*free the space one for one*/
    object_destroy(game->objects[i]);
  }
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
  if (space == NULL)
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
  for(i=0; i!=MAX_OBJECTS && game->objects[i]; i++){
    name2=object_get_name(game->objects[i]);
    if(strcmp(name, name2)==0){
      return object_get_id(game->objects[i]);
    }
  }
  return -1;
}

const char* game_get_object_name_at_id(Game* game, Id id){
  int i=0;
  if(id==NO_ID || !game ){
    return " ";
  }
  for(i=0; i!=MAX_OBJECTS || game->objects[i]==NULL; i++){
    if(object_get_id(game->objects[i])==id){
      return object_get_name(game->objects[i]);
    }
  }
  return " ";
}

void game_get_objects_name_at_space(Space *space, Game *game, char *names){
  int i=0, j, z;
  if(!space)
    return;
  names[0]='\0';
  for(i=0; i!=space_get_num(space); i++){
    strcat(names, game_get_object_name_at_id(game, set_get_id_at_position(space_get_objects(space), i)));
    strcat(names, " ");
  }
  for(j=strlen(names); j<gp; j++){
    names[j]=' ';
  }
  z=strlen(names);
  if(z>gp){
    for(i=z-3; i!=z-5; i--)
      names[i]=' ';
    for(i=z-5; i!=z-8; i--){
      names[i]='.';
    }
    names[z-2]='\0';
  }
  /*return names;*/
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
  command_set_status(game_get_last_command(game), "OK");
}

void game_callback_exit(Game *game)
{
  command_set_status(game_get_last_command(game), "OK");
}

void game_callback_take(Game *game)
{
  Id object;
  command_set_status(game_get_last_command(game), "ERROR");
  if(strncmp(game_get_last_argument(game), "\0", 1)==0 || !game_get_last_argument(game)){
    return;
  }
  object=game_get_object_id_at_name(game, command_get_argument(game->last_cmd));
  if(object==-1 || !command_get_argument(game->last_cmd) || player_get_object(game->player)!=NO_ID || space_get_num(game_get_space(game, player_get_location(game->player)))<=0 || space_is_object(game_get_space(game, player_get_location(game->player)), object)==FALSE){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  player_set_object(game->player, game_get_object_id_at_name(game, command_get_argument(game->last_cmd)));
  space_dell_object(game_get_space(game, player_get_location(game->player)), game_get_object_id_at_name(game, command_get_argument(game->last_cmd)));
  command_set_status(game->last_cmd, "OK");
  return;
}

void game_callback_drop(Game *game)
{
  command_set_status(game_get_last_command(game), "ERROR");
  if(player_get_object(game->player)==NO_ID || space_get_num(game_get_space(game, player_get_location(game->player)))>4){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  space_add_object(game_get_space(game, player_get_location(game->player)), player_get_object(game->player));
  player_set_object(game->player, NO_ID);
  command_set_status(game->last_cmd, "OK");
  return;
}

void game_callback_roll(Game *game){
  command_set_status(game_get_last_command(game), "ERROR");
  if(!game){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  dice_roll(game->dice);
  command_set_status(game->last_cmd, "OK");
  return;
}

void game_callback_next(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  space_id = player_get_location(game->player);
  command_set_status(game_get_last_command(game), "ERROR");
  if (space_id == NO_ID)
  {
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID)
      {
        player_set_location(game->player, current_id);
        command_set_status(game->last_cmd, "OK");
      }
      if(strcmp(command_get_status(game_get_last_command(game)), "OK")!=0)
        command_set_status(game->last_cmd, "ERROR");
      return;
    }
  }
}

void game_callback_back(Game *game)
{
  int i = 0;
  command_set_status(game_get_last_command(game), "ERROR");
  command_set_status(game_get_last_command(game), "ERROR");
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  space_id = player_get_location(game->player);
  command_set_status(game_get_last_command(game), "ERROR");
  if (NO_ID == space_id)
  {
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID)
      {
        player_set_location(game->player, current_id);
        command_set_status(game->last_cmd, "OK");
      }
      if(strcmp(command_get_status(game_get_last_command(game)), "OK")!=0)
        command_set_status(game->last_cmd, "ERROR");
      return;
    }
  }
}

void game_callback_right(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  space_id = player_get_location(game->player);
  command_set_status(game_get_last_command(game), "ERROR");
  if (NO_ID == space_id)
  {
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_west(game->spaces[i]);
      if (current_id != NO_ID)
      {
        player_set_location(game->player, current_id);
        command_set_status(game->last_cmd, "OK");
      }
      if(strcmp(command_get_status(game_get_last_command(game)), "OK")!=0)
        command_set_status(game->last_cmd, "ERROR");
      return;
    }
  }
}

void game_callback_left(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  space_id = player_get_location(game->player);
  command_set_status(game_get_last_command(game), "ERROR");
  if (NO_ID == space_id)
  {
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_east(game->spaces[i]);
      if (current_id != NO_ID)
      {
        player_set_location(game->player, current_id);
        command_set_status(game->last_cmd, "OK");
      }
      if(strcmp(command_get_status(game_get_last_command(game)), "OK")!=0)
        command_set_status(game->last_cmd, "ERROR");
      return;
    }
  }
}
