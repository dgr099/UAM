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
#include "graphic_engine.h"
#include "game.h"
#include "command.h"
/**
* @brief  Initialize the game
* gane_loop_init
*
* @date 10/02/2020
* @author: Profesores PPROG
*
* @param game game address
* @param gengine **gengine address 
* @param file_name  file name addres 
* @return Returns 0 or 1 in case of error
*/
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);
/**
* @brief  Initialize the game loop
* game_loop_run
*
* @date 10/02/2020
* @author: Profesores PPROG
*
* @param game game
* @param gengine gengine address 
* @return 
*/
void game_loop_run(Game game, Graphic_engine *gengine);
/**
* @brief  Initialize the Initializes the release of dynamic memory
*
*
* @date 10/02/2020
* @author: Profesores PPROG
*
* @param game game address
* @param gengine *gengine address 
* @return
*/
void game_loop_cleanup(Game game, Graphic_engine *gengine);
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
  Game game;
  Graphic_engine *gengine;

  if (argc < 2)
  {                                                         /*if you don't receive any arguments besides ./executable*/
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }
  if (!game_loop_init(&game, &gengine, argv[1]))
  {
    game_loop_run(game, gengine);
    game_loop_cleanup(game, gengine);
  }

  return 0;
}
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
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name)
{
  if (game_create_from_file(game, file_name) == ERROR)
  {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }
  if ((*gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
  }

  return 0;
}
/**
* @brief  Initialize the game loop
*
*
* @date 10/02/2020
* @author: Profesores PPROG
*
* @param game game address
* @param gengine gengine address 
* @return 
*/
void game_loop_run(Game game, Graphic_engine *gengine)
{
  T_Command command = NO_CMD;

  while ((command != EXIT) && !game_is_over(&game))
  {
    graphic_engine_paint_game(gengine, &game);
    command = command_get_user_input();
    game_update(&game, command);
  }
}
/**
* @brief  Initialize the Initializes the release of dynamic memory
*
*
* @date 10/02/2020
* @author: Profesores PPROG
*
* @param game game address
* @param gengine *gengine address 
* @return
*/
void game_loop_cleanup(Game game, Graphic_engine *gengine)
{
  game_destroy(&game);
  graphic_engine_destroy(gengine);
}
