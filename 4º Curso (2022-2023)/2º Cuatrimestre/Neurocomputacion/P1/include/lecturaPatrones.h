#ifndef LECTURAPATRONES_H
#define LECTURAPATRONES_H

#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

int leer1(const char *nombre_fichero, float porcentaje, \
    vector<vector<float>> *x_train, vector<vector<float>> *y_train, \
    vector<vector<float>> *x_test, vector<vector<float>> *y_test);

int leer2(const char *nombre_fichero, vector<vector<float>> *x_datos, vector<vector<float>> *y_datos);

int leer3(const char *nombre_fichero_train, const char *nombre_fichero_test, \
    vector<vector<float>> *x_train, vector<vector<float>> *y_train, \
    vector<vector<float>> *x_test, vector<vector<float>> *y_test);

#endif