#include "../include/cmdAnswer.h"
#include "../include/command.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/types.h"
/**
* @brief The command answer structure
*
* It stores information of a command answer
*/
struct  _CmdAnswer{
  char *error_awnsers[MAX_ERROR+1][MAX_F+1]; /*!< the error matrix */
  int num_errores;  /*!< the number of diferents errors */
  char *ok_awnsers[MAX_F+1];/*!< the ok matrix */
  int last; /*!< the last index of error or ok (used to avoid repeating ans) */
};

CmdAnswer *CmdAnswer_init(){
  CmdAnswer *cmd_a=NULL;
  int i, j;
  if(!(cmd_a=calloc(1, sizeof(CmdAnswer))))
    return NULL;
  for(i=0; i<MAX_ERROR; i++){
    for(j=0; j<MAX_F; j++)
      cmd_a->error_awnsers[i][j]=NULL;
  }
  cmd_a->num_errores=0;
  cmd_a->last=-1;
  for(i=0; i<MAX_F; i++){
    cmd_a->ok_awnsers[i]=NULL;
  }
  return cmd_a;
}

STATUS CmdAnswer_destroy(CmdAnswer *cmda){
  int i, j;
  if(!cmda){
    return ERROR;
  }
  for(i=0; i<=cmda->num_errores; i++){
    for(j=0; cmda->error_awnsers[i][j]; j++){
      free(cmda->error_awnsers[i][j]);
    }
  }
  for(i=0; cmda->ok_awnsers[i]; i++){
    free(cmda->ok_awnsers[i]);
  }
  free(cmda);
  return OK;
}
STATUS CmdAnswer_add_new_error(CmdAnswer *cmda){
  if(!cmda)
    return ERROR;
  if(cmda->num_errores+1==MAX_ERROR){
    return ERROR;
  }
  cmda->num_errores++;
  return OK;
}

STATUS CmdAnswer_add_error_at(CmdAnswer *cmda ,char *awns, int n){
  int i;
  if(!cmda || !awns || n<0 || n>(cmda->num_errores)){
    return ERROR;
  }
  for(i=0; cmda->error_awnsers[n][i]!=NULL; i++);
  if(i>=MAX_ERROR){
    return ERROR;
  }
  if(!(cmda->error_awnsers[n][i]=(char*)calloc(WORD_SIZE, sizeof(char)))){
    return ERROR;
  }
  strcpy(cmda->error_awnsers[n][i], awns);
  return OK;
}

STATUS CmdAnswer_add_ok(CmdAnswer *cmda, char *awns){
  int i;
  if(!cmda || !awns){
    return ERROR;
  }
  for(i=0; cmda->ok_awnsers[i]; i++);
  if(i>=MAX_F){
    return ERROR;
  }
  if(!(cmda->ok_awnsers[i]=(char*)calloc(WORD_SIZE, sizeof(char)))){
    return ERROR;
  }
  strcpy(cmda->ok_awnsers[i], awns);
  return OK;
}

char* CmdAnswer_get_random_error(CmdAnswer *cmda, int n){
  int i, j;
  char *rderr;
  if(!cmda || n>cmda->num_errores){
    return NULL;
  }
  if(!(rderr=calloc(WORD_SIZE, sizeof(char))));
  for(i=0; cmda->error_awnsers[n][i]!=NULL; i++);
  do{
    j = rand() % i;
  } while(j==cmda->last && i>1);
  cmda->last=j;
  strcpy(rderr, cmda->error_awnsers[n][j]);
  /*rderr=cmda->error_awnsers[n][j];*/
  return rderr;
}

char* CmdAnswer_get_random_ok(CmdAnswer* cmda){
  int i, j;
  char *rdok;
  if(!cmda)
    return NULL;
  for(i=0; cmda->ok_awnsers[i]!=NULL; i++);
  if(!(rdok=calloc(WORD_SIZE, sizeof(char))))
    return NULL;
  do{
    j = rand() % i;
  } while(j==cmda->last && i>1);
  cmda->last=j;
  strcpy(rdok, cmda->ok_awnsers[j]);
  /**rdok=*cmda->ok_awnsers[j];*/
  return rdok;
}