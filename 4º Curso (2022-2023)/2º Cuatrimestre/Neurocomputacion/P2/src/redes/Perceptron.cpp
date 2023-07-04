#include "../../include/Perceptron.h"

Perceptron::Perceptron(int num_entradas, int num_salidas, float alpha=0.1, int num_epocas=10, float tolerancia=0.1, float umbral=0.5){
    this->alpha = alpha;
    this->num_epocas = num_epocas;
    this->tolerancia = tolerancia;
    this->umbral = umbral;

    this->red = (RedNeuronal *)calloc(1, sizeof(RedNeuronal));
    *(this->red) = RedNeuronal();

    Capa *entrada = crearCapa(umbral, Directo, num_entradas, true);
    Capa *salida = crearCapa(umbral, Percept, num_salidas, false);

    this->red->aniadir(entrada);
    this->red->aniadir(salida);

    entrada->conectar(salida, 0, 0);
}

void Perceptron::entrenamiento(vector<vector<float>> x_train, vector<vector<float>> y_train){
    int train_size = x_train.size();
    bool continuarEntrenamiento = true;
    int epoca = this->num_epocas;
    unsigned int num_neuronas_capa_entrada = this->red->capas[0]->neuronas.size();

    while (continuarEntrenamiento && epoca--){
        continuarEntrenamiento = false;
        for (int i = 0; i < train_size; i++){
            // Inicializar capa entrada (incluido BIAS - mirar lecturaFicheros.cpp)
            unsigned int j = 0;
            for (float entrada: x_train[i]){
                this->red->capas[0]->neuronas[j++]->valor_entrada = entrada;
            }

            // Feedforward
            for (int capas = this->red->capas.size(); capas > 0; capas--){
                this->red->disparar();
                this->red->inicializar();
                this->red->propagar();
            }

            // Recogemos las salidas
            vector<float> y;
            for (Neurona *n: this->red->capas[1]->neuronas){
                y.push_back(n->valor_salida);
            }

            // Actualizamos pesos si t != y y comprobamos si hay que seguir entrenando
            j = 0;
            for (Neurona *n: this->red->capas[0]->neuronas){
                for (int k = 0; k < (int)n->conexiones.size(); k++){
                    if (i == 0)
                        n->conexiones[k].peso_anterior = n->conexiones[k].peso;
                    if (y_train[i][k] != y[k]){
                        if (j + 1 != num_neuronas_capa_entrada)
                            n->conexiones[k].peso += this->alpha * x_train[i][j] * y_train[i][k];
                        else
                            n->conexiones[k].peso += this->alpha * y_train[i][k];
                    }
                    if (i + 1 == train_size && continuarEntrenamiento == false && \
                        n->conexiones[k].peso_anterior != n->conexiones[k].peso)
                            continuarEntrenamiento = true;
                }
                j++;
            }
        }
    }
}

vector<vector<float>> Perceptron::clasificacion(vector<vector<float>> x_test){

    vector<vector<float>> predicciones;
    int test_size = x_test.size();

    for (int i = 0; i < test_size; i++){

        // Inicializamos las entradas
        unsigned int j = 0;
        for(Neurona *n: this->red->capas[0]->neuronas){
            if(j<x_test[i].size())
                n->valor_entrada = x_test[i][j++];
        }

        // Feedforward
        for (int capas = this->red->capas.size(); capas > 0; capas--){
            this->red->disparar();
            this->red->inicializar();
            this->red->propagar();
        }

        // Recogemos las predicciones
        vector<float> pred_patron;
        for (Neurona *n: this->red->capas[1]->neuronas){
            pred_patron.push_back(n->valor_salida);
        }
        predicciones.push_back(pred_patron);
    }

    return predicciones;
}

