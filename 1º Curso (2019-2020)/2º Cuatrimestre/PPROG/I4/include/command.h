/** 
 * @brief It implements the command interpreter
 * 
 * @file command.h
 * @author José Manuel García Giráldez, David Teófilo Garitagoitia Romero 
 * @version 1.0 
 * @date 19-12-2014 
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H
/*! \def N_CMDT
    \brief A macro that stores the number of commands types
   
    Details.
*/
#define N_CMDT 2
/*! \def N_CMD
    \brief A macro that stores the number of diferents commands
   
    Details.
*/
#define N_CMD 19
/*! \def CMD_LENGHT
    \brief A macro that stores the maximum lenght of a cmd
   
    Details.
*/
#define CMD_LENGHT 30
#include "../include/types.h"
#include <stdio.h>
/*! \var typedef struct _Command Command
    \brief A type definition for a command.
    
    Details.
*/
typedef struct _Command Command;
/**
* @brief  The CmdType enum
*/
typedef enum enum_CmdType {
  CMDS, /*CMDS*/
  CMDL  /*CMDL*/ 
} T_CmdType;
/**
* @brief  The Command enum
*/
typedef enum enum_Command {
  NO_CMD = -1, 
  UNKNOWN, /*unknow command*/
  EXIT, /*command to finish the game*/
  TAKE, /*command to take an object*/
  DROP, /*command to drop an object*/
  ROLL, /*command to roll the dice*/
  MOVE, /*command to move the player*/
  INSPECT, /*command to inspect*/
  TURNON, /*command to turn on an object*/
  TURNOFF, /*command to turn off an object*/
  OPEN, /*command to open closed links*/
  SAVE, /*command to save the game*/
  LOAD,  /*command to load the game*/
  TALK, /*command to talk with an npc*/
  ACCUSE,  /*command to accuse an npc*/
  NEXT, /*command to go to the next space*/
  BACK,  /*command to go to the previous space*/
  RIGHT,  /*command to go to the right space*/
  LEFT  /*command to go to the left space*/
} T_Command;
/**
* @brief initialitates the structure command
** command_init
*
* @date 06-03-2019
* @author José Manuel García Giráldez
* @return the structure command
*/
Command *command_init();
/**
* @brief get the principal command and the argument 
*
* command_get_user_input
*
* @date 06-03-2019
* @author José Manuel García Giráldez
* @param cmd the command structure and file to log
* @return the structure command
*/
Command *command_get_user_input(Command *cmd);
/**
* @brief set an especific argument 
*
* command_set_argument
*
* @date 06-03-2019
* @author José Manuel García Giráldez
* @param cmd the command structure 
* @param argument the argument we want to set 
* @return ERROR if there is an error, otherwise return OK
*/
STATUS command_set_argument(Command *cmd, char *argument);
/**
* @brief set an especific command 
*
* command_set_principalcmd
*
* @date 06-03-2019
* @author José Manuel García Giráldez
* @param cmd the command structure 
* @param command the command we want to set 
* @return ERROR if there is an error, otherwise return OK
*/
STATUS command_set_principalcmd(Command *cmd, T_Command command);
/**
* @brief free the strcture command 
*
* command_destroy
*
* @date 06-03-2019
* @author José Manuel García Giráldez
* @param cmd the command structure 
* @return ERROR if there is an error, otherwise return OK
*/
STATUS command_destroy(Command *cmd);
/**
* @brief get an argument 
*
* command_get_argument
*
* @date 06-03-2019
* @author José Manuel García Giráldez
* @param cmd the command structure 
* @return the argument
*/
char *command_get_argument(Command *cmd);
/**
* @brief get the command 
*
* command_get_principalcmd
*
* @date 06-03-2019
* @author José Manuel García Giráldez
* @param cmd the command structure 
* @return the command
*/
T_Command command_get_principalcmd(Command *cmd);
/**
* @brief set an especific status 
*
* command_set_status
*
* @date 06-03-2019
* @author David Teófilo Garitagoitia Romero
* @param cmd the command structure
* @param status the status we want to set 
* @return ERROR if there is an error, otherwise return OK
*/
STATUS command_set_status(Command *cmd, char *status);
/**
* @brief get an especific status 
*
* command_get_status
*
* @date 06-03-2019
* @author David Teófilo Garitagoitia Romero
* @param cmd the command structure
* @return NULL if there is an error, otherwise return the status
*/
char* command_get_status(Command *cmd);

#endif
