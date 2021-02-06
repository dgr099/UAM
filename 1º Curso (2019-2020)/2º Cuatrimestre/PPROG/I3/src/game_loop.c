/** 
 * @brief It defines the game loop 
 * 
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/graphic_engine.h"
/**
* @brief  Initialize the game
*
*
* @date 10/02/2020
* @author: Profesores PPROG
*
* @param game game address
* @param gengine *gengine address 
* @param file_name  file name addres 
* @return Returns 0 or 1 in case of error
*/
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);
/**
* @brief  Initialize the game loop
*
*
* @date 10/02/2020
* @author: Profesores PPROG
*
* @param game game address
* @param gengine gengine address 
* @param file file address 
* @return 
*/
void game_loop_run(Game *game, Graphic_engine *gengine, FILE *file);
/**
* @brief  Initialize the Initializes the release of dynamic memory
*
*
* @date 10/02/2020
* @author: Profesores PPROG
*
* @param game game address
* @param gengine *gengine address 
* @param f pointer to the file
* @return
*/
void game_loop_cleanup(Game *game, Graphic_engine *gengine, FILE *f);

/**
* @brief the main function of game_loop
** main
*
* @date 06-03-2019
* @author Instructor of PPROG
* @param argc number received at start of run
* @param argv array of strings received at start of run
* @return
*/
int main(int argc, char *argv[])
{ /*argc is the number of chains that it indicates argv*/
  Game *game;
  Graphic_engine *gengine;
  FILE *file = NULL;

  if (argc < 2)
  {                                                         /*if you don't receive any arguments besides ./executable*/
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }
  if (argc>=3 && strcmp(argv[2],"-l") == 0){
    if(argc<4){
      fprintf(stdout,"ERROR, debe introducir un fichero LOG\n");
      return -1;
    }
   
      file = fopen(argv[3], "w");
      if(file==NULL){
        fprintf(stdout,"ERROR, debe introducir un fichero LOG\n");
        return -1;
       }
    if (game_loop_init(&game, &gengine, argv[1]) != 1)
    {
      game_loop_run(game, gengine,file);
      game_loop_cleanup(game, gengine, file);
    }
    fclose(file);
  }
  else{
    if (game_loop_init(&game, &gengine, argv[1]) != 1)
    {
      game_loop_run(game, gengine,file);
      game_loop_cleanup(game, gengine, file);
    }
  }
  return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name)
{
  if ((*game=game_create_from_file(file_name)) == NULL)
  {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }
  if ((*gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(*game);
    return 1;
  }

  return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine,FILE *file)
{
  Command *cmd;
  cmd = command_init();


  while ((command_get_principalcmd(cmd)!= EXIT) && !game_is_over(game))
  {
    graphic_engine_paint_game(gengine, game, file);
    cmd = command_get_user_input(cmd);
    game_update(game, command_get_principalcmd(cmd), command_get_argument(cmd));
}
command_destroy(cmd);
return;
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine, FILE *f)
{
  game_destroy(game);
  graphic_engine_destroy(gengine);
  if(f){
    fprintf(f, "exit");
  }
}
