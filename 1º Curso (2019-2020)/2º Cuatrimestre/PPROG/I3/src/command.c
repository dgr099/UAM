/** 
 * @brief It implements the command interpreter
 * 
 * @file command.c
 * @author Profesores PPROG
 * @version 2.0 
 * @date 13-01-2020 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/command.h"
#include "../include/game_reader.h"
/**
* @brief The command structure
*
* It stores information of a command
*/
struct _Command{
T_Command principalcmd; /*!<the principal cmd*/
char argument[CMD_LENGHT]; /*!< the argument of the cmd */
char Status[WORD_SIZE]; /*!< the status result of ejecuting the cmd */
};
/*! \var cmd_to_str
    \brief matrix of commands
    
    Details.
*/
char *cmd_to_str[N_CMD][N_CMDT] = {{"", "no command"}, {"", "unknown"}, {"e", "exit"}, {"t", "take"}, {"d", "drop"}, {"rl", "roll"}, {"m", "move"}, {"i", "inspect"}, {"n", "next"}, {"b", "back"}, {"r", "right"}, {"l", "left"}};


Command *command_init(){
Command *cmd = NULL;
cmd = (Command *)malloc(sizeof(Command));
  if (!cmd)/*it's checked if there is an error*/
    return NULL;
cmd->principalcmd=NO_CMD;
strcpy(cmd->argument,"\0");
strcpy(cmd->Status,"ERROR");

return cmd;
}

Command *command_get_user_input(Command *cmd)
{
  char line[WORD_SIZE] = "";
  char *toks1,*toks;
  char input[CMD_LENGHT] = "Unknown";
  command_set_status(cmd, "ERROR");
  /*char argument[WORD_SIZE] = "";*/
  int i = UNKNOWN - NO_CMD + 1;

  if (!cmd)/*it's checked if there is an error*/
    return NULL;

 fgets(line, WORD_SIZE, stdin);
  toks = strtok(line, " \n");
  if(toks!=NULL)
  strcpy(input, toks);
  if(strncmp("t", line, 1) == 0 || strncmp("d", line, 1)==0 || strncmp("m", line, 1)==0 || strncmp("i", line, 1)==0){
      toks1 = strtok(NULL, " \n");
      if(toks1!=NULL)
        strcpy(cmd->argument, toks1);
      else
        strcpy(cmd->argument, "\0");
  }
  else
    strcpy(cmd->argument, "\0");
  cmd->principalcmd = UNKNOWN;
    while (cmd->principalcmd == UNKNOWN && i < N_CMD)
    {
      if (!strcasecmp(input, cmd_to_str[i][CMDS]) || !strcasecmp(input, cmd_to_str[i][CMDL]))
      {
        cmd->principalcmd = i + NO_CMD;
      }
      else
      {
        i++;
      }
    }
  return cmd;
}
T_Command command_get_principalcmd(Command *cmd){

if (!cmd)
return NO_CMD;

return cmd->principalcmd;
}

char *command_get_argument(Command *cmd){
if (!cmd)
return NULL;

return cmd->argument;
}

STATUS command_destroy(Command *cmd){
if (!cmd)
return ERROR;

free(cmd);
return OK;
}

STATUS command_set_principalcmd(Command *cmd, T_Command command){
if(!cmd || command==NO_CMD)
return ERROR;

cmd->principalcmd=command;
return OK;
}
STATUS command_set_argument(Command *cmd, char *argument){
if(!cmd || argument==NULL)
return ERROR;

if (!strcpy(cmd->argument, argument))
  { /*it's checked if there is an error*/
    return ERROR;
  }
  return OK;
}

STATUS command_set_status(Command *cmd, char *status){
  if(!cmd || status==NULL)
    return ERROR;

if (!strcpy(cmd->Status, status))
  { /*it's checked if there is an error*/
    return ERROR;
  }
  return OK;
}

char* command_get_status(Command *cmd){
  if(!cmd){
    return NULL;
  }
  return cmd->Status;
}