/** 
 * @brief add, load, and get spaces 
 * 
 * @file object.c
 * @author David Teófilo Garitagoitia Romero y José Manuel García Giráldez
 * @version 1.0 
 * @date 06-02-2019 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/game.h"
#include "../include/game_reader.h"
#include "../include/object.h"
#include "../include/space.h"
#include "../include/player.h"
#include "../include/link.h"
/*! \def WORD_SIZE
    \brief A macro that stores the word size.
   
    Details.
*/
#define WORD_SIZE 1000

STATUS game_reader_load_spaces(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  char *toks = NULL;
  char string1[NUM_CHARACTS +1];
char string2[NUM_CHARACTS +1];
char string3[NUM_CHARACTS +1];
  int position1=0,position2=0;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  STATUS status = OK;
  if (!filename)
  { /*check if there is an error with the filename*/
    return ERROR;
  }
  file = fopen(filename, "r");
  if (file == NULL)
  { /*check if there is an error while opening the file*/
    return ERROR;
  }
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#s:", line, 3) == 0)
    { /*if they are equal then replace the empty gaps with bars*/
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(string1,toks);
      toks = strtok(NULL, "|");
      strcpy(string2,toks);
      toks = strtok(NULL, "|");
      strcpy(string3,toks);
      toks = strtok(NULL, "|");
      strcpy(description,toks);


#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%s|%s|%s|%s\n", id, name, north, east, south, west,string1,string2,string3,description);
#endif
 space = space_create(id);
      
      if (space != NULL)

      { /*if there is no space then set it*/
        space_set_description(space, description);
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        game_add_space(game, space);
position1 = 0;
        for(position2=0;position2<NUM_CHARACTS;position2++){
          if(space_set_gdesc_at(space,position1,position2,string1[position2])==ERROR)
            return ERROR;
        }

      position1 = 1;
      
        for(position2=0;position2<NUM_CHARACTS;position2++){
          if(space_set_gdesc_at(space,position1,position2,string2[position2])==ERROR)
            return ERROR;
        }

      position1 = 2;
     
        for(position2=0;position2<NUM_CHARACTS;position2++){
          if(space_set_gdesc_at(space,position1,position2,string3[position2])==ERROR)
            return ERROR;
        }

      }
    }
  }
  if (ferror(file))
  {
    status = ERROR;
  }
  fclose(file);
  return status;
}

STATUS game_reader_load_objects(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, position = NO_ID;
  Object *object = NULL;
  STATUS status = OK;
  if (!filename)
  { /*check if there is an error with the filename*/
    return ERROR;
  }
  file = fopen(filename, "r");
  if (file == NULL)
  { /*check if there is an error while opening the file*/
    return ERROR;
  }
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#o:", line, 3) == 0)
    { /*if they are equal then replace the empty gaps with bars*/
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      position = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(description,toks);
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%s|\n", id, name, position, description);
#endif
      object = object_create(id);
      if (object != NULL)
      { /*if there is no space then set it*/
        object_set_name(object, name);
        object_set_description(object, description);
      }
      game_add_object(game, object);
      /*space_add_object(game_get_space(game, game_get_space_id_at(game, position)), id);*/
      space_add_object(game_get_space(game, position), id);
    }
    
  }
  if (ferror(file))
  {
    status = ERROR;
  }
  fclose(file);
  return status;
}

STATUS game_reader_load_player(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Player* player;
  Id id = NO_ID, position = NO_ID;
  int max;
  STATUS status = OK;
  if (!filename)
  { /*check if there is an error with the filename*/
    return ERROR;
  }
  file = fopen(filename, "r");
  if (file == NULL)
  { /*check if there is an error while opening the file*/
    return ERROR;
  }
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#p:", line, 3) == 0)
    { /*if they are equal then replace the empty gaps with bars*/
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      position = atol(toks);
      toks = strtok(NULL, "|");
      max = atol(toks);
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%d|\n", id, name, position, max);
#endif
      player=player_create(id, max);
      player_set_name(player, name);
      player_set_location(player, position);
      game_set_player(game, player);
    }
    
  }
  if (ferror(file))
  {
    status = ERROR;
  }
  fclose(file);
  return status;
}

STATUS game_reader_load_links(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Link* link;
  Id id = NO_ID, id1 = NO_ID, id2 = NO_ID, open = NO_ID;
  STATUS status = OK;
  if (!filename)
  { /*check if there is an error with the filename*/
    return ERROR;
  }
  file = fopen(filename, "r");
  if (file == NULL)
  { /*check if there is an error while opening the file*/
    return ERROR;
  }
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#l:", line, 3) == 0)
    { /*if they are equal then replace the empty gaps with bars*/
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      id1 = atol(toks);
      toks = strtok(NULL, "|");
      id2 = atol(toks);
      toks = strtok(NULL, "|");
      open = atol(toks);
#ifdef DEBUG
      printf("Leido: %ld|%s|%d|%d|%d|\n", id, name, id1, id2, open);
#endif
      link=link_create(id);
      link_set_name(link, name);
      link_set_id1(link, id1);
      link_set_id2(link, id2);
      link_set_open(link, open);
      game_add_link(game, link);
    }
    
  }
  if (ferror(file))
  {
    status = ERROR;
  }
  fclose(file);
  return status;
}


