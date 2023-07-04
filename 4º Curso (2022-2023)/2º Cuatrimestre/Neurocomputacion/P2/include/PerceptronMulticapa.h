#ifndef PERCEPTRONMULTICAPA_H
#define PERCEPTRONMULTICAPA_H

#include "lecturaPatrones.h"
#include "utils.h"

#include <unistd.h>
#include <iomanip>
#include <algorithm>

class PerceptronMulticapa{
    private:

    public:
        RedNeuronal *red;
        float alpha;
        int num_epocas;
        float tolerancia;
        float umbral;

        PerceptronMulticapa(int num_entradas, vector<int> neuronas_ocultas, int num_salidas, float alpha, int num_epocas, float tolerancia);
        void entrenamiento(vector<vector<float>> x_train, vector<vector<float>> y_train);
        vector<vector<float>> clasificacion(vector<vector<float>> x_test);
};

#endif