#include "../../include/RedNeuronal.h"

int main(){

    int i = 0;

    RedNeuronal red = RedNeuronal();
    for (i = 0; i < 2; i++){
        Capa *c = (Capa*)calloc(1, sizeof(Capa));
        *c = Capa();
        red.aniadir(c);
    }
    for (i = 0; i < 5; i++){
        Neurona *n = (Neurona *)calloc(1, sizeof(Neurona));
        *n = Neurona(i, McCulloch);
        red.capas[0]->aniadir(n);
    }
    Neurona *n = (Neurona *)calloc(1, sizeof(Neurona));
    *n = Neurona(i, McCulloch);
    red.capas[1]->aniadir(n);

    printf("\nTest aniadir\n");
    i = 0;
    for (Capa *c: red.capas){
        for (Neurona *n: c->neuronas){
            printf("Capa %d: Umbral = %f, Tipo = %d\n", i, n->umbral, n->tipo);
        }
        i++;
    }

    red.inicializar();
    printf("\nTest inicializar\n");
    i = 0;
    for (Capa *c: red.capas){
        for (Neurona *n: c->neuronas){
            printf("Capa %d: Valor_entrada = %f\n", i, n->valor_entrada);
        }
        i++;
    }

    int num_capas = red.capas.size();
    for (int i = 0; i < num_capas; i++){
        int num_neuronas = red.capas[i]->neuronas.size();
        for (int j = 0; j < num_neuronas; j++){
            red.capas[i]->neuronas[j]->inicializar(5);
        }
    }

    red.disparar();
    printf("\nTest disparar\n");
    i = 0;
    for (Capa *c: red.capas){
        for (Neurona *n: c->neuronas){
            printf("Capa %d: Valor_salida = %f\n", i, n->valor_salida);
        }
        i++;
    }

    red.capas[0]->conectar(red.capas[1], 1, 1);
    red.propagar();
    printf("\nTest propagar\n");
    i = 0;
    for (Capa *c: red.capas){
        for (Neurona *n: c->neuronas){
            printf("Capa %d: Valor_entrada = %f\n", i, n->valor_entrada);
        }
        i++;
    }
    red.liberar();

    return 0;
}