#include "../../include/Capa.h"

Capa::Capa(){
}

void Capa::liberar(){
    for(Neurona* n: neuronas){
        n->liberar();
        free(n);
        //delete n;
    }
    vector<Neurona*>().swap(neuronas);
    //neuronas.clear();
}

void Capa::aniadir(Neurona *neurona){
    neuronas.push_back(neurona);
}

void Capa::conectar(Capa *capa, float peso_min, float peso_max){
    for (Neurona *n: capa->neuronas){
        //conectar(n, peso_min, peso_max);
        for (Neurona *n2: this->neuronas){
            // Generamos peso aleatorio entre los pesos dados
            float peso = peso_min + (((float) rand()) / (float) RAND_MAX) * (peso_max - peso_min);
            n2->conectar(n, peso);
    }
    }
}

void Capa::conectar(Neurona *neurona, float peso_min, float peso_max){
    for (Neurona *n: this->neuronas){
        // Generamos peso aleatorio entre los pesos dados
        float peso = peso_min + (((float) rand()) / (float) RAND_MAX) * (peso_max - peso_min);
        n->conectar(neurona, peso);
    }
}

void Capa::disparar(){
    for (Neurona *n: neuronas){
        n->disparar();
    }
}

void Capa::inicializar(){
    for (Neurona *n: neuronas){
        n->inicializar(0);
    }
}

void Capa::propagar(){
    for (Neurona *n: neuronas){
        n->propagar();
    }
}