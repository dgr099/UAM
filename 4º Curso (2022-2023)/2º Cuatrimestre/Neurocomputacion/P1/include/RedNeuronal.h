#ifndef REDNEURONAL_H
#define REDNEURONAL_H

#include "Capa.h"

using namespace std;

class Capa;

class RedNeuronal{
    private:

    public:
        vector<Capa*> capas;

        RedNeuronal();
        void liberar();
        void aniadir(Capa *capa);
        void disparar();
        void inicializar();
        void propagar();
};

#endif