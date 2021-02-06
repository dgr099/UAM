/** 
 * @brief display the game on the screen
 * 
 * @file game.c
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/screen.h"
#include "../include/graphic_engine.h"
#include "../include/command.h"
#include "../include/player.h"
#include "../include/object.h"
#include "../include/dice.h"
#include "../include/game_reader.h"
#include "../include/set.h"
/*! \def MAX_STR
    \brief A macro that stores the maximum number of strings
   
    Details.
*/
#define MAX_STR 255
/*! \def OBJECT_MAX
    \brief A macro that stores the maximum number of chars that represent objects
   
    Details.
*/
#define OBJECT_MAX 100
/**
* @brief The graic engine structure
*
* It stores information of the graphic engine
*/
struct _Graphic_engine
{
  Area *map; /*!< Area of map*/
  Area *descript; /*!< Area of descript*/
  Area *banner; /*!< Area of banner*/
  Area *help; /*!< Area of help*/
  Area *feedback; /*!< Area of feedback*/
};

Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;
  if (ge)
    return ge;
  screen_init();
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if(!ge){
    return NULL;
  }
  ge->map = screen_area_init(1, 1, 48, 17); /*the map*/
  ge->descript = screen_area_init(50, 1, 29, 17); /*object location, player object, las roll value*/
  ge->banner = screen_area_init(28, 19, 23, 1); /*banner (game of the goose)*/
  ge->help = screen_area_init(1, 20, 78, 3); /*commands you can use*/
  ge->feedback = screen_area_init(1, 20+4, 78, 5);  /*feedback of the game*/
  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge)
{
  if (!ge)
    return;
  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);
  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game, FILE *file)
{
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_right = NO_ID, id_left = NO_ID; 
  int i, z; /*auxiliar ints*/
  Space *space_act=NULL;
  char obje[OBJECT_MAX]=" ";
  char str[MAX_STR]=" ";
  int position1=0,position2;
  char string1[NUM_CHARACTS +1]=" ";
  char string2[NUM_CHARACTS +1]=" ";
  char string3[NUM_CHARACTS +1]=" ";
  char string_left[NUM_CHARACTS + 1]=" ";
  char string_aux[NUM_CHARACTS + 1]=" ";
  char string_right[NUM_CHARACTS + 1]=" ";
  char argument[CMD_LENGHT];
  extern char *cmd_to_str[N_CMD][N_CMDT];
  char *toks;
  /* Paint the in the map area */
  screen_area_clear(ge->map);



  if ((id_act = player_get_location(game_get_player(game))) != NO_ID)
  {

    space_act = game_get_space(game, id_act);
    strcmp(argument,game_get_last_argument(game));
    id_back = game_get_north(game, space_act);
    id_next = game_get_south(game, space_act);
    
    if (id_back != NO_ID)
    {
      position1++;
      for(position2=0;position2<NUM_CHARACTS;position2++){
        if((string2[position2]=space_get_gdesc_at(game_get_space(game, id_back),position1,position2))==FALSE)
        return;
      }
      position1++;
      for(position2=0;position2<NUM_CHARACTS;position2++){
      if((string3[position2]=space_get_gdesc_at(game_get_space(game, id_back),position1,position2))==FALSE)
        return;
      }
      space_act=game_get_space(game, id_back);
      id_right = space_get_east(space_act);
      id_left = space_get_west(space_act);
      sprintf(str, "            | %s          |", string2);
      screen_area_puts(ge->map, str);
      
      for(i=0; i!=NUM_CHARACTS; i++){
        string_left[i]='\0';
        string_right[i]='\0';
      }

      if(id_right!=NO_ID){
        sprintf(string_right, "--> %ld", game_get_east(game, space_act));
      }
      if(id_left!=NO_ID){
        sprintf(string_aux, "%ld <--", game_get_west(game, space_act));
      }
      z=strlen(string_aux);
      for(i=0; i!=NUM_CHARACTS-z; i++){
        string_left[i]=' ';
      }
      strcat(string_left, string_aux);

      sprintf(str, "     %s| %s          |%s",string_left, string3, string_right);
      screen_area_puts(ge->map, str);
      game_get_objects_name_at_space(game_get_space(game, id_back), game, obje);

      for(i=0; i!=NUM_CHARACTS; i++){
        string_left[i]='\0';
        string_right[i]='\0';
      }
      if(id_right!=NO_ID){
        sprintf(string_right, "%ld", id_right);
      }
      string_aux[0]='\0';
      if(id_left!=NO_ID){
        sprintf(string_aux, "%ld", id_left);
        }

      z=strlen(string_aux);
      for(i=0; i!=NUM_CHARACTS-z; i++){
        string_left[i]=' ';
      }
      strcat(string_left, string_aux);

      sprintf(str, "     %s|%s%2d|%s", string_left, obje,(int)id_back, string_right);
      screen_area_puts(ge->map, str);
      sprintf(str, "            +------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    ^ %ld", space_get_north(game_get_space(game, id_act)));
      screen_area_puts(ge->map, str);
    }
    
    if (id_act != NO_ID)
    {
      position1=0;
      for(position2=0;position2<NUM_CHARACTS;position2++){
        if((string1[position2]=space_get_gdesc_at(game_get_space(game, id_act),position1,position2))==FALSE)
          return;
    }

      position1++;

      for(position2=0;position2<NUM_CHARACTS;position2++){
        if((string2[position2]=space_get_gdesc_at(game_get_space(game, id_act),position1,position2))==FALSE)
        return;
      }

      position1++;
      for(position2=0;position2<NUM_CHARACTS;position2++){
        if((string3[position2]=space_get_gdesc_at(game_get_space(game, id_act),position1,position2))==FALSE)
        return;
      }
      space_act = game_get_space(game, id_act);
      id_right = space_get_east(space_act);
      id_left = space_get_west(space_act);
      for(i=0; i!=NUM_CHARACTS; i++){
        string_left[i]='\0';
        string_right[i]='\0';
      }      
      if(id_right!=NO_ID){
        sprintf(string_right, "%ld", id_right);
      }
      string_aux[0]='\0';
      if(id_left!=NO_ID){
        sprintf(string_aux, "%ld", id_left);
        }

      z=strlen(string_aux);
      for(i=0; i!=NUM_CHARACTS-z; i++){
        string_left[i]=' ';
      }
      strcat(string_left, string_aux);

      sprintf(str, "    %s +------------------+ %s", string_left, string_right);
      screen_area_puts(ge->map, str);

      for(i=0; i!=NUM_CHARACTS; i++){
        string_left[i]='\0';
        string_right[i]='\0';
      }
      if(id_right!=NO_ID){
        sprintf(string_right, "--> %ld", game_get_east(game, space_act));
      }
      if(id_left!=NO_ID){
        sprintf(string_aux, "%ld <--", game_get_west(game, space_act));
      }
      z=strlen(string_aux);
      for(i=0; i!=NUM_CHARACTS-z; i++){
        string_left[i]=' ';
      }
      strcat(string_left, string_aux);

      sprintf(str, "     %s| 8D             %2d|%s", string_left, (int)id_act, string_right);
      screen_area_puts(ge->map, str);
      sprintf(str, "            | %s          |",string1);
      screen_area_puts(ge->map, str);
      sprintf(str, "            | %s          |",string2);
      screen_area_puts(ge->map, str);
      sprintf(str, "            | %s          |",string3);
      screen_area_puts(ge->map, str);
      game_get_objects_name_at_space(game_get_space(game, id_act), game, obje);
      sprintf(str, "            |%s  |", obje);
      screen_area_puts(ge->map, str);
      sprintf(str, "            +------------------+");
      screen_area_puts(ge->map, str);
    }
   

    if (id_next != NO_ID)
    {

    position1=0;
    for(position2=0;position2<NUM_CHARACTS;position2++){
      if((string1[position2]=space_get_gdesc_at(game_get_space(game, id_next),position1,position2))==FALSE)
        return;
    }
    position1++;
    for(position2=0;position2<NUM_CHARACTS;position2++){
      if((string2[position2]=space_get_gdesc_at(game_get_space(game, id_next),position1,position2))==FALSE)
        return;
      }

      sprintf(str, "                    v %ld", space_get_south(game_get_space(game, id_act)));
      screen_area_puts(ge->map, str);
      
      space_act=game_get_space(game, id_next);
      id_right = space_get_east(space_act);
      id_left = space_get_west(space_act);

      for(i=0; i!=NUM_CHARACTS; i++){
        string_left[i]='\0';
        string_right[i]='\0';
      }      
      
      if(id_right!=NO_ID){
        sprintf(string_right, "%ld", id_right);
      }
      string_aux[0]='\0';
      if(id_left!=NO_ID){
        sprintf(string_aux, "%ld", id_left);
        }

      z=strlen(string_aux);
      for(i=0; i!=NUM_CHARACTS-z; i++){
        string_left[i]=' ';
      }
      strcat(string_left, string_aux);

      sprintf(str, "    %s +------------------+ %s", string_left, string_right);
      screen_area_puts(ge->map, str);
      game_get_objects_name_at_space(game_get_space(game, id_next), game, obje);

      for(i=0; i!=NUM_CHARACTS; i++){
        string_left[i]='\0';
        string_right[i]='\0';
      }
      if(id_right!=NO_ID){
        sprintf(string_right, "--> %ld", game_get_east(game, space_act));
      }
      if(id_left!=NO_ID){
        sprintf(string_aux, "%ld <--", game_get_west(game, space_act));
      }
      z=strlen(string_aux);
      for(i=0; i!=NUM_CHARACTS-z; i++){
        string_left[i]=' ';
      }
      strcat(string_left, string_aux);

      sprintf(str, "     %s|%s%2d|%s", string_left, obje,(int)id_next, string_right);
      screen_area_puts(ge->map, str);
      sprintf(str, "            | %s          |",string1);
      screen_area_puts(ge->map, str);
      sprintf(str, "            | %s          |",string2);
      screen_area_puts(ge->map, str);
    }
  }
  /* Paint the in the description area */
  screen_area_clear(ge->descript);
  sprintf(str, "Objects location:  ");          
  screen_area_puts(ge->descript, str);
  game_get_objects_location(game, obje);
  sprintf(str, "%s", obje);          
  screen_area_puts(ge->descript, str);
  game_get_player_objects(game, obje);
  sprintf(str, "Player object: %s", obje);          
  screen_area_puts(ge->descript, str);
  sprintf(str, "Last dice value: %d", dice_get_last(game_get_dice(game)));          
  screen_area_puts(ge->descript, str);
  /* Paint the in the banner area */
  screen_area_puts(ge->banner, " The game of the Goose");
  /* Paint the in the help area */
  screen_area_clear(ge->help);
   sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
   sprintf(str, "     move or m, exit or e, take or t, drop or d, roll or rl, inspect or i");
  screen_area_puts(ge->help, str);
     sprintf(str, "     next or n, back or b, left or l, right or r");
  screen_area_puts(ge->help, str);
  /* Paint the in the feedback area */
   
  
  sprintf(str, " %s (%s): %s", cmd_to_str[game_get_last_principal_command(game) - NO_CMD][CMDL], cmd_to_str[game_get_last_principal_command(game) - NO_CMD][CMDS], command_get_status(game_get_last_command(game)));
  screen_area_puts(ge->feedback, str);
  if(file!=NULL && strcmp(cmd_to_str[game_get_last_principal_command(game) - NO_CMD][CMDL], "no command")!=0){
    if(strncmp(game_get_last_argument(game), "\0", 1)!=0)
      fprintf(file, "%s %s:", cmd_to_str[game_get_last_principal_command(game) - NO_CMD][CMDL], game_get_last_argument(game));
    else
      fprintf(file, "%s:", cmd_to_str[game_get_last_principal_command(game) - NO_CMD][CMDL]);
    toks=strtok(str, ":");
    toks=strtok(NULL, ",");
    fprintf(file, "%s\n", toks);  
  }
  /* Dump to the terminal */
  screen_paint();
  printf("prompt :> ");
}
