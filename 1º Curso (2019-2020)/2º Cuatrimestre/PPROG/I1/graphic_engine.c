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
#include "screen.h"
#include "graphic_engine.h"
#include "command.h"
#include "player.h"
#include "object.h"
#include "game_reader.h"
#include "game.h"
#include "space.h"
/*! \def MAX_STR
    \brief A macro that stores the maximum number of strings
   
    Details.
*/
#define MAX_STR 255
/*! \def MAP_WIDHT
    \brief A macro that stores the widht of the map
   
    Details.
*/
#define MAP_WIDHT 48
/*! \def MAP_HEIGHT
    \brief A macro that stores the height of the map
   
    Details.
*/
#define MAP_HEIGHT 13
/*! \def DESCRIPT_WIDHT
    \brief A macro that stores the widht of the descript
   
    Details.
*/
#define DESCRIPT_WIDHT 29
/*! \def BANNER_WIDHT
    \brief A macro that stores the widht of the banner
   
    Details.
*/
#define BANNER_WIDHT 23
/*! \def BANNER_X
    \brief Macro containing the x coordinate of the banner
   
    Details.
*/
#define BANNER_X 28
/**
* @brief The graic engine structure
*
* It stores information of the graphic engine
*/
struct _Graphic_engine
{
  Area *map, *descript, *banner, *help, *feedback; /*!< Area of map, descript, etc. */
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
  ge->map = screen_area_init(1, 1, MAP_WIDHT, MAP_HEIGHT);
  ge->descript = screen_area_init(MAP_WIDHT + 2, 1, DESCRIPT_WIDHT, MAP_HEIGHT);
  ge->banner = screen_area_init(BANNER_X, MAP_HEIGHT + 2, BANNER_WIDHT, 1);
  ge->help = screen_area_init(1, MAP_HEIGHT + 3, MAP_WIDHT + DESCRIPT_WIDHT + 1, 2);
  ge->feedback = screen_area_init(1, MAP_HEIGHT + 6, MAP_WIDHT + DESCRIPT_WIDHT + 1, 3);
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

void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID;
  Space *space_act = NULL;
  char obj = '\0';
  char str[MAX_STR];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = player_get_location(game->player)) != NO_ID)
  {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    if (game_get_object_location(game, object_get_id(game->object)) == id_back)
      obj = '*';
    else
      obj = ' ';
    if (id_back != NO_ID)
    {
      sprintf(str, "  |         %2d|", (int)id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }
    if (game_get_object_location(game, object_get_id(game->object)) == id_act)
      obj = '*';
    else
      obj = ' ';
    if (id_act != NO_ID)
    {
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | 8D      %2d|", (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }
    if (game_get_object_location(game, object_get_id(game->object)) == id_next)
      obj = '*';
    else
      obj = ' ';

    if (id_next != NO_ID)
    {
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |         %2d|", (int)id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
    }
  }
  /* Paint the in the description area */
  screen_area_clear(ge->descript);
  if ((obj_loc = game_get_object_location(game, object_get_id(game->object))) != NO_ID)
  {
    sprintf(str, "  Object location:%d", (int)obj_loc);
    screen_area_puts(ge->descript, str);
  }
  /* Paint the in the banner area */
  screen_area_puts(ge->banner, " The game of the Goose");
  /* Paint the in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next or n, back or b, exit or e, take or t, drop or d");
  screen_area_puts(ge->help, str);
  /* Paint the in the feedback area */
  last_cmd = game_get_last_command(game);
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);
  /* Dump to the terminal */
  screen_paint();
  printf("prompt :> ");
}
