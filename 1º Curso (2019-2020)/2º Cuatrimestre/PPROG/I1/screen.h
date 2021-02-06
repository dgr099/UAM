/** 
 * @brief It defines a screen
 * 
 * @file screen.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 11-01-2017
 * @copyright GNU Public License
 */

#ifndef __SCREEN__
#define __SCREEN__
/*! \def SCREEN_MAX_STR
    \brief A macro to storage the max number of strings
   
    Details.
*/
#define SCREEN_MAX_STR 80
/*! \var typedef struct _Area Area
    \brief A type definition for a area.
    
    Details.
*/
typedef struct _Area Area;
/**
*@brief create the background
*
* screen_init
*
* @date 13-01-2015
* @author: Instructors of PPROG
*/
void screen_init();
/**
* @brief free the screen
*
* screen_destroy free a especific space 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*/
void screen_destroy();
/**
* @brief print in the terminal the background with the data
*
* screen_paint  
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
*/
void screen_paint();
/**
* @brief get the information on the screen
*
* screen_gets  
*
* @date 13-01-2015
* @author: Instructors of PPROG
*/
void screen_gets(char *str);
/**
* @brief create the area of the screen
*
* screen_area_init  
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* @param x coordinate x
* @param y coordinate y
* @param width coordinate width
* @param height coordinate height
* @return area the area that has been created
*/
Area *screen_area_init(int x, int y, int width, int height);
/**
* @brief free the area of the screen
*
* screen_destroy free a especific space 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
** param area the area we want free
*/
void screen_area_destroy(Area *area);
/**
* @brief clear the area
*
* screen_area_clear 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* param area the area we want to modified
*/
void screen_area_clear(Area *area);
/**
* @brief reset the cursor
*
* screen_area_reset_cursor 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* param area the area we want to modified
*/
void screen_area_reset_cursor(Area *area);
/**
* @brief puts the area
*
* screen_area_puts 
*
* @date 13-01-2015
* @author: Instructors of PPROG
*
* param area the area we want to modified
* param str the string we will use
*/
void screen_area_puts(Area *area, char *str);
#endif
