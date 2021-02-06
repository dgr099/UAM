#include <stdio.h>
#include <stdlib.h>
#include "element.h"

struct _Element{
  char *a;
};

Element* element_init(){
  Element* element;
  element=(Element*)malloc(sizeof(Element));
  element->a=NULL;
  if(!element){
    return NULL;
  }
  return element;
}

void element_free(Element *element){
  if(!element){
    return;
  }
  free(element);
  element=NULL;
  return;
}

Element* element_setInfo(Element* element, void* info){
  if(!element || !info){
    return NULL;
  }
  element->a=info;
  return NULL;
}

void* element_getInfo(Element* element){
  if(!element){
    return NULL;
  }
  return element->a;
}

Element* element_copy(const Element* element){
  Element *aux=NULL;
  if(!element){
    return NULL;
  }
  aux=element_init();
  if(!aux){
    return NULL;
  }
  aux->a=element->a;
  return aux;
}

Bool element_equals(const Element* element, const Element* element2){
  if(!element || !element2){
    return FALSE;
  }
  if(element->a==element2->a){
    return TRUE;
  }
  return FALSE;
}

int element_print(FILE* f, const Element* element){
  if(!f || !element){
    return -1;
  }
  return fprintf(f, "%s", element->a);
}