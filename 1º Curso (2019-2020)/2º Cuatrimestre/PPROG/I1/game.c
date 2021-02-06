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
#include "types.h"
#include "game_reader.h"
#include "player.h"
#include "object.h"
#include "space.h"
/*! \def N_CALLBACK
    \brief A macro that stores the number of callbacks
   
    Details.
*/
#define N_CALLBACK 6

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

static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_exit,
    game_callback_next,
    game_callback_back,
    game_callback_take,
    game_callback_drop};

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
Id game_get_space_id_at(Game *game, int position);

STATUS game_create(Game *game)
{
  int i;
  game->object = object_create(0);
  if (!game->object)
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
  if (player_set_location(game->player, NO_ID) == ERROR)
  { /*it's checked if there is an error*/
    return ERROR;
  }
  game->last_cmd = NO_CMD;
  return OK;
}

STATUS game_create_from_file(Game *game, char *filename)
{
  /*First check if there is an error, if not then set the location of the player and set the object*/
  if (game_create(game) == ERROR) /*it's checked if there is an error*/
    return ERROR;
  if (game_reader_load_spaces(game, filename) == ERROR) /*it's checked if there is an error*/
    return ERROR;
  /*call the functions*/

  player_set_location(game->player, game_get_space_id_at(game, 0));
  space_set_object(game_get_space(game, 1), object_get_id(game->object));
  return OK;
}

Id game_get_object_location(Game *game, Id object)
{
  int i;
  for (i = 0; game->spaces[i] != NULL; i++)
  { /*check all the spaces */
    if (space_get_object(game->spaces[i]) == object_get_id(game->object))
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
  object_destroy(game->object);
  for (i = 0; game->spaces[i] != NULL; i++)
  { /*free the space one for one*/
    space_destroy(game->spaces[i]);
  }
  return OK;
}

STATUS game_update(Game *game, T_Command cmd)
{
  /*match the previous command with the current one, updating the previous one*/
  game->last_cmd = cmd;
  (*game_callback_fn_list[cmd])(game);
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

T_Command game_get_last_command(Game *game)
{
  return game->last_cmd;
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
  printf("=> Object location: %d\n", (int)game_get_object_location(game, object_get_id(game->object)));
  printf("=> Player location: %d\n", (int)player_get_location(game->player));
  printf("prompt:> ");
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
}

void game_callback_exit(Game *game)
{
}

void game_callback_take(Game *game)
{
  if (game_get_object_location(game, object_get_id(game->object)) == player_get_location(game->player) && player_get_object(game->player) == NO_ID)
  {
    player_set_object(game->player, object_get_id(game->object));
    space_set_object(game_get_space(game, game_get_object_location(game, object_get_id(game->object))), NO_ID);
  }
}

void game_callback_drop(Game *game)
{
  if (space_get_object(game_get_space(game, player_get_location(game->player))) == NO_ID && player_get_object(game->player) != NO_ID)
  {
    space_set_object(game_get_space(game, player_get_location(game->player)), player_get_object(game->player));
    player_set_object(game->player, NO_ID);
  }
}

void game_callback_next(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  space_id = player_get_location(game->player);
  if (space_id == NO_ID)
  {
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
      }
      return;
    }
  }
}

void game_callback_back(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  space_id = player_get_location(game->player);
  if (NO_ID == space_id)
  {
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
      }
      return;
    }
  }
}
