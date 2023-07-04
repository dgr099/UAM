#include "../../include/Conexion.h"

Conexion::Conexion(float peso, Neurona *neurona){
    this->peso = peso;
    this->neurona = neurona;
    this->peso_anterior = peso;
}

void Conexion::liberar(){
}