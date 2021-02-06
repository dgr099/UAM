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
#include "../include/game_managment.h"
#include "../include/set.h"

#define MAX_STR 255
#define Object_MAX 100
#define MAX_CHAR_CHAT 42
#define MAX_CHAR_HELP 98
#define MAX_LINE_CHAT 16/2
#define MAX_LINE_HELP 4
#define MAX_CHAR_MAP 55
#define MAX_LINE_MAP 21
#define MAX_CHAR_DESCRIPT 42
#define MAX_LINE_DESCRIPT 24/2
#define MAX_CHAR_FEEDBACK 98
#define MAX_LINE_FEEDBACK 5
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
  Area *chat; /*!< Area of chat*/
};

Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;
  if (ge)
    return ge;
  screen_init();
  if(!(ge = (Graphic_engine *)malloc(sizeof(Graphic_engine)))){
    return NULL;
  }
  ge->map = screen_area_init(1, 1, MAX_CHAR_MAP, MAX_LINE_MAP); /*the map*/
  ge->descript = screen_area_init(MAX_CHAR_MAP+2, 1, MAX_CHAR_DESCRIPT, MAX_LINE_DESCRIPT); /*object location, player object, las roll value*/
  ge->chat = screen_area_init( MAX_CHAR_MAP+2, 2+MAX_LINE_DESCRIPT, MAX_CHAR_CHAT, MAX_LINE_CHAT);
  ge->banner = screen_area_init(38, 23, 24, 1); /*banner (game of the goose)*/
  ge->help = screen_area_init(1, 24, MAX_CHAR_HELP, MAX_LINE_HELP); /*commands you can use*/
  ge->feedback = screen_area_init(1, 29, MAX_CHAR_FEEDBACK, MAX_LINE_FEEDBACK);  /*feedback of the game*/
  return ge;
}
/**
* @brief adapt Adapt the text for its correct display
*
* graphic_engine_apat_text
*
* @date 6-05-2020
* @author: David Teófilo Garitagoitia Romero
* @param text The original text
* @param MAX_CHAR The maximum number of characters per line
* @param MAX_LINE The maximum number of lines, to avoid stealing space from other screens
*@return a new string with spaces to avoid errors in the display of words
*/
char*   graphic_engine_adapt_text(const char *text, int MAX_CHAR, int MAX_LINE){
  char *aux2=NULL, *tok=NULL, *aux1=NULL;
  int c=0, line=0, z, len, top;
  if(!text || MAX_CHAR<=0 || MAX_LINE<=0 ){
    return NULL;
  }
  top=strlen(text);
  if(!(aux2=(char*)calloc(MAX_LINE*MAX_CHAR+1, sizeof(char))))
    return NULL;
  if(!(aux1=(char*)calloc(MAX_LINE*MAX_CHAR+1, sizeof(char))))
    return NULL;
  strcpy(aux1, text);
  tok=strtok(aux1, " \n\t");

  for(len=0; len<top && line<MAX_LINE; ){
    /*printf("%s", aux2);*/
    for(c=0; c<MAX_CHAR; ){
      if(tok){
        if(strcmp(tok, "/")==0){
          tok=NULL;
          continue;
        }
        z=strlen(tok);
        if((z+1+c)<MAX_CHAR && tok){
          strcat(aux2, tok);
          strcat(aux2, " ");
          tok=NULL;
          c+=z+1;
          len+=z+1;
        }
        else{
          for(c=c; c<MAX_CHAR; c++){
            aux2[strlen(aux2)]=' ';
          }
          line++;
          continue;
        }
      }
      else{
        tok=strtok(NULL, " \n\t");
        if(tok){
          z=strlen(tok);
          if(strcmp(tok, "/")==0){
            len++;
            goto salto_linea;
          }          
        }
        else
          z=0;
        if((z+1+c)<MAX_CHAR && tok){
          strcat(aux2, tok);
          strcat(aux2, " ");  
          c+=z+1;
          len+=z+1;        
          tok=NULL;
        }
        else{
          salto_linea:
          for(c=c; c<MAX_CHAR; c++){
            aux2[strlen(aux2)]=' ';
          }
          line++;
          continue;          
        }        
      }
    }
  }
  free(aux1);
  return aux2;
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
  screen_area_destroy(ge->chat);
  screen_destroy();
  free(ge);
}

