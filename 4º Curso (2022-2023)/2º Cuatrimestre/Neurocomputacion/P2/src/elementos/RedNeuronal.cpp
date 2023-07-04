#include "../../include/RedNeuronal.h"

RedNeuronal::RedNeuronal(){
}

void RedNeuronal::liberar(){
    for(Capa *c: capas){
        c->liberar();
        free(c);
    }
    vector<Capa*>().swap(capas);
}

void RedNeuronal::aniadir(Capa *capa){
    this->capas.push_back(capa);
}

void RedNeuronal::disparar(){
    for (Capa *c: capas){
        c->disparar();
    }
}

void RedNeuronal::inicializar(){
    for (Capa *c: capas){
        c->inicializar();
    }
}

void RedNeuronal::propagar(){
    for (Capa *c: capas){
        c->propagar();
    }
}