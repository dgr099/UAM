#ifndef CONEXION_H
#define CONEXION_H

#include "Neurona.h"

using namespace std;

class Neurona;

class Conexion{
    private:
        
    public:
        float peso_anterior;

        float peso;
        Neurona *neurona;
        
        Conexion(float peso, Neurona *neurona);
        void liberar();
};

#endif