void graphic_engine_paint_intro(Graphic_engine *ge, Game *game, char *f){
  char *aux=NULL, *aux2=NULL;
  screen_area_clear(ge->map);
  aux=game_get_tutorial(game);
  aux2=graphic_engine_adapt_text(aux, MAX_CHAR_MAP, MAX_LINE_MAP);
  /*printf("%s", aux2);*/
  screen_area_puts(ge->map, aux2);
  screen_area_puts(ge->banner, "    Murder Mystery   ");
  screen_area_puts(ge->help, " ");
  screen_area_puts(ge->help, " ");
  screen_area_puts(ge->help, "                                    Press any key to continue.");
  screen_paint();
  printf("prompt :> ");
  fgets(aux2, WORD_SIZE, stdin); /*waiting to press any key*/
  free(aux2);
}

void graphic_engine_paint_end(Graphic_engine *ge, Game *game, char *f){
  char *aux=NULL;
  Npc *guilty=NULL;
  int win=0;
  char str[WORD_SIZE]="", aux2[WORD_SIZE], *tok=NULL, *txt=NULL;
  screen_area_clear(ge->map);
  aux=game_get_end(game);
  strcpy(aux2, aux);
  tok=strtok(aux2, "[");
  sprintf(str, "%s", tok);
  strcat(str, game_get_last_argument(game));
  tok=strtok(NULL, "]");
  tok=strtok(NULL, "[");
  strcat(str, tok);
  guilty=game_get_npc_at_name(game, game_get_last_argument(game));
  if(npc_get_guilty(guilty)==TRUE){
    strcat(str, "guilty");
    win=1;
  }
  else{
    strcat(str, "innocent");
  }
  tok=strtok(NULL, "]");
  tok=strtok(NULL, "\n|");
  if(tok)
    strcat(str, tok);
  txt=graphic_engine_adapt_text(str, MAX_CHAR_MAP, MAX_LINE_MAP);
  screen_area_puts(ge->map, txt);
  free(txt);
  screen_area_clear(ge->help);
  if(win==1){
    screen_area_puts(ge->help, "                                             YOU WIN");
  }
  else{
    screen_area_puts(ge->help, "                                             YOU LOSE");    
  }
  screen_area_clear(ge->descript);
  screen_area_puts(ge->descript, "Credits:");
  screen_area_puts(ge->descript, "DAVID TEOFILO GARITAGOITIA ROMERO");
  screen_area_puts(ge->descript, "JOSE MANUEL GARCIA GIRALDEZ");
  screen_area_puts(ge->descript, "DANIEL CERRATO SANCHEZ");
  screen_area_puts(ge->descript, "DIEGO GRANDE CAMARERO");
  screen_area_clear(ge->feedback);
  screen_area_puts(ge->feedback, "We hope you enjoyed playing our game");
  screen_area_clear(ge->chat);
  screen_area_puts(ge->chat, " ");
  screen_area_puts(ge->chat, "                  ****  ****");
  screen_area_puts(ge->chat, "                **************");
  screen_area_puts(ge->chat, "                 ************");
  screen_area_puts(ge->chat, "                   ******** ");
  screen_area_puts(ge->chat, "                     ****");
  screen_area_puts(ge->chat, "                      **");

  screen_paint();
  return;

}
void graphic_engine_paint_game(Graphic_engine *ge, Game *game, FILE *file)
{
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_right = NO_ID, id_left = NO_ID; 
  int i, z; /*auxiliar ints*/
  Space *space_act=NULL;
  char obje[Object_MAX]="";
  char str[MAX_STR], *aux;
  int position1=0,position2;
  char string1[NUM_CHARACTS +1]="";
  char string2[NUM_CHARACTS +1]="";
  char string3[NUM_CHARACTS +1]="";
  char string_left[NUM_CHARACTS + 1]="";
  char string_aux[NUM_CHARACTS + 1]="";
  char string_right[NUM_CHARACTS + 1]="";
  char argument[CMD_LENGHT];
  char *toks=NULL;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  char npc[WORD_SIZE];
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

      sprintf(str, "     %s|%s%c%2d|%s", string_left, obje, game_get_npc_initial(game, space_act), (int)id_back, string_right);
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
      sprintf(str, "            |%s %c |", obje, game_get_npc_initial(game, space_act));
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

      sprintf(str, "     %s|%s%c%2d|%s", string_left, obje, game_get_npc_initial(game, space_act), (int)id_next, string_right);
      screen_area_puts(ge->map, str);
      sprintf(str, "            | %s          |",string1);
      screen_area_puts(ge->map, str);
      sprintf(str, "            | %s          |",string2);
      screen_area_puts(ge->map, str);
    }
  }
  game_get_full_npc_name(game, npc);
  /* Paint the in the description area */
  screen_area_clear(ge->descript);
  sprintf(str, "Objects location:  ");          
  screen_area_puts(ge->descript, str);
  game_get_objects_location(game, obje);
  aux=graphic_engine_adapt_text(obje, MAX_CHAR_DESCRIPT, 8);
  sprintf(str, "%s", aux);  
  free(aux);          
  screen_area_puts(ge->descript, str);
  game_get_player_objects(game, obje);
  sprintf(str, "Player object:");
  aux=graphic_engine_adapt_text(obje, MAX_CHAR_DESCRIPT, 3);          
  screen_area_puts(ge->descript, str);
  screen_area_puts(ge->descript, aux);
  free(aux);
  sprintf(str, "Last dice value: %d", dice_get_last(game_get_dice(game)));          
  screen_area_puts(ge->descript, str);
  sprintf(str, "Space:");  
  screen_area_puts(ge->descript, str);  
  if(space_is_iluminated(game_get_space(game, player_get_location(game_get_player(game))))==TRUE){
    aux=graphic_engine_adapt_text(space_get_description1(game_get_space(game, player_get_location(game_get_player(game)))), MAX_CHAR_DESCRIPT, 4);
    sprintf(str, "%s", aux);
    free(aux);
  }
  else
    sprintf(str, "Nothing is seen");      
  screen_area_puts(ge->descript, str); 
  /* Paint the in the banner area */
  screen_area_puts(ge->banner, "     Murder Mystery     ");
  /* Paint the in the help area */
  screen_area_clear(ge->help);
  sprintf(str, "The commands you can use are: / move or m, exit or e, take or t, drop or d, roll or rl, inspect or i, turnon or tn, turnoff or tf, open or o, load or lo, save or s, talk or tl, accuse or a, next or n, back or b, left or l, right or r.");
  aux=graphic_engine_adapt_text(str, MAX_CHAR_HELP, MAX_LINE_HELP);
  screen_area_puts(ge->help, aux);
  free(aux);
  /*Paint the chat area*/
  screen_area_clear(ge->chat);
  screen_area_puts(ge->chat, npc);
  if(npc_get_description(game_get_npc(game))!=NULL){
    aux=graphic_engine_adapt_text(npc_get_description(game_get_npc(game)), MAX_CHAR_CHAT, MAX_LINE_CHAT-1);
    sprintf(str, "%s", aux);
    screen_area_puts(ge->chat, str);
    free(aux);    
  }
  /* Paint the in the feedback area */
  screen_area_clear(ge->feedback);
  sprintf(str, "%s (%s): %s", cmd_to_str[game_get_last_principal_command(game) - NO_CMD][CMDL], cmd_to_str[game_get_last_principal_command(game) - NO_CMD][CMDS], command_get_status(game_get_last_command(game)));
  aux=graphic_engine_adapt_text(str, MAX_CHAR_FEEDBACK, 5);
  screen_area_puts(ge->feedback, aux);  
  free(aux);  
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
