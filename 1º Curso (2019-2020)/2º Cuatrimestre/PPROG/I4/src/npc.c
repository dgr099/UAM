#include <stdio.h>
#include "../include/npc.h"
#include "../include/types.h"
#include "../include/space.h"
#include <stdlib.h>
#include <string.h>
/**
* @brief The npc structure
*
* It stores information of a npc
*/
struct _Npc{
  Id id;  /*!< npc identifier */
  BOOL guilty; /*!<0 indicates if this npc is guilty or not*/
  int nd; /*!< number of dialogues */
  char name[WORD_SIZE];/*!< npc name*/
  char description[WORD_SIZE]; /*!< npc description*/
  char dialogues[MAX_DIALOGUES][WORD_SIZE];/*!<dialogue matrix */
  Id position;/*!<the position of the npc */
  int last;/*!<last index of dialogue (usedto avoid repeating*/
};

Npc* npc_init(Id id){
  /*int i, j;*/
  Npc *new;
  if(!(new=calloc(1, sizeof(Npc))))
    return NULL;
  new->guilty=FALSE;
  new->nd=0;
  new->id=id;
  /*for(i=0; i!=MAX_DIALOGUES; i++){
    for(j=0; j!=WORD_SIZE; j++){
      new->dialogues[i][j] = ' ';
    }
  }*/
  new->position=NO_ID;
  new->last=-1;
  return new;
}

STATUS npc_set_name(Npc *npc, char* name){
  if(!npc||!name){
    return ERROR;
  }
  if(!strcpy(npc->name, name))
    return ERROR;
  return OK;
}

STATUS npc_add_dialogue(Npc *npc, char *dialogue){
  if(!npc || !dialogue || npc->nd==MAX_DIALOGUES)
    return ERROR;
  if(!strcpy(npc->dialogues[npc->nd], dialogue))
    return ERROR;
  npc->nd++;
  return OK;
}

STATUS npc_set_culpability(Npc *npc, BOOL g){
  if(!npc)
    return ERROR;
  npc->guilty=g;
  return OK;
}

char* npc_get_random_dialogue(Npc *npc){
  int i;
  char *dialogue;
  if(!npc)
    return NULL;
  do{
  i = rand() % npc->nd;    
  }while(i==npc->last);
  npc->last=i;
  if(!(dialogue=(char*)calloc(WORD_SIZE, sizeof(char))));
  if(!(strcpy(dialogue, npc->dialogues[i])))
    return NULL;
  return dialogue;
  //return npc->dialogues[i];
}

char* npc_get_name(Npc *npc){
  if(!npc){
    return ERROR;
  }
  return npc->name;
}

BOOL npc_get_guilty(Npc *npc){
  if(!npc)
    return FALSE;
  return npc->guilty;
}

STATUS npc_destroy(Npc *npc){
  if(!npc){
    return ERROR;
  }
  free(npc);
  return OK;
}

Id npc_get_position(Npc *npc){
  if(!npc){
    return NO_ID;
  }
  return npc->position;
}

STATUS npc_set_position(Npc *npc, Id position){
  if(!npc || position==NO_ID){
    return ERROR;
  }
  npc->position=position;
  return OK;
}

char npc_get_initial(Npc *npc){
  if(!npc){
    return ' ';
  }
  return npc->name[0];
}

STATUS npc_set_number_dialogues(Npc *npc, int n){
  if(!npc || n<0){
    return ERROR;
  }
  npc->nd=n;
  return OK;
}

STATUS npc_set_description(Npc *npc, char *descr){
  if(!npc || !descr){
    return ERROR;
  }
  if(!strcpy(npc->description, descr))
    return ERROR;
  return OK;
}

char* npc_get_description(Npc *npc){
  if(!npc){
    return NULL;
  }
  return npc->description;
}

Id npc_get_id(Npc *npc){
  if(!npc){
    return NO_ID;
  }
  return npc->id;
}