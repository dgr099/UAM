#include "../../include/lecturaPatrones.h"

int leerFichero(const char *nombre_fichero, \
    int *num_atributos, int *num_clases, int *num_patrones, vector<vector<float>> *patrones){
    
    int tam_patron;
    ifstream fichero(nombre_fichero);

    if (!fichero.is_open())
        return 1;

    fichero >> *num_atributos;
    fichero >> *num_clases;
    tam_patron = *num_atributos + *num_clases;

    float valor;
    vector<float> patron;

    *num_patrones = 0;
    for (int i = 0; fichero >> valor; i = (i + 1) % tam_patron){
        patron.push_back(valor);
        if (i + 1 == tam_patron){
            patrones->push_back(patron);
            patron.clear();
            (*num_patrones)++;
        }
    }

    return 0;
}

int leer1(const char *nombre_fichero, float porcentaje, \
    vector<vector<float>> *x_train, vector<vector<float>> *y_train, \
    vector<vector<float>> *x_test, vector<vector<float>> *y_test){

        vector<vector<float>> patrones;
        int num_atributos, num_clases, num_patrones;

        if (leerFichero(nombre_fichero, &num_atributos, &num_clases, &num_patrones, &patrones) == 1)
            return 1;

        // Para randomizar los patrones de entrenamiento y test, 
        // hacemos swaps aleatorios en la lista de indices y
        // los n primeros seran para train y el resto para test
        int *indices = (int *)malloc(num_patrones * sizeof(int));
        if (!indices){
            printf("Error al reservar memoria\n");
            return 2;
        }

        for(int i = 0; i < num_patrones; i++){
            indices[i] = i;
        }

        for (int a, b, aux, i = 0; i < num_patrones; i++){
            a = rand() % num_patrones;
            b = rand() % num_patrones;
            aux = indices[a];
            indices[a] = indices[b];
            indices[b] = aux;
        }

        float tam_train = num_patrones * porcentaje - 0.5;  // -0.5 para hacer un redondeo con el bucle siguiente
        int i, j;
        for (i = 0; i < tam_train; i++){
            vector<float> xy;
            for (j = 0; j < num_atributos; j++){
                xy.push_back(patrones[indices[i]][j]);
            }
            
            x_train->push_back(xy);
            vector<float> xy2;
            for (; j < num_atributos + num_clases; j++){
                xy2.push_back(patrones[indices[i]][j]);
            }
            y_train->push_back(xy2);
        }
        for (; i < num_patrones; i++){
            vector<float> xy;
            for (j = 0; j < num_atributos; j++){
                xy.push_back(patrones[indices[i]][j]);
            }
            x_test->push_back(xy);
            vector<float> xy2;
            for (; j < num_atributos + num_clases; j++){
                xy2.push_back(patrones[indices[i]][j]);
            }
            y_test->push_back(xy2);
        }

        free(indices);

        return 0;
}

int leer2(const char *nombre_fichero, vector<vector<float>> *x_datos, vector<vector<float>> *y_datos){

    vector<vector<float>> patrones;
    int num_atributos, num_clases, num_patrones;

    if (leerFichero(nombre_fichero, &num_atributos, &num_clases, &num_patrones, &patrones) == 1)
        return 1;
    
    vector<float> xy;
    for (int i = 0; i < num_patrones; i++){
        int j;
        for (j = 0; j < num_atributos; j++){
            xy.push_back(patrones[i][j]);
        }
        x_datos->push_back(xy);
        xy.clear();
        for (; j < num_atributos + num_clases; j++){
            xy.push_back(patrones[i][j]);
        }
        y_datos->push_back(xy);
        xy.clear();
    }

    return 0;
}

int leer3(const char *nombre_fichero_train, const char *nombre_fichero_test, \
    vector<vector<float>> *x_train, vector<vector<float>> *y_train, \
    vector<vector<float>> *x_test, vector<vector<float>> *y_test){

    if (leer2(nombre_fichero_train, x_train, y_train) == 1)
        return 1;
    if (leer2(nombre_fichero_test, x_test, y_test) == 1)
        return 2;
    return 0;
}

void printRows(vector<vector<float>> v){
    for (vector<float> b: v){
        for (float c: b){
            printf("%.2f ", c);
        }
        cout << "\n";
    }
}

/*
int main(){

    string fichero = "./data/and.txt";
    string fichero2 = "./data/or.txt";
    vector<vector<float>> xtr, ytr, xte, yte;
    vector<vector<float>> x, y;
    int modo = 3, result;

    srand(time(0));

    switch(modo){
        case 1:        
            cout << "Leyendo en modo 1...\n";    
            result = leer1(fichero.c_str(), 0.3, &xtr, &ytr, &xte, &yte);
            if (result == 1){
                printf("Error al abrir el archivo \"%s\"\n", fichero.c_str());
                return 1;
            } else if (result == 2){
                printf("Error al reservar memoria\n");
                return 1;
            }

            cout << "\nx_train:\n"; printRows(xtr);
            cout << "\ny_train:\n"; printRows(ytr);
            cout << "\nx_test:\n"; printRows(xte);
            cout << "\ny_test:\n"; printRows(yte);
            break;

        case 2:
            cout << "Leyendo en modo 2...\n";
            result = leer2(fichero.c_str(), &x, &y);
            if (result == 1){
                printf("Error al abrir el archivo \"%s\"\n", fichero.c_str());
                return 1;
            }

            cout << "\nx_data:\n"; printRows(x);
            cout << "\ny_data:\n"; printRows(y);
            break;

        case 3:
            cout << "Leyendo en modo 3...\n";
            result = leer3(fichero.c_str(), fichero2.c_str(), &xtr, &ytr, &xte, &yte);
            if (result == 1){
                printf("Error al abrir el archivo \"%s\"\n", fichero.c_str());
                return 1;
            } else if (result == 2){
                printf("Error al abrir el archivo \"%s\"\n", fichero2.c_str());
                return 1;
            }

            cout << "\nx_train:\n"; printRows(xtr);
            cout << "\ny_train:\n"; printRows(ytr);
            cout << "\nx_test:\n"; printRows(xte);
            cout << "\ny_test:\n"; printRows(yte);
            break;
        
        default:
            break;
    }
    
    return 0;
}
*/