#ifndef CAPA_H
#define CAPA_H

#include <cstdlib>

#include "Neurona.h"

using namespace std;

class Neurona;

class Capa{
    private:

    public:
        vector<Neurona*> neuronas;

        Capa();
        void liberar();
        void aniadir(Neurona *neurona);
        void conectar(Capa *capa, float peso_min, float peso_max);
        void conectar(Neurona *neurona, float peso_min, float peso_max);
        void disparar();
        void inicializar();
        void propagar();
};

#endif