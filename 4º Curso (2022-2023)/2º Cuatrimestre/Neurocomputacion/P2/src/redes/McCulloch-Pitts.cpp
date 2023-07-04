#include "../../include/RedNeuronal.h"
#include <unistd.h>

void inicializacion(RedNeuronal *mp){
    
    int umbral = 2;

    Capa *entrada = (Capa *)calloc(1, sizeof(Capa));   *entrada = Capa();
    Capa *oculta = (Capa *)calloc(1, sizeof(Capa));    *oculta = Capa();
    Capa *salida = (Capa *)calloc(1, sizeof(Capa));    *salida = Capa();

    Neurona *I = (Neurona *)calloc(1, sizeof(Neurona));    *I = Neurona(umbral, Directo);
    Neurona *D = (Neurona *)calloc(1, sizeof(Neurona));    *D = Neurona(umbral, Directo);

    Neurona *N1 = (Neurona *)calloc(1, sizeof(Neurona));    *N1 = Neurona(umbral, McCulloch);
    Neurona *N2 = (Neurona *)calloc(1, sizeof(Neurona));    *N2 = Neurona(umbral, McCulloch);

    Neurona *ID = (Neurona *)calloc(1, sizeof(Neurona));    *ID = Neurona(umbral, McCulloch);
    Neurona *DI = (Neurona *)calloc(1, sizeof(Neurona));    *DI = Neurona(umbral, McCulloch);

    mp->aniadir(entrada); mp->aniadir(oculta); mp->aniadir(salida);

    entrada->aniadir(I); 
    entrada->aniadir(D);
    oculta->aniadir(N1); 
    oculta->aniadir(N2);
    salida->aniadir(ID); 
    salida->aniadir(DI);

    I->conectar(N1, 2);
    I->conectar(N2, -1);
    I->conectar(ID, -1);
    I->conectar(DI, 1);

    D->conectar(N2, 2);
    D->conectar(N1, -1);
    D->conectar(DI, -1);
    D->conectar(ID, 1);

    N1->conectar(ID, 1);
    N2->conectar(DI, 1);
}

void comprobarRed(RedNeuronal& mp){
    int i = 0;
    for (Capa *c: mp.capas){
        int j = 0;
        for (Neurona *n: c->neuronas){
            printf("Capa %d: Neurona %d: Umbral = %f, Tipo = %d\n", i, j++, n->umbral, n->tipo);
            int k = 0;
            for (Conexion c: n->conexiones){
                printf("\tNeurona %d: Peso = %f, Umbral = %f\n", k++, c.peso, c.neurona->umbral);
            }
        }
        i++;
    }
}

vector<vector<int>> crearPruebas(){

    vector<vector<int>> pruebas {
        {1, 0}, {0, 1}, {0, 0},                 // Izquierda a derecha 3(1,0)
        {0, 1}, {1, 0}, {0, 0},                 // Derecha a izquierda 6(0,1)
        {1, 0}, {0, 1}, {1, 0}, {0, 1}, {0, 0}, // Izquierda a derecha a izquierda y a derecha 9(1,0), 10(0,1), 11(1,0)
        {1, 0}, {1, 1}, {0, 0},                 // Deben fallar (0,0)
        {1, 1}, {0, 1}, {0, 0},
        {1, 1}, {1, 1}, {0, 0},
    };

    return pruebas;
}

int t = 1;
void pasarPruebas(RedNeuronal *mp, vector<vector<int>> pruebas){

    int i;
    
    for (vector<int> entradas: pruebas){
        i = 0;
        for (int entrada: entradas){
            mp->capas[0]->neuronas[i++]->inicializar(entrada);
        }
        mp->disparar();
        mp->inicializar();
        mp->propagar();
        printf("%d\t", t);
        for (Capa *c: mp->capas){
            printf(" |");
            for (Neurona *n: c->neuronas){
                printf(" %.2f", n->valor_salida);
            }
        }
        printf("\n");
        t++;
    }
}

int error(string errorString, char *exeName){
    printf("ERROR: %s\n", errorString.c_str());
    printf("Sintaxis: %s -[peh]\n", exeName);
    printf("\t-p: Version de prueba\n\t-e: Version de ejecucion\n\t-h: Ayuda\n");
    return -1;
}

int main(int argc, char *argv[]){

    srand(time(0));

    RedNeuronal mp = RedNeuronal();
    vector<vector<int>> pruebas;

    printf("Creando red de McCulloch-Pitts...\n");
    inicializacion(&mp);

    int opcion;
    while ((opcion = getopt (argc, argv, "peh")) != -1){        
        switch (opcion){
            case 'p':
                printf("\nVERSION DE PRUEBA:\n");

                /*
                printf("Comprobando red...\n");
                comprobarRed(mp);
                */

                printf("Creando pruebas...\n");
                pruebas = crearPruebas();

                printf("Pasando pruebas...\n");
                printf("t        | I    D    | N1   N2   | ID   DI  \n");
                printf("--------- ----------- ----------- ----------\n");
                pasarPruebas(&mp, pruebas);

                break;

            case 'e':
                printf("\nVERSION DE EJECUCION:\n");

                int I, D;

                printf("Introduce dos entradas [0-1] o (-1 -1) para finalizar:\n> ");
                scanf("%d %d", &I, &D);
                
                while (I != -1 && D != -1){
                    if ((I == 0 || I == 1) && (D == 0 || D == 1)){
                        pasarPruebas(&mp, {{I, D}});
                    } else {
                        printf("ERROR: Valores introducidos incorrectos, prueba de nuevo\n");
                    }
                    printf("\n> ");
                    //printf("Introduce dos entradas [0-1] o (-1 -1) para finalizar:\n");
                    cin >> I >> D;
                }

                break;

            case 'h':
                printf("\nAYUDA:\n");
            default:
                printf("Sintaxis: %s -[peh]\n", argv[0]);
                printf("\t-p: Version de prueba\n\t-e: Version de ejecucion\n\t-h: Ayuda\n");
        };
    }

    for (int i = optind; i < argc; i++)
        printf("ERROR: opcion '%s' no soportada\n", argv[i]);

    printf("Liberando\n");
    mp.liberar();

    return 0;
}