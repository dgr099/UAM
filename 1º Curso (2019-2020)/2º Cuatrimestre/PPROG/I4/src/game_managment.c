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
#include "../include/game_managment.h"
#include "../include/object.h"
#include "../include/space.h"
#include "../include/player.h"
#include "../include/link.h"
#include "../include/npc.h"

#define WORD_SIZE 1000
STATUS game_managment_load_CmdAnswers(Game *game, char *filename){
  FILE *file = NULL;
  char line[WORD_SIZE*2] = "", *toks=NULL, ans_error[WORD_SIZE], ans_ok[WORD_SIZE];
  int n=0, n2=0, i, j, h=0, d=0;
  STATUS st=OK;
  CmdAnswer *ca; 
  if(!filename){
    return ERROR;
  }
  if(!(file=fopen(filename, "r")))
    return ERROR;
  while (fgets(line, WORD_SIZE*2, file) && st==OK){
    if(strncmp("#ca:", line, 4) == 0){
      toks = strtok(line + 4, "|");
      if(!(ca=CmdAnswer_init())){
        return ERROR;
      }
      i = atol(toks);
      for(j=0; j!=i && st==OK; j++, h++){
        toks=strtok(NULL, "|");
        n=atol(toks);
        if(n>n2){
          st=CmdAnswer_add_new_error(ca);
        }
        toks=strtok(NULL, "|");
        strcpy(ans_error, toks);
        st=CmdAnswer_add_error_at(ca, ans_error, n);
        n2=n;
      }
      toks=strtok(NULL, "|");
      i = atol(toks);
      for(j=0; j!=i && st==OK; d++,j++){
        toks=strtok(NULL, "|");
        strcpy(ans_ok, toks);
        st=CmdAnswer_add_ok(ca, ans_ok);
      }
      st=game_add_cmda(game, ca);
    }
  }
  fclose(file);
  return st;
  
}

