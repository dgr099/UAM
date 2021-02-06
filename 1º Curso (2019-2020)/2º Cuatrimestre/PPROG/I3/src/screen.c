/** 
 * @brief is responsible for drawing the background of the game, also     
 * eliminates distractions from the thermianal, cleaning the screen
 *
 * @file screen.c
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/screen.h"

#pragma GCC diagnostic ignored "-Wpedantic"
/*! \def ROWS
    \brief A macro that stores the number of rows
   
    Details.
*/
#define ROWS 30
/*! \def COLUMNS
    \brief A macro that stores the number of columns
   
    Details.
*/
#define COLUMNS 80
/*! \def TOTAL_DATA
    \brief A macro that stores ROWS*COLUMNS+1
   
    Details.
*/
#define TOTAL_DATA (ROWS * COLUMNS) + 1
/*! \def BG_CHAR
    \brief BG_CHAR
   
    Details.
*/
#define BG_CHAR '~'
/*! \def FG_CHAR
    \brief FG_CHAR
   
    Details.
*/
#define FG_CHAR ' '
/*! \def PROMPT
    \brief Prompt
   
    Details.
*/
#define PROMPT " prompt:> "
/*! \def ACCESS(d, x, y) (d + ((y)*COLUMNS) + (x))
    \brief acces
   
    Details.
*/
#define ACCESS(d, x, y) (d + ((y)*COLUMNS) + (x))

/**
* @brief  The Area structure
*
* store the information necessary to draw the area 
*/

struct _Area
{
  int x; /*!< coordinates X*/
  int y; /*!< coordinates Y*/
  int width; /*!< widht*/
  int  height; /*!< height */
  char *cursor;            /*!< name of the cursor */
};
/*! \var __data
    \brief __data
    
    Details.
*/
char *__data;

/****************************/
/*     Private functions    */
/****************************/
/**
* @brief Prevents errors from occurring when the cursor is out of bounds
*
* screen_area_cursor_is_out_of_bounds 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* param area the area we want to modified
* return area->cursor the cursor we have modified
*/
int screen_area_cursor_is_out_of_bounds(Area *area);
/**
* @brief scroll up the area
*
* screen_area_scroll_up 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* param area the area we want to modified
*/
void screen_area_scroll_up(Area *area);
/**
* @brief replace special chars
*
* screen_utils_replaces_special_chars 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* param str the string with the special characters
*/
void screen_utils_replaces_special_chars(char *str);

/****************************/
/* Functions implementation */
/****************************/

void screen_init()
{
  /* first destroy a previous screen if it existed, then fill the background*/
  screen_destroy(); /* Dispose if previously initialized */
  __data = (char *)malloc(sizeof(char) * TOTAL_DATA);
  if (__data)
  {
    memset(__data, (int)BG_CHAR, TOTAL_DATA); /*Fill the background*/
    *(__data + TOTAL_DATA - 1) = '\0';        /*NULL-terminated string*/
  }
}

void screen_destroy()
{
  if (__data)
    free(__data);
}

void screen_paint()
{
  /*First check if there is data, then print*/
  char *src = NULL;
  char dest[COLUMNS + 1];
  int i = 0;
  memset(dest, 0, COLUMNS + 1);
  if (__data)
  {
    /* puts(__data); */ /*Dump data directly to the terminal*/
    /*It works fine if the terminal window has the right size*/
    puts("\033[2J"); /*Clear the terminal*/
    for (src = __data; src < (__data + TOTAL_DATA - 1); src += COLUMNS)
    {
      memcpy(dest, src, COLUMNS);
      /* printf("%s\n", dest); */
      for (i = 0; i < COLUMNS; i++)
      {
        if (dest[i] == BG_CHAR)
        {
          printf("\033[0;34;44m%c\033[0m", dest[i]); /* fg:blue(34);bg:blue(44) */
        }
        else
        {
          printf("\033[0;30;47m%c\033[0m", dest[i]); /* fg:black(30);bg:white(47)*/
        }
      }
      printf("\n");
    }
  }
}

void screen_gets(char *str)
{
  fprintf(stdout, PROMPT);
  if (fgets(str, COLUMNS, stdin))
    *(str + strlen(str) - 1) = 0; /* Replaces newline character with '\0' */
}

Area *screen_area_init(int x, int y, int width, int height)
{
  /*First reserve memory and check if there is an error, if not then create the area*/
  int i = 0;
  Area *area = NULL;
  if ((area = (Area *)malloc(sizeof(struct _Area))))
  { /*reserve memory for area*/
    *area = (struct _Area){x, y, width, height, ACCESS(__data, x, y)};
    for (i = 0; i < area->height; i++)
      memset(ACCESS(area->cursor, 0, i), (int)FG_CHAR, (size_t)area->width);
  }
  return area;
}

void screen_area_destroy(Area *area)
{
  if (area)
    free(area);
}

void screen_area_clear(Area *area)
{
  /*First check if exists area if it exists then clear it*/
  int i = 0;
  if (area)
  {                                 /*check if exists area*/
    screen_area_reset_cursor(area); /*call the function*/
    for (i = 0; i < area->height; i++)
      memset(ACCESS(area->cursor, 0, i), (int)FG_CHAR, (size_t)area->width);
  }
}

void screen_area_reset_cursor(Area *area)
{
  if (area)
    area->cursor = ACCESS(__data, area->x, area->y);
}

void screen_area_puts(Area *area, char *str)
{
  /*First chake if there is an error, if the cursor is out of bounds call a function that fix it, also if str have special characters call another function taht replace this characters, then put the area on the screen*/
  int len = 0;
  char *ptr = NULL;
  if (screen_area_cursor_is_out_of_bounds(area))
    screen_area_scroll_up(area);            /*call a function that fix if the area is out*/
  screen_utils_replaces_special_chars(str); /*call a function that replace the special characters of str*/
  for (ptr = str; ptr < (str + strlen(str)); ptr += area->width)
  {
    memset(area->cursor, FG_CHAR, area->width);
    len = (strlen(ptr) < area->width) ? strlen(ptr) : area->width;
    memcpy(area->cursor, ptr, len);
    area->cursor += COLUMNS;
  }
}

int screen_area_cursor_is_out_of_bounds(Area *area)
{
  return area->cursor > ACCESS(__data, area->x + area->width, area->y + area->height - 1);
}

void screen_area_scroll_up(Area *area)
{
  for (area->cursor = ACCESS(__data, area->x, area->y);
       area->cursor < ACCESS(__data, area->x + area->width, area->y + area->height - 2);
       area->cursor += COLUMNS)
  {
    memcpy(area->cursor, area->cursor + COLUMNS, area->width);
  }
}

void screen_utils_replaces_special_chars(char *str)
{
  char *pch = NULL;
  /* Replaces acutes and tilde with '??' */
  while ((pch = strpbrk(str, "ÁÉÍÓÚÑáéíóúñ")))
    memcpy(pch, "??", 2);
}