int main(int argc, char *argv[]){

    int opcion, modoLectura = 0, numFicheros = 0, num_epocas = 10;
    char *nombresFicheros[2];
    float porcentaje = 0.75, tolerancia = 0.1, umbral = 0.5;
    float alpha = rand() % 2;   // Valores entre 0 y 1

    while ((opcion = getopt(argc, argv, "hf:m:p:e:a:u:")) != -1){
        switch(opcion){
            case 'm':
                modoLectura = atoi(optarg);
                if (modoLectura < 1 || modoLectura > 3)
                    return errorPerceptronAdaline("Argumento de opcion -m invalido", argv[0]);
                break;
            
            case 'f':
                nombresFicheros[numFicheros++] = optarg;
                break;

            case 'p':
                porcentaje = strtof(optarg, nullptr);
                if (porcentaje < 0.0 || porcentaje > 1.0)
                    return errorPerceptronAdaline("Argumento de opcion -p invalido", argv[0]);
                break;

            case 'e':
                num_epocas = atoi(optarg);
                if (num_epocas < 1)
                    return errorPerceptronAdaline("Argumento de opcion -e invalido", argv[0]);
                break;

            case 'a':
                alpha = strtof(optarg, nullptr);
                if (alpha <= 0.0)
                    return errorPerceptronAdaline("Argumento de opcion -a invalido", argv[0]);
                break;

            case 'u':
                umbral = strtof(optarg, nullptr);
                if (umbral <= 0.0)
                    return errorPerceptronAdaline("Argumento de opcion -u invalido", argv[0]);
                break;

            case 'h':
                printf("\nAYUDA:\n");
            default:
                printArgs(argv[0]);
                return 0;
        }
    }

    if (numFicheros == 0)
        return errorPerceptronAdaline("Indica los ficheros a utilizar", argv[0]);
    else if (modoLectura == 1 && porcentaje == 0.0)
        return errorPerceptronAdaline("El modo lectura 1 necesita un porcentaje de entrenamiento", argv[0]);
    else if (modoLectura == 3 && numFicheros < 2)
        return errorPerceptronAdaline("El modo lectura 2 necesita dos ficheros", argv[0]);

    srand(time(0));

    vector<vector<float>> x_train, y_train, x_test, y_test;     // En modo 2 solo usamos train
    vector<vector<float>> y_preds;
    float porcentajeAciertos;
    int num_entradas, num_salidas, result;

    switch(modoLectura){
        case 1: {
            result = leer1(nombresFicheros[0], porcentaje, &x_train, &y_train, &x_test, &y_test);
            if (result == 1){
                printf("Error al abrir el archivo \"%s\"\n", nombresFicheros[0]);
                return 1;
            } else if (result == 2){
                printf("Error al reservar memoria\n");
                return 1;
            }

            num_entradas = x_train[0].size(), num_salidas = y_train[0].size();
            Perceptron perceptron = Perceptron(num_entradas, num_salidas, alpha, num_epocas, tolerancia);

            perceptron.entrenamiento(x_train, y_train);
            y_preds = perceptron.clasificacion(x_test);

            vector<vector<bool>> errores_clasificacion = comprobarClasificaciones(y_test, y_preds);
            porcentajeAciertos = calcularAccurate(errores_clasificacion);

            cout << "Accurate = " << porcentajeAciertos << "\n";

            limpiar(perceptron.red);

            break;
        }
        case 2: {
            result = leer2(nombresFicheros[0], &x_train, &y_train);
            if (result == 1){
                printf("Error al abrir el archivo \"%s\"\n", nombresFicheros[1]);
                return 1;
            }

            num_entradas = x_train[0].size(), num_salidas = y_train[0].size();
            Perceptron perceptron = Perceptron(num_entradas, num_salidas, alpha, num_epocas, 0.1);

            perceptron.entrenamiento(x_train, y_train);
            y_preds = perceptron.clasificacion(x_train);

            vector<vector<bool>> errores_clasificacion = comprobarClasificaciones(y_train, y_preds);
            porcentajeAciertos = calcularAccurate(errores_clasificacion);

            //cout << "Accurate = " << porcentajeAciertos << "\n";
            cout<<"Accurate = ";
            cout<<fixed<<setprecision(5)<<porcentajeAciertos<<endl;
            //printf("Accurate: %0.5f\n", porcentajeAciertos);

            
            // Para conocer los pesos de la red 
            for (Capa *capa: perceptron.red->capas){
                for (Neurona *n: capa->neuronas){
                    for (Conexion c: n->conexiones){
                        cout << c.peso << " ";
                    }
                    cout << "\n";
                }
            }
            

            limpiar(perceptron.red);

            break;
        }
        case 3: {
            result = leer3(nombresFicheros[0], nombresFicheros[1], &x_train, &y_train, &x_test, &y_test);
            if (result == 1){
                printf("Error al abrir el archivo \"%s\"\n", nombresFicheros[0]);
                return 1;
            } else if (result == 2){
                printf("Error al abrir el archivo \"%s\"\n", nombresFicheros[1]);
                return 1;
            }

            num_entradas = x_train[0].size(), num_salidas = y_train[0].size();
            Perceptron perceptron = Perceptron(num_entradas, num_salidas, alpha, num_epocas, 0.1);

            perceptron.entrenamiento(x_train, y_train);
            y_preds = perceptron.clasificacion(x_test);

            vector<vector<bool>> errores_clasificacion = comprobarClasificaciones(y_test, y_preds);
            porcentajeAciertos = calcularAccurate(errores_clasificacion);

            cout<<"Accurate = ";
            cout<<fixed<<setprecision(5)<<porcentajeAciertos<<endl;

            /*// Para conocer los pesos de la red 
            for (Capa *capa: perceptron.red->capas){
                for (Neurona *n: capa->neuronas){
                    for (Conexion c: n->conexiones){
                        cout << c.peso << " ";
                    }
                    cout << "\n";
                }
            }
            cout<<"Predictions: \n";
            for(vector<float> aux:y_preds){
                for(float pred : aux){
                    cout<<pred<<" ";
                }
                cout<<"\n";
            }*/

            limpiar(perceptron.red);

            break;
        }
        default:
            return errorPerceptronAdaline("Indica el modo de lectura a utilizar", argv[0]);
    }

    return 0;
}