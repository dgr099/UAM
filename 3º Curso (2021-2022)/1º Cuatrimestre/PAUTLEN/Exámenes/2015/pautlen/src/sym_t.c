#include "sym_t.h"
#include "sym_info.h"

#define SIZE_T_GLOBAL 400
#define SIZE_T_LOCAL 400

static sym_t *tabla = NULL;

/* INICIALIZAR TABLA DE SIMBOLOS */
sym_t *sym_t_create()
{
    /*usas una tabla de símbolos*/
    if((tabla = (sym_t*)malloc(1*sizeof(sym_t)))==NULL){
        return NULL;
    }
    if((tabla->symbolsGlobal = (char**)calloc(SIZE_T_GLOBAL, sizeof(char*)))==NULL){
        free(tabla);
        return NULL;
    }
    /*inicializas el hash de global*/
    tabla->tabla_global = hash_create(SIZE_T_GLOBAL);
    /*retorna la dirección de la tabla creada*/
    tabla->tabla_local = NULL;
    tabla->symbolsLocal = NULL;
    tabla->tamG=0;
    tabla->tamL=0;
    return tabla;
}

char **sym_t_getLocalSymbols(){
    return tabla->symbolsLocal;
}

char **sym_t_getGlobalSymbols(){
    return tabla->symbolsGlobal;
}

void sym_t_free()
{
    if(!tabla){
        return;
    }
    if(tabla->tabla_local){
        hash_free(tabla->tabla_local);
        for(int i=0; tabla->symbolsLocal[i]!=NULL; i++){
            free(tabla->symbolsLocal[i]);
        }
        free(tabla->symbolsLocal);
    }
    hash_free(tabla->tabla_global);
    for(int i=0; tabla->symbolsGlobal[i]!=NULL; i++){
        free(tabla->symbolsGlobal[i]);
    }
    free(tabla->symbolsGlobal);
    free(tabla);
}

int sym_t_add_symb(sym_info *sym)
{
    char *key=NULL;
    if(!tabla || !sym || sym_t_check(sym->lexema)!=NULL ){
        return -1;
    }
    if((key=(char*)calloc(strlen(sym->lexema)+1,sizeof(char)))==NULL){
        return -1;
    }
    if(strcpy(key, sym->lexema)==0){
        free(key);
        return -1;
    }
    /*primero compruebo si hay tabla local*/
    if(tabla->tabla_local){
        sym->is_var_loc=1;
        hash_set(tabla->tabla_local, sym->lexema, sym);
        if(tabla->symbolsLocal!=NULL){
            tabla->symbolsLocal[tabla->tamL]=key;
            sym->pos_param=tabla->tamL;
            tabla->tamL++;
        }
        return 0;
    }
    else if(tabla->tabla_global){
            hash_set(tabla->tabla_global, sym->lexema, sym);
            tabla->symbolsGlobal[tabla->tamG]=key;
            tabla->tamG++;
            return 0;
        }
    return -1;
}

sym_info* sym_t_get_symb_local(char *id){
    if(!id || !tabla){
        return NULL;
    }
    if(tabla->tabla_global){
        return(hash_get(tabla->tabla_global, id));
    }else{
        return NULL;
    }
}

sym_info* sym_t_get_symb(char *id)
{
    sym_info *valor=NULL;
    if(!id || !tabla){
        return NULL;
    }
    if(tabla->tabla_local){
        if((valor=hash_get(tabla->tabla_local, id))!=NULL){
            return valor;
        }
    }
    if(tabla->tabla_global){
        return(hash_get(tabla->tabla_global, id));
    }else{
        return NULL;
    }
}

sym_info* sym_t_check(char *id)
{
    if(!id || !tabla){
        return NULL;
    }
    if(tabla->tabla_local){
        return(hash_get(tabla->tabla_local, id));
    }
    else if(tabla->tabla_global){
        return(hash_get(tabla->tabla_global, id));
    }else{
        return NULL;
    }
}

void open_scope(char* key, int value, Tipo tipo){
    if(!tabla){
        return;
    }
    if((tabla->symbolsLocal = (char**)calloc(SIZE_T_LOCAL, sizeof(char*)))==NULL){
        return;
    }
    sym_info *info1 = sym_info_create(key, FUNCION, tipo, ESCALAR, -1, -1); //int y escalar está x poner
    info1->valor=value;
    tabla->tabla_local = hash_create(SIZE_T_LOCAL);
    //insertamos simbolo tanto en tabla local como global
    hash_set(tabla->tabla_global, info1->lexema, info1);
    hash_set(tabla->tabla_local, info1->lexema, info1);

}

void close_scope(){
    if(!tabla || !tabla->tabla_local)
        return;
    hash_free(tabla->tabla_local);
    if(tabla->symbolsLocal){
        for(int i=0; tabla->symbolsLocal[i]!=NULL; i++){
            free(tabla->symbolsLocal[i]);
        }
        free(tabla->symbolsLocal);
    }
    tabla->symbolsLocal=NULL;
    tabla->tamL=0;
    tabla->tabla_local = NULL;
    return;
}