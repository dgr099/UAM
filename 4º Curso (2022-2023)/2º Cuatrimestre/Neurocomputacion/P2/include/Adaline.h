#ifndef ADALINE_H
#define ADALINE_H

#include "lecturaPatrones.h"
#include "utils.h"

#include <unistd.h>
#include <cmath>
#include <iomanip>

class Adaline{
    private:

    public:
        RedNeuronal *red;
        float alpha;
        int num_epocas;
        float tolerancia;

        Adaline(int num_entradas, int num_salidas, float alpha, int num_epocas, float tolerancia);
        void entrenamiento(vector<vector<float>> x_train, vector<vector<float>> y_train);
        vector<vector<float>> clasificacion(vector<vector<float>> x_test);
};

#endif