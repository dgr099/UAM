/** 
 * @brief It implements the command interpreter
 * 
 * @file command.h
 * @author Profesores PPROG y José Manuel García Giráldez
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
#define N_CMD 7
/**
* @brief  The CmdType enum
*/
typedef enum enum_CmdType {
  CMDS, /*CMDS*/ 
  CMDL /*CMDL*/
  } T_CmdType;
/**
* @brief  The Command enum
*/
typedef enum enum_Command {
  NO_CMD = -1, /*NO_CMD*/
  UNKNOWN, /*Unknow command*/
  EXIT, /*Exit command*/
  NEXT, /*Next command*/
  BACK, /*Back command*/
  TAKE, /*Take command*/
  DROP /*Drop command*/
  } T_Command;
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
T_Command command_get_user_input();

#endif
