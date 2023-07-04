#include "../../include/utils.h"

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

int errorPerceptronAdaline(string error_string, char *exe_name){
    printf("ERROR: %s\n", error_string.c_str());
    printf("Sintaxis: %s -[hf:m:p:e:t:a:u:]\n", exe_name);
    printf("\t-m: Modo de lectura de los ficheros [1-3]\n");
    printf("\t-f: Acompañado por un nombre de fichero\n");
    printf("\t-p: En modo 1, porcentaje de patrones para entrenamiento [0.0-1.0]\n");
    printf("\t-e: Numero de epocas\n");
    printf("\t-t: Tolerancia al cambio de pesos para el entrenamiento (>0.0)\n");
    printf("\t-a: Constante de aprendizaje \"alpha\" (>0.0)\n");
    printf("\t-u: Umbral de la funcion de activacion (>0.0)\n");
    printf("\t-h: Ayuda\n");
    return -1;
}