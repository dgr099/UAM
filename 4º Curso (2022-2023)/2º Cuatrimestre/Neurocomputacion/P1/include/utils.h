#ifndef UTILS_H
#define UTILS_H

#include "RedNeuronal.h"

Capa *crearCapa(float umbral, enum Tipo tipo, int num_neuronas, bool hasBias);
vector<vector<bool>> comprobarClasificaciones(vector<vector<float>> y_test, vector<vector<float>> y_preds);
float calcularAccurate(vector<vector<bool>> errores);
void limpiar(RedNeuronal *red);
int errorPerceptronAdaline(string errorString, char *exeName);

#endif