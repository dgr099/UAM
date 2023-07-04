#include "../../include/Neurona.h"
#include "../../include/utils.h"

Neurona::Neurona(float umbral, Tipo tipo){  // Crear
    this->umbral = umbral;
    this->tipo = tipo;
    this->valor_entrada = 0;
    this->valor_salida = 0;
}

void Neurona::liberar(){ 
    
    for(Conexion c: conexiones){
        c.liberar();    
    }
    vector<Conexion>().swap(conexiones);
}

void Neurona::conectar(Neurona *neurona, float peso){
    Conexion conexion = Conexion(peso, neurona);
    conexiones.push_back(conexion);
}

void Neurona::disparar(){
    switch(this->tipo){
        case Directo:
            this->valor_salida = this->valor_entrada;
            break;
        case Sesgo:
            this->valor_salida = 1.0;
            break;
        case McCulloch:
            this->valor_salida = this->valor_entrada >= this->umbral ? 1 : 0;
            break;
        case AdaLiNe:
            this->valor_salida = this->valor_entrada >= this->umbral ? 1 : -1;
            break;
        case Percept:
            if (this->valor_entrada <= this->umbral && this->valor_entrada >= - this->umbral)
                this->valor_salida = 0;
            else
                this->valor_salida = this->valor_entrada > this->umbral ? 1 : -1;
            break;
        case PercMulti:
            this->valor_salida = sigmoideBipolar(this->valor_entrada);
            break;
        default:
            this->valor_salida = 0.0;
    }
}

void Neurona::inicializar(float entrada){
    this->valor_entrada = entrada;
}

void Neurona::propagar(){
    for(Conexion c: conexiones){
        c.neurona->inicializar(c.neurona->valor_entrada + c.peso * this->valor_salida);
    }
}