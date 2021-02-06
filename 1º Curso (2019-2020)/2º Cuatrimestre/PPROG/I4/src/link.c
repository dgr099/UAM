/**
* @brief It implements the link interface
*
* @file link.c
* @author David Teófilo Garitagoitia Romero
* @version 1.0
* @date 17-03-2020
* @copyright GNU Public License
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/game.h"
#include "../include/types.h"
#include "../include/link.h"

/**
* @brief The link structure
*
* It stores information of a link
*/
struct _Link{
  char  name [WORD_SIZE + 1]; /*!< the name of the link */
  Id id; /*!< the id of the link */
  Id  Id1; /*!< the id of the first link */
  Id  Id2; /*!< the id of the secod link */
  int open; /*!< an integer to determine whether or not a link is open */
};


Link* link_create(Id id){
  Link* link;
  if(!(link=(Link *)calloc(1, sizeof(Link))) || id==NO_ID){
    return NULL;
  }
  link->id=id;
  return link;
}

STATUS link_set_name(Link* link, char* name){
  if(!link || !name){
    return ERROR;
  }
  if (!strcpy(link->name, name))
  { /*it's checked if there is an error*/
    return ERROR;
  }
  return OK;
}

STATUS link_set_id1(Link* link, Id id){
  if(!link || id==NO_ID){
    return ERROR;
  }
  link->Id1=id;
  return OK;
}

STATUS link_set_id2(Link* link, Id id){
  if(!link || id==NO_ID){
    return ERROR;
  }
  link->Id2=id;
  return OK;
}

STATUS link_set_open(Link* link, int open){
  if(!link){
    return ERROR;
  }
  link->open=open;
  return OK;
}

STATUS link_destory(Link* link){
  if(!link){
    return ERROR;
  }
  free(link);
  return OK;
}

Id  link_get_id(Link* link){
  if(!link){
    return NO_ID;
  }
  return link->id;
}

char* link_get_name(Link* link){
  if(!link){
    return NULL;
  }
  return link->name;
}

Id  link_get_id1(Link* link){
  if(!link){
    return NO_ID;
  }
  return link->Id1;
}

Id  link_get_id2(Link* link){
  if(!link){
    return NO_ID;
  }
  return link->Id2;
}

BOOL  link_is_open(Link* link){
  if(!link){
    return FALSE;
  }
  switch(link->open){
    case 1:
      return FALSE;
    case 0:
      return TRUE;
  }
  return FALSE;
}

STATUS link_print(FILE* f,Link* link){
  if(!link){
    return ERROR;
  }
  fprintf(f, "Name: %s\nId1: %ld\nId2: %ld\nOpen: %d\n", link->name, link->Id1, link->Id2, link->open);
  return OK;
}