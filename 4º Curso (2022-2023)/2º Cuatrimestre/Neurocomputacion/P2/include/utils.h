#ifndef UTILS_H
#define UTILS_H

#include "RedNeuronal.h"

#include <cmath>

void definirSalidasActivasBipolares(vector<vector<float>> *salidas_patrones);
void deBinarioABipolar(vector<vector<float>> *vectores_binarios);
float calculoEC(vector<float> diferencias);
float derivadaSigmoideBipolar(float x);
float sigmoideBipolar(float x);
Capa *crearCapa(float umbral, enum Tipo tipo, int num_neuronas, bool hasBias);
vector<vector<bool>> comprobarClasificaciones(vector<vector<float>> y_test, vector<vector<float>> y_preds);
float calcularAccurate(vector<vector<bool>> errores);
void limpiar(RedNeuronal *red);
void printArgs(char *exe_name);
int errorPerceptronAdaline(string errorString, char *exeName);

#endif