STATUS game_managment_load_spaces(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char description1[WORD_SIZE] = "";
  char description2[WORD_SIZE] = "";
  char *toks = NULL;
  char string1[NUM_CHARACTS +1];
  char string2[NUM_CHARACTS +1];
  char string3[NUM_CHARACTS +1];
  int position1=0,position2=0;
  BOOL ilumination;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID, up = NO_ID, down = NO_ID;
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
      up = atol(toks);
      toks = strtok(NULL, "|");
      down = atol(toks);
      toks = strtok(NULL, "|");
      ilumination = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(string1,toks);
      toks = strtok(NULL, "|");
      strcpy(string2,toks);
      toks = strtok(NULL, "|");
      strcpy(string3,toks);
      toks = strtok(NULL, "|");
      strcpy(description1,toks);
      toks = strtok(NULL, "|");
      strcpy(description2,toks);


#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%ld|ld|%d|%s|%s|%s|%s|%s\n", id, name, north, east, south, west, up, down, ilumination, string1, string2, string3, description1, description2);
#endif
 space = space_create(id);
      
      if (space != NULL)

      { /*if there is no space then set it*/
        space_set_description1(space, description1);
        space_set_description2(space, description2);
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        space_set_up(space, up);
        space_set_down(space, down);
        space_set_ilumination(space, ilumination);
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

STATUS game_managment_load_objects(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, position = NO_ID, open=NO_ID, dependency=NO_ID, incompatible=NO_ID;
  BOOL movable, hidden, illuminate, turned;
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
      toks = strtok(NULL, "|");
      movable = atol(toks);
      toks = strtok(NULL, "|");
      hidden = atol(toks);
      toks = strtok(NULL, "|");
      open = atol(toks);
      toks = strtok(NULL, "|");
      illuminate = atol(toks);
      toks = strtok(NULL, "|");
      turned = atol(toks);
      toks = strtok(NULL, "|");
      dependency = atol(toks);
      toks = strtok(NULL, "|");
      incompatible = atol(toks);

#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%s|%d|%d|%d|%d|%d|%d|%d|\n", id, name, position, description, movable, hidden, open, illuminate, turned, dependency, incompatible);
#endif
      object = object_create(id);
      if (object != NULL)
      { /*if there is no space then set it*/
        object_set_name(object, name);
        object_set_description(object, description);
        object_set_movable(object, movable);
        object_set_hidden(object, hidden);
        object_set_open(object, open);
        object_set_illuminate(object, illuminate);
        object_turned(object, turned);
        object_set_dependency(object, dependency);
        object_set_incompatible(object, incompatible);
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

STATUS game_managment_load_npc(Game *game, char *filename){
  FILE *file=NULL;
  Id id;
  int nd, j;
  BOOL guilty;
  char line[WORD_SIZE]= "";
  char name[WORD_SIZE] = "";
  char dialogue[MAX_DIALOGUES][WORD_SIZE];
  char description[WORD_SIZE]= "";
  char *toks=NULL;
  Id position;
  Npc *npc=NULL;
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
    if (strncmp("#n:", line, 3) == 0){
      toks=strtok(line+3, "|");
      id=atol(toks);
      toks=strtok(NULL, "|");
      strcpy(name, toks);
      toks=strtok(NULL, "|");
      position=atol(toks);
      toks=strtok(NULL, "|");
      nd=atol(toks);
      for(j=0; j!=nd; j++){
        toks=strtok(NULL, "|");
        strcpy(dialogue[j], toks);
      }
      toks=strtok(NULL, "|");
      guilty=atol(toks);
      toks=strtok(NULL, "|");
      strcpy(description, toks);
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld", id, name, position);
      for(j=0; j!=nd; j++)
        printf("%s|"dialogue[j]);
      printf("%ld|%s|", guilty, descprition)
#endif
      if(!(npc=npc_init(id)))
        return ERROR;
      if(npc_set_name(npc, name)==ERROR)
        return ERROR;
      for(j=0; j!=nd; j++){
        if(npc_add_dialogue(npc, dialogue[j])==ERROR)
          return ERROR;
      }
      if(npc_set_culpability(npc, guilty)==ERROR)
        return ERROR;
      if(npc_set_position(npc, position)==ERROR){
        return ERROR;
      }
      if(npc_set_description(npc, description)==ERROR){
        return ERROR;
      }
      game_add_npc(game, npc);
    }
      
  }
  fclose(file);
  return OK;
}

STATUS game_managment_load_player(Game *game, char *filename)
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

STATUS game_managment_load_links(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Link* link;
  Id id = NO_ID, origin = NO_ID, destination = NO_ID, open = NO_ID;
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
      origin = atol(toks);
      toks = strtok(NULL, "|");
      destination = atol(toks);
      toks = strtok(NULL, "|");
      open = atol(toks);
#ifdef DEBUG
      printf("Leido: %ld|%s|%d|%d|%d|\n", id, name, origin, destination, open);
#endif
      link=link_create(id);
      link_set_name(link, name);
      link_set_id1(link, origin);
      link_set_id2(link, destination);
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

STATUS game_managment_save(Game *game, char *filename){
  FILE *f;
  int i, j, z, h;
  BOOL x;
  if(!game || !filename){
    return ERROR;
  }
  if(!(f=fopen(filename, "w"))){
    return ERROR;
  }
  /*stores the important information of the spaces*/
  for(i=0, j=game_get_num_spaces(game); i!=j; i++){
    z=set_get_num(space_get_objects(game_get_space_at_position(game, i)));
    fprintf(f, "#s:%d|", z);
    for(h=0; h!=z; h++){
      /*stores the set of the space*/
      fprintf(f, "%ld|", set_get_id_at_position(space_get_objects(game_get_space_at_position(game, i)), h));
    }
    fprintf(f, "\n");
  }
  /*stores the important information of the links*/
  for(i=0, j=game_get_num_links(game); i!=j; i++){
    x=link_is_open(game_get_link_at_postion(game, i));
    fprintf(f, "#l:%d|", x);
    fprintf(f, "\n");
  }
  /*stores the important information of the objects*/
  for(i=0, j=game_get_num_objects(game); i!=j; i++){
    x=object_get_turned(game_get_object_at_position(game, i));
    fprintf(f, "#o:%d|", x);
    fprintf(f, "\n");
  }
  /*stores the important information of the player*/
  fprintf(f, "#p:%ld|", player_get_location(game_get_player(game)));
  /*stores the objects of the inventory*/
  j=set_get_num(inventory_get_inside(player_get_inventory(game_get_player(game))));
  fprintf(f, "%d|",j);
  for(i=0; i!=j; i++){
    fprintf(f, "%ld|", set_get_id_at_position(inventory_get_inside(player_get_inventory(game_get_player(game))), i));
  }
  fclose(f);
  return OK;
}

STATUS game_managment_load(Game *game, char *filename){
  int i, h, s=0, l=0, o=0, j;
  Id id_aux;
  char line[WORD_SIZE] = "", *toks;
  Set *set;
  BOOL x;
  FILE *f;
  if(!game || !filename){
    return ERROR;
  }
  if(!(f=fopen(filename, "r"))){
    return ERROR;
  }
  while (fgets(line, WORD_SIZE, f)){
    if (strncmp("#s:", line, 3) == 0){
      toks = strtok(line + 3, "|");
      h=atol(toks);
      if(!(set=set_create())){
        return ERROR;
      }
      for(i=0; i!=h; i++){
        toks = strtok(NULL, "|");
        j=atol(toks);
        set_add(set, j);
      }
      set_update(space_get_objects(game_get_space_at_position(game, s)), set);
      set_destroy(set);
      s++;
    }
    else if (strncmp("#l:", line, 3) == 0){
      toks = strtok(line + 3, "|");
      x = atol(toks);
      if(x==0){
        x=1;
      }
      else
        x=0;
      link_set_open(game_get_link_at_postion(game, l), x);
      l++;
    }
    else if (strncmp("#o:", line, 3) == 0){
      toks = strtok(line + 3, "|");
      x = atol(toks);
      object_turned(game_get_object_at_position(game, o), x);
      o++;
    }
    else if(strncmp("#p:", line, 3) == 0){
      toks = strtok(line + 3, "|");
      h = atol(toks);
      player_set_location(game_get_player(game), h);
      toks = strtok(NULL, "|");
      h = atol(toks);
      if(h>inventory_get_max(player_get_inventory(game_get_player(game)))){
        fclose(f);
        return ERROR;
      }
      if(!(set=set_create())){
        fclose(f);
        return ERROR;
      }
      for(i=0; i!=h; i++){
        toks = strtok(NULL, "|");
        id_aux = atol(toks);
        set_add(set, id_aux);
      }
      set_update(inventory_get_inside(player_get_inventory(game_get_player(game))), set);
      set_destroy(set);
    }
  }
  fclose(f);
  return OK;
}


STATUS game_managment_load_tutorial(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char tutorial[WORD_SIZE]="";
  char *tok=NULL;
  STATUS st=OK;
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
    if (strncmp("#t:", line, 3) == 0)
    { /*if they are equal then replace the empty gaps with bars*/
      tok = strtok(line + 3, "|");

#ifdef DEBUG
      printf("Leido: %s\n", tutorial);
#endif  
      strcpy(tutorial, tok);
      break;
    }
    
  }
  st=game_add_tutorial(game, tutorial);
  fclose(file);
  return st;
}

STATUS game_managment_load_ending(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char *tok = NULL;
  char end[WORD_SIZE] = "";
  STATUS st=OK; 
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
    if (strncmp("#e:", line, 3) == 0)
    { /*if they are equal then replace the empty gaps with bars*/
      tok = strtok(line + 3, "|");
      strcpy(end, tok);
      break;
#ifdef DEBUG
      printf("Leido: %s\n", end);
#endif
    }
    
  }
  st=game_add_end(game, end);
  fclose(file);
  return st;
}
