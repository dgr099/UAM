#include "../../include/Capa.h"

int main(){

    Capa capa = Capa();

    for (int i = 0; i < 5; i++){
        Neurona *n = (Neurona *)calloc(1, sizeof(Neurona));
        *n = Neurona(i, McCulloch);
        capa.aniadir(n);
    }
    
    printf("\nTest aniadir\n");
    int i = 0;
    for (Neurona *n: capa.neuronas){
        printf("Neurona %d: Umbral = %f, Tipo = %d\n", i++, n->umbral, n->tipo);
    }
    int capa_size = capa.neuronas.size();

    Capa capa2 = Capa();
    Neurona *n = (Neurona *)calloc(1, sizeof(Neurona));
        *n = Neurona(10, McCulloch);
    capa2.aniadir(n);

    capa.conectar(&capa2, 1, 1);
    printf("\nTest conectar\n");
    for (Neurona *n: capa.neuronas){
        for (Conexion c: n->conexiones){
            printf("Peso: %f, Umbral = %f, Tipo = %d\n", c.peso, c.neurona->umbral, c.neurona->tipo);
        }
    }

    capa.inicializar();
    printf("\nTest inicializar\n");
    for (Neurona *n: capa.neuronas){
        printf("Valor entrada = %f\n", n->valor_entrada);
    }

    for (int i = 0; i < capa_size; i++){
        capa.neuronas[i]->inicializar(10);
    }

    capa.disparar();
    printf("\nTest disparar\n");
    for (Neurona *n: capa.neuronas){
        printf("Valor salida = %f\n", n->valor_salida);
    }

    /*int*/ i = 0;
    for (Neurona *n: capa.neuronas){
        printf("Neurona %d: Valor entrada = %f\n", i++, n->valor_entrada);
    }

    capa.propagar();
    printf("\nTest propagar (+ reinicializacion)\n");
    for (Neurona *n: capa2.neuronas){
        printf("Valor entrada = %f\n", n->valor_entrada);
    }
    capa.liberar();
    capa2.liberar();

    return 0;
}