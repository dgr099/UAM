#include "../../include/utils.h"

void definirSalidasActivasBipolares(vector<vector<float>> *salidas_patrones){
    int num_patrones = (*salidas_patrones).size();
    int num_salidas = (*salidas_patrones)[0].size();
    int max_indice;

    if (num_salidas > 1){
        for (int i = 0; i < num_patrones; i++){
            max_indice = 0;
            for (int j = 1; j < num_salidas; j++){  // Suponer primer valor como maximo
                if ((*salidas_patrones)[i][j] > (*salidas_patrones)[i][max_indice]){    // Si hay algun valor mayor
                    (*salidas_patrones)[i][max_indice] = -1;                            // sabemos que el antiguo va a ser -1
                    max_indice = j;
                }
                else    // Sino simplemente no es el maximo
                    (*salidas_patrones)[i][j] = -1;
            }
            (*salidas_patrones)[i][max_indice] = 1;    // El que quede como maximo sera el 1
        }
    } else if (num_salidas == 1){
        for (int i = 0; i < num_patrones; i++){
            if ((*salidas_patrones)[i][0] >= 0)
                (*salidas_patrones)[i][0] = 1;
            else    // Sino simplemente no es el maximo
                (*salidas_patrones)[i][0] = -1;
        }
    }
}

void deBinarioABipolar(vector<vector<float>> *vectores_binarios){
    int num_vectores = (*vectores_binarios).size();

    for (int i = 0; i < num_vectores; i++){
        int tam_vector = (*vectores_binarios)[i].size();
        for (int j = 0; j < tam_vector; j++)
            (*vectores_binarios)[i][j] = 2 * (*vectores_binarios)[i][j] - 1;
    }
}

float calculoEC(vector<float> diferencias){
    float suma = 0;
    int num_salidas = diferencias.size();
    for(int i = 0; i < num_salidas; i++){
        suma += pow(diferencias[i], 2);
    }
    return 0.5 * suma;
}

float derivadaSigmoideBipolar(float x){
    float sigmoid = sigmoideBipolar(x);
    return 0.5 * (1 + sigmoid) * (1 - sigmoid);
    //return (1 - pow(sigmoideBipolar(x), 2)) / 2;
}

float sigmoideBipolar(float x){
    return 2 / (1 + exp(-x)) - 1;
}

Capa *crearCapa(float umbral, enum Tipo tipo, int num_neuronas, bool hasBias){
    Capa *c = (Capa *)calloc(1, sizeof(Capa));
    *c = Capa();
    while (num_neuronas--){
        Neurona *n = (Neurona *)calloc(1, sizeof(Neurona));
        *n = Neurona(umbral, tipo);
        c->aniadir(n);
    }
    if (hasBias){
        Neurona *n = (Neurona *)calloc(1, sizeof(Neurona));
        *n = Neurona(umbral, Sesgo);
        c->aniadir(n);
    }

    return c;
}

vector<vector<bool>> comprobarClasificaciones(vector<vector<float>> y_test, vector<vector<float>> y_preds){
    vector<vector<bool>> errores_patrones;
    vector<bool> errores_patron;
    int num_tests = y_test.size(), num_salidas = y_test[0].size();

    for (int i = 0; i < num_tests; i++){
        for (int j = 0; j < num_salidas; j++){
            errores_patron.push_back(y_test[i][j] == y_preds[i][j]);
        }
        errores_patrones.push_back(errores_patron);
        errores_patron.clear();
    }

    return errores_patrones;
}

float calcularAccurate(vector<vector<bool>> errores){
    int num_clasificaciones = errores.size() * errores[0].size();
    float num_aciertos = 0;
    for (vector<bool> errores_patron: errores){
        for (bool is_acierto: errores_patron){
            if (is_acierto)
                num_aciertos++;
        }
    } 
    return num_aciertos / num_clasificaciones;
}

void limpiar(RedNeuronal *red){
    red->liberar();
    free(red);
}

void printArgs(char *exe_name){
    printf("Sintaxis: %s -[hf:m:p:e:t:a:u:]\n", exe_name);
    printf("\t-m: Modo de lectura de los ficheros [1-3]\n");
    printf("\t-f: Acompañado por un nombre de fichero\n");
    printf("\t-p: En modo 1, porcentaje de patrones para entrenamiento [0.0-1.0]\n");
    printf("\t-e: Numero de epocas\n");
    printf("\t-t: NO PERCEPTRON. Tolerancia al cambio de pesos para el entrenamiento (>0.0)\n");
    printf("\t-a: Constante de aprendizaje \"alpha\" (>0.0)\n");
    printf("\t-u: NO ADALINE. Umbral de la funcion de activacion (>0.0)\n");
    printf("\t-n: SOLO PERCEPTRON MULTICAPA. Vector de numero de neuronas de cada capa oculta (>0)\n");
    printf("\t-h: Ayuda\n");
}

int errorPerceptronAdaline(string error_string, char *exe_name){
    printf("ERROR: %s\n", error_string.c_str());
    printArgs(exe_name);
    return -1;
}