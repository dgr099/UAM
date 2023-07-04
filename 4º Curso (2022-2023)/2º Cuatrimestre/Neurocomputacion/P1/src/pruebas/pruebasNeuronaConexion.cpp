#include "../../include/Neurona.h"

int main(){

    Neurona neurona = Neurona(2, McCulloch);
    Neurona neurona2 = Neurona(3, McCulloch);
    
    printf("Umbral = %f\nTipo = %d\n\n", neurona.umbral, neurona.tipo);

    neurona.conectar(&neurona2, 0.5);
    for (Conexion c: neurona.conexiones){
        printf("Conexion: Peso = %f\n", c.peso);
        printf("\tUmbral = %f\n\tTipo = %d\n\n", c.neurona->umbral, c.neurona->tipo);
    }
    
    neurona.inicializar(10);
    printf("Valor entrada = %f\n", neurona.valor_entrada);

    neurona.disparar();
    printf("Valor salida = %f\n", neurona.valor_salida);

    printf("\nConexiones:");

    neurona.propagar();
    for (Conexion c: neurona.conexiones){
        printf("\n\tValor entrada = %f\n", c.neurona->valor_entrada);
    }

    neurona2.liberar();
    neurona.liberar();

    return 0;
}