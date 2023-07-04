#include "../../include/PerceptronMulticapa.h"

PerceptronMulticapa::PerceptronMulticapa(int num_entradas, vector<int> neuronas_ocultas, int num_salidas, float alpha=0.1, int num_epocas=10, float tolerancia=0.1){
    this->alpha = alpha;
    this->num_epocas = num_epocas;
    this->tolerancia = tolerancia;

    this->red = (RedNeuronal *)calloc(1, sizeof(RedNeuronal));
    *(this->red) = RedNeuronal();

    Capa *entrada = crearCapa(0, Directo, num_entradas, true);
    this->red->aniadir(entrada);
    
    for(int num_neuronas: neuronas_ocultas){
        Capa *oculta = crearCapa(0, PercMulti, num_neuronas, true);
        this->red->aniadir(oculta);
    }

    Capa *salida = crearCapa(0, PercMulti, num_salidas, false);
    this->red->aniadir(salida);

    for (unsigned int i = 0; i < this->red->capas.size() - 1; i++){
        this->red->capas[i]->conectar(this->red->capas[i+1], 0.2, 0.2);
    }
}

void PerceptronMulticapa::entrenamiento(vector<vector<float>> x_train, vector<vector<float>> y_train){
    int train_size = x_train.size();
    bool continuarEntrenamiento = true;
    int epoca = this->num_epocas;
    int num_capas = this->red->capas.size();

    while (continuarEntrenamiento && epoca-- > 0){
        continuarEntrenamiento = false;

        for (int i = 0; i < train_size; i++){
            // Inicializar capa entrada
            int j = 0;
            for (float entrada: x_train[i]){
                this->red->capas[0]->neuronas[j++]->valor_entrada = entrada;
            }

            // Feedforward por capa sin inicializar para no perder las entradas de cada neurona
            for (Capa *c: this->red->capas){
                c->disparar();
                c->propagar();
            }

            vector<vector<float>> deltas;       // Contendra todas las deltas obtenidas
            vector<float> errores_salidas;      // Vector con (t-y)
            float delta_k = 0.0, delta_j = 0.0;

            // Calculamos error de las neuronas de salida
            j = num_capas - 1;
            vector<float> deltas_salida;
            unsigned int k = 0;
            for (Neurona *n: this->red->capas[j]->neuronas){
                // Error = (t-y)f'(y_in)
                float diferencia = (y_train[i][k++] - n->valor_salida);
                errores_salidas.push_back(diferencia);
                delta_k = diferencia * derivadaSigmoideBipolar(n->valor_entrada);
                deltas_salida.push_back(delta_k);
                n->inicializar(0);   // Ahora si, reiniciamos valor_entrada
            }
            j--;
            deltas.push_back(deltas_salida);

            // Calculamos error de las neuronas ocultas hacia atras
            float delta_in_j;
            while (j > 0){
                vector<float> deltas_capa_oculta_j;
                for (Neurona *n: this->red->capas[j]->neuronas){
                    if (n->tipo == Sesgo)
                        continue;
                    delta_in_j = 0;
                    k = 0;
                    for (Conexion con: n->conexiones){
                        delta_in_j += con.peso * deltas[num_capas - j - 2][k++];    // Porque se meten al final
                    }
                    delta_j = delta_in_j * derivadaSigmoideBipolar(n->valor_entrada);
                    deltas_capa_oculta_j.push_back(delta_j);
                    n->inicializar(0);   // Ahora si, reiniciamos valor_entrada
                }
                j--;
                deltas.push_back(deltas_capa_oculta_j);
            }

            // Actualizamos pesos de todas las capas salvo la de salida
            for (j = 0; j < num_capas - 1; j++){
                for (Neurona *n: this->red->capas[j]->neuronas){
                    for (k = 0; k != n->conexiones.size(); k++){
                        if(n->tipo != Sesgo) //si no se trata de la bias
                            n->conexiones[k].peso = n->conexiones[k].peso + this->alpha * deltas[num_capas - j - 2][k] * n->valor_salida; //n->valor_salida;
                        else    // BIAS
                            n->conexiones[k].peso = n->conexiones[k].peso + this->alpha * deltas[num_capas - j - 2][k];
                        if (continuarEntrenamiento == false && \
                            calculoEC(errores_salidas) >= this->tolerancia)
                                continuarEntrenamiento = true;
                    }
                }
            }           
        }
    }
}

vector<vector<float>> PerceptronMulticapa::clasificacion(vector<vector<float>> x_test){

    vector<vector<float>> predicciones;
    int test_size = x_test.size();
    int num_capas = this->red->capas.size();

    for (int i = 0; i < test_size; i++){

        // Inicializamos las entradas
        unsigned int j = 0;
        for (float entrada: x_test[i]){
            this->red->capas[0]->neuronas[j++]->valor_entrada = entrada;
        }

        // Feedforward
        for (Capa *c: this->red->capas){
            c->disparar();
            c->inicializar();
            c->propagar();
        }

        // Recogemos las predicciones
        vector<float> pred_patron;
        for (Neurona *n: this->red->capas[num_capas - 1]->neuronas){
            pred_patron.push_back(n->valor_salida);
        }
        predicciones.push_back(pred_patron);
    }

    return predicciones;
}

int main(int argc, char *argv[]){

    int opcion, modoLectura = 0, numFicheros = 0, num_epocas = 10;
    char *nombresFicheros[2];
    float porcentaje = 0.75, tolerancia = 0.1;
    float alpha = rand() % 2;   // Valores entre 0 y 1
    vector<int> neuronas_ocultas {};

    while ((opcion = getopt(argc, argv, "hf:m:p:e:t:a:n:")) != -1){
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

            case 't':
                tolerancia = strtof(optarg, nullptr);
                if (tolerancia <= 0.0)
                    return errorPerceptronAdaline("Argumento de opcion -t invalido", argv[0]);
                break;

            case 'a':
                alpha = strtof(optarg, nullptr);
                if (alpha <= 0.0)
                    return errorPerceptronAdaline("Argumento de opcion -a invalido", argv[0]);
                break;

            case 'n':
                int num_neuronas;
                optind--;
                for( ;optind < argc && *argv[optind] != '-'; optind++){
                    if ((num_neuronas = atoi(argv[optind])) <= 0)
                        return errorPerceptronAdaline("Argumento de opcion -n invalido", argv[0]);
                    neuronas_ocultas.push_back(num_neuronas);
                }
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

            deBinarioABipolar(&y_train);
            deBinarioABipolar(&y_test);

            num_entradas = x_train[0].size(), num_salidas = y_train[0].size();
            PerceptronMulticapa perceptron = PerceptronMulticapa(num_entradas, neuronas_ocultas, num_salidas, alpha, num_epocas, tolerancia);

            perceptron.entrenamiento(x_train, y_train);
            y_preds = perceptron.clasificacion(x_test);

            definirSalidasActivasBipolares(&y_preds);
            vector<vector<bool>> errores_clasificacion = comprobarClasificaciones(y_test, y_preds);
            porcentajeAciertos = calcularAccurate(errores_clasificacion);

            cout << "Accurate = " << porcentajeAciertos << "\n";

            limpiar(perceptron.red);

            break;
        }
        case 2: {
            result = leer2(nombresFicheros[0], &x_train, &y_train);
            if (result == 1){
                printf("Error al abrir el archivo \"%s\"\n", nombresFicheros[0]);
                return 1;
            }

            //deBinarioABipolar(&y_train);
            //deBinarioABipolar(&y_test);

            num_entradas = x_train[0].size(), num_salidas = y_train[0].size();
            PerceptronMulticapa perceptron = PerceptronMulticapa(num_entradas, neuronas_ocultas, num_salidas, alpha, num_epocas, 0.1);

            perceptron.entrenamiento(x_train, y_train);
            y_preds = perceptron.clasificacion(x_train);

            definirSalidasActivasBipolares(&y_preds);

            for (vector<float> v: y_preds){
                for (float f: v){
                    cout << f << " ";
                }
                cout << "\n";
            }

            vector<vector<bool>> errores_clasificacion = comprobarClasificaciones(y_train, y_preds);
            porcentajeAciertos = calcularAccurate(errores_clasificacion);

            //cout << "Accurate = " << porcentajeAciertos << "\n";
            //cout<<"Accurate = ";
            //cout<<fixed<<setprecision(5)<<porcentajeAciertos<<endl;
            //printf("Accurate: %0.5f\n", porcentajeAciertos);

            
            // Para conocer los pesos de la red 
            /*for (Capa *capa: perceptron.red->capas){
                for (Neurona *n: capa->neuronas){
                    for (Conexion c: n->conexiones){
                        cout << c.peso << " ";
                    }
                    cout << "\n";
                }
            }*/
            

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

            deBinarioABipolar(&y_train);
            deBinarioABipolar(&y_test);

            num_entradas = x_train[0].size(), num_salidas = y_train[0].size();
            PerceptronMulticapa perceptron = PerceptronMulticapa(num_entradas, neuronas_ocultas, num_salidas, alpha, num_epocas, 0.1);

            perceptron.entrenamiento(x_train, y_train);
            y_preds = perceptron.clasificacion(x_test);

            definirSalidasActivasBipolares(&y_preds);
            
            vector<vector<bool>> errores_clasificacion = comprobarClasificaciones(y_test, y_preds);
            porcentajeAciertos = calcularAccurate(errores_clasificacion);

            /*
            cout<<"Accurate = ";
            cout<<fixed<<setprecision(5)<<porcentajeAciertos<<endl;

            // Para conocer los pesos de la red 
            for (Capa *capa: perceptron.red->capas){
                for (Neurona *n: capa->neuronas){
                    for (Conexion c: n->conexiones){
                        cout << c.peso << " ";
                    }
                    cout << "\n";
                }
            }
            cout<<"Predictions: \n";
            */
            for(vector<float> aux:y_preds){
                for(float pred : aux){
                    cout<<pred<<" ";
                }
                cout<<"\n";
            }

            limpiar(perceptron.red);

            break;
        }
        default:
            return errorPerceptronAdaline("Indica el modo de lectura a utilizar", argv[0]);
    }

    return 0;
}