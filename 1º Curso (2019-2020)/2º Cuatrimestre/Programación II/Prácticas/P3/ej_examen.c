#include "types.h"
#include "queue_fp.h"
#include "element.h"
Status from_red_to_blue(Queue *red, Queue *blue){
  Element *aux;
  if(!red || !blue){
    return ERROR;
  }
  while(queue_isEmpty(red)!=TRUE){
    aux=queue_extract(red);
    if(!aux){
      return ERROR;
    }
    if(queue_insert(blue, aux)==ERROR){
      element_free(aux);
      return ERROR;
    }
    element_free(aux);
  }
  return OK;
}
int main(){
  Queue *red=NULL, *blue=NULL;
  Element *el;
  int i;
  if(!(el=element_init()))
    return -1;
  if(!(red=queue_init(element_free, element_copy, element_print))){
    element_free(el);
    return -1;
  }
  if(!(blue=queue_init(element_free, element_copy, element_print))){
    element_free(el);
    queue_free(red);
    return -1;
  }
  /*prueba sin control de errores*/
  element_setInfo(el, "d");
  queue_insert(red, el);
  element_setInfo(el, "e");
  queue_insert(red, el);
  queue_print(stdout, red);
  printf("\n");
  element_setInfo(el, "a");
  queue_insert(blue, el);
  element_setInfo(el, "b");
  queue_insert(blue, el);
  element_setInfo(el, "c");
  queue_insert(blue, el);
  queue_print(stdout, blue);
  printf("\n");
  from_red_to_blue(red, blue);
  queue_print(stdout, blue);
  element_free(el);
  queue_free(red);
  queue_free(blue);
  return 0;
}