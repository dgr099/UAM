#ifndef NEURONA_H
#define NEURONA_H

#include <iostream>
#include <vector>

#include "Conexion.h"

using namespace std;

class Conexion;

enum Tipo {Directo, Sesgo, McCulloch, AdaLiNe, Percept, PercMulti};

class Neurona{
    private:

    public:
        float umbral;
        Tipo tipo;
        float valor_salida;
        vector<Conexion> conexiones; // Probamos con vector, si problemas => cambiar a array de punteros a conexion

        float valor_entrada;
        
        Neurona(float umbral, Tipo tipo);
        void liberar();
        void conectar(Neurona* neurona, float peso);
        void disparar();
        void inicializar(float entrada);
        void propagar();
};

#endif