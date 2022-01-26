/**
 *      Funciones de generacion de codigo
 *      OBSERVACIÓN GENERAL A TODAS LAS FUNCIONES:
 *      Todas ellas escriben el código NASM a un FILE* proporcionado como primer argumento.
 *
 *      @author Carlos Anivarro Batiste
 *      @author Daniel Barahona Martin
 *      @author David Garitagoitia Romero
*/
#include "generacion.h"
#include "alfa.h"


void escribir_cabecera_presentacion(FILE *fpasm, char *input_filename)
{
      if(!fpasm){
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, ";-------------------------------\n");
        fprintf(fpasm, "; %s\n", input_filename);
        fprintf(fpasm, ";   Autor: Carlos Anivarro\n");
        fprintf(fpasm, ";   Autor: Daniel Barahona\n");
        fprintf(fpasm, ";   Autor: David Garitagoitia\n");
        fprintf(fpasm, ";-------------------------------\n");
}

void escribir_cabecera_bss(FILE *fpasm)
{
        if(!fpasm){
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "segment .bss\n");
        fprintf(fpasm, "__esp resd 1\n");
}

void escribir_subseccion_data(FILE *fpasm)
{
        if(!fpasm){
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "segment .data\n");
        fprintf(fpasm, "msg_error_division db \"**** Division por 0 no permitida\", 0\n");
        fprintf(fpasm, "msg_error_indice_vector db \"**** Indice fuera de rango\", 0\n");
}

void declarar_variable(FILE *fpasm, char *nombre, int tipo, int tamano)
/*
   Para ser invocada en la sección .bss cada vez que se quiera declarar una variable:
    • El argumento nombre es el de la variable.
    • tipo puede ser INT o BOOLEAN (observa la declaración de las constantes del principio del fichero).
    • Esta misma función se invocará cuando en el compilador se declaren vectores, por eso se adjunta un argumento final (tamano) que para esta primera práctica siempre recibirá el valor 1.
*/
{
        if(!fpasm){
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; declarar_variable\n");
        NO_USO(tipo);

        if(!nombre){
                printf("Error fallo en compilador, nombre de la variable nulo");
                return;
        }
        fprintf(fpasm, "_%s resd %d\n", nombre, tamano);
        
}

void escribir_segmento_codigo(FILE *fpasm)
/*
   Para escribir el comienzo del segmento .text, básicamente se indica que se exporta la etiqueta main y que se usarán las funciones declaradas en la librería olib.o
*/
{
        if(!fpasm){
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; escribir_segmento_codigo\n");

        fprintf(fpasm, "segment .text\n");
        fprintf(fpasm, "global main\n");
        fprintf(fpasm, "extern print_int, print_boolean, print_string, print_blank\n");
        fprintf(fpasm, "extern print_endofline, scan_int, scan_boolean\n");
}

void escribir_inicio_main(FILE *fpasm)
/* 
   En este punto se debe escribir, al menos, la etiqueta main y la sentencia que guarda el puntero de pila en su variable (se recomienda usar __esp).
*/
{
        if(!fpasm){
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; escribir_inicio_main\n");
        fprintf(fpasm, "main:\n");
        fprintf(fpasm, "mov dword [__esp], esp\n");
}

void escribir_fin(FILE *fpasm)
/*
   Al final del programa se escribe:
    • El código NASM para salir de manera controlada cuando se detecta un error en tiempo de ejecución (cada error saltará a una etiqueta situada en esta zona en la que se imprimirá el correspondiente mensaje y se saltará a la zona de finalización del programa).
    • En el final del programa se debe:
         ·Restaurar el valor del puntero de pila (a partir de su variable __esp)
         ·Salir del programa (ret).
*/
{
        if(!fpasm){
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; escribir_fin\n");
        fprintf(fpasm, "jmp near fin ; termina sin errores\n");
        fprintf(fpasm, "fin_error_division: ; división por cero\n");
        fprintf(fpasm, "push dword msg_error_division\n");
        fprintf(fpasm, "call print_string\n");
        fprintf(fpasm, "call print_endofline\n");
        fprintf(fpasm, "add esp, 4\n");
        fprintf(fpasm, "jmp near fin ; salta al final\n");
        fprintf(fpasm, "fin_indice_fuera_rango: ; error de índice fuera de rango\n");
        fprintf(fpasm, "push dword msg_error_indice_vector\n");
        fprintf(fpasm, "call print_string\n");
        fprintf(fpasm, "call print_endofline\n");
        fprintf(fpasm, "add esp, 4\n");
        fprintf(fpasm, "jmp near fin ; salta al final\n");
        fprintf(fpasm, "fin:\n");
        /*fprintf(fpasm, "call print_endofline\n");*/
        fprintf(fpasm, "mov dword esp, [__esp] ; recupera el puntero de pila\n");
        fprintf(fpasm, "ret\n");
}

void escribir_operando(FILE *fpasm, char *nombre, int es_variable)
{
        if (!fpasm || !nombre) {
                printf("Error fallo en compilador, fichero fpasm o nombre nulo");
                return;
        }
        fprintf(fpasm, "; escribir_operando\n");

        if (es_variable == 0)
        { // Numero
                fprintf(fpasm, "mov eax, %s\n", nombre);
        }
        else
        { // Variable
                fprintf(fpasm, "mov eax, [_%s]\n", nombre);
        }
        fprintf(fpasm, "push eax\n");
}

void asignar(FILE *fpasm, char *nombre, int es_variable)
{
        if (!fpasm || !nombre) {
                printf("Error fallo en compilador, fichero fpasm o nombre nulo");
                return;
        }
        fprintf(fpasm, "; asignar\n");
        fprintf(fpasm, "pop dword eax\n");
        if (es_variable == 0){ // Numero
                fprintf(fpasm, "mov dword [_%s], eax\n", nombre);
        }else{ // Variable
                fprintf(fpasm, "mov dword eax, [eax]\n");
                fprintf(fpasm, "mov dword [_%s], eax\n", nombre);
        }
}

void apilar_constante(FILE *fpasm, int valor)
{
        fprintf(fpasm, "; apilar_constante\n");
        fprintf(fpasm, "push dword %d\n", valor);
}

void apilar_valor(FILE* fpasm, int es_referencia)
{
    fprintf(fpasm, "; apilar_valor\n");
    if (es_referencia) {
        fprintf(fpasm, "pop dword ebx");
        fprintf(fpasm, "mov ebx, [ebx]");
        fprintf(fpasm, "push dword ebx");
    }
}

/* FUNCIONES ARITMÉTICO-LÓGICAS BINARIAS */
/*
En todas ellas se realiza la operación como se ha resumido anteriormente:
- Se extrae de la pila los operandos
- Se realiza la operación
- Se guarda el resultado en la pila
Los dos últimos argumentos indican respectivamente si lo que hay en la pila es
una referencia a un valor o un valor explícito.
Deben tenerse en cuenta las peculiaridades de cada operación. En este sentido
sí hay que mencionar explícitamente que, en el caso de la división, se debe
controlar si el divisor es “0” y en ese caso se debe saltar a la rutina de error
controlado (restaurando el puntero de pila en ese caso y comprobando en el retorno
que no se produce “Segmentation Fault”)
*/

void sumar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; sumar\n");
        fprintf(fpasm, "pop dword eax\n");
        if (es_variable_2)
                fprintf(fpasm, "mov dword eax, [eax]\n");
        fprintf(fpasm, "pop dword ebx\n");
        if (es_variable_1)
                fprintf(fpasm, "mov dword ebx, [ebx]\n");
        fprintf(fpasm, "add ebx, eax\n");
        fprintf(fpasm, "push dword ebx\n");
}

void restar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; restar\n");
        fprintf(fpasm, "pop dword eax\n"); // recoge operando 1
        if (es_variable_2) // si es una variable y no un dato inmediato
                fprintf(fpasm, "mov dword eax, [eax]\n"); // cogemos el valor de esa variable de la memoria
        fprintf(fpasm, "pop dword ebx\n"); // recoge operando 2
        if (es_variable_1) // si es una variable y no un dato inmediato
                fprintf(fpasm, "mov dword ebx, [ebx]\n"); // cogemos el valor de esa variable de la memoria
        // ebx-> operando 1 y eax -> operando 2
        fprintf(fpasm, "sub ebx, eax\n"); // ebx = ebx - eax
        fprintf(fpasm, "push dword ebx\n"); // guardas en la pila el resultado
}

void multiplicar(FILE *fpasm, int es_variable_1, int es_variable_2)
{       
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; multiplicar\n");
        fprintf(fpasm, "pop dword eax\n"); // op2
        fprintf(fpasm, "pop dword ebx\n"); // op1
        if(es_variable_1 == 1){ // Variable
                fprintf(fpasm, "mov dword ebx, [ebx]\n"); 
        }
        if(es_variable_2 == 1){ // Variable
                fprintf(fpasm, "mov dword eax, [eax]\n"); 
        }
        fprintf(fpasm, "mov dword ecx, ebx\n");
        fprintf(fpasm, "imul ecx\n"); // eax ya tiene un operando, resultado en edx:eax
        // todos los valores son de 32 bits entonces lo que queda en edx es overflow)
        fprintf(fpasm, "push dword eax\n"); // guardas en la pila el resultado
}

void dividir(FILE *fpasm, int es_variable_1, int es_variable_2)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; dividir\n");
        fprintf(fpasm, "pop dword eax\n"); // op2
        if(es_variable_2 == 1){
                fprintf(fpasm, "mov dword eax, [eax]\n");
        }
        fprintf(fpasm, "cmp eax, 0\n");
        fprintf(fpasm, "je fin_error_division\n"); // Si el divisor es 0, imprimir error
        
        fprintf(fpasm, "pop dword ebx\n"); // op1
        if(es_variable_1 == 1){
                fprintf(fpasm, "mov dword ebx, [ebx]\n");
        }
        fprintf(fpasm, "mov dword ecx, eax\n"); // ecx <- divisor
        fprintf(fpasm, "mov dword eax, ebx\n"); // eax <- dividendo
        fprintf(fpasm, "cdq\n"); // extiende en signo edx:eax
        fprintf(fpasm, "idiv ecx\n");
        fprintf(fpasm, "push dword eax\n"); // resultado en eax y lo guardamos en pila
}

void o(FILE *fpasm, int es_variable_1, int es_variable_2)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; or logico\n");
        fprintf(fpasm, "pop dword eax\n"); // op2
        if (es_variable_2) // si es una variable y no un dato inmediato
                fprintf(fpasm, "mov dword eax, [eax]\n"); // cogemos el valor de esa variable de la memoria
        fprintf(fpasm, "pop dword ebx\n"); // op1
        if (es_variable_1) // si es una variable y no un dato inmediato
                fprintf(fpasm, "mov dword ebx, [ebx]\n"); // cogemos el valor de esa variable de la memoria
        fprintf(fpasm, "or ebx, eax\n"); // ebx = ebx or eax
        fprintf(fpasm, "push dword ebx\n"); //guardamos resultado en la pila
}

void y(FILE *fpasm, int es_variable_1, int es_variable_2)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; and logico\n");
        fprintf(fpasm, "pop dword eax\n"); // op2
        if (es_variable_2) // si es una variable y no un dato inmediato
                fprintf(fpasm, "mov dword eax, [eax]\n"); // cogemos el valor de esa variable de la memoria
        fprintf(fpasm, "pop dword ebx\n"); // op1
        if (es_variable_1) // si es una variable y no un dato inmediato
                fprintf(fpasm, "mov dword ebx, [ebx]\n"); // cogemos el valor de esa variable de la memoria
        fprintf(fpasm, "and ebx, eax\n"); // ebx = ebx and eax
        fprintf(fpasm, "push dword ebx\n"); // guardamos resultado en la pila
}

void cambiar_signo(FILE *fpasm, int es_variable)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; cambiar signo\n");
        fprintf(fpasm, "pop dword eax\n");
        if (es_variable)
                fprintf(fpasm, "mov dword eax, [eax]\n");
        fprintf(fpasm, "neg eax\n"
                       "push dword eax\n");
}

void no(FILE *fpasm, int es_variable, int cuantos_no)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; no lógico\n");
        fprintf(fpasm, "pop dword eax\n");
        if (es_variable)
                fprintf(fpasm, "mov dword eax, [eax]\n");
        fprintf(fpasm, "cmp eax, 0\n");
        fprintf(fpasm, "je dejar_1_no%d\n", cuantos_no);
        fprintf(fpasm, "cmp eax, 1\n");
        fprintf(fpasm, "je dejar_0_no%d\n", cuantos_no);
        fprintf(fpasm, "jmp fin_no%d\n", cuantos_no);
        fprintf(fpasm, "dejar_1_no%d:\n", cuantos_no);
        fprintf(fpasm, "mov dword eax, 1\n");
        fprintf(fpasm, "push dword eax\n");
        fprintf(fpasm, "jmp fin_no%d\n", cuantos_no);
        fprintf(fpasm, "dejar_0_no%d:\n", cuantos_no);
        fprintf(fpasm, "mov dword eax, 0\n");
        fprintf(fpasm, "push dword eax\n");
        fprintf(fpasm, "fin_no%d:\n", cuantos_no);
}

/* FUNCIONES COMPARATIVAS */
void igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; comparación igual\n");
        //lecuta de operandos
        fprintf(fpasm, "pop dword eax\n"); // Op2
        if (es_variable2)
                fprintf(fpasm, "mov dword eax, [eax]\n");
        fprintf(fpasm, "pop dword ebx\n"); // Op1
        if (es_variable1)
                fprintf(fpasm, "mov dword ebx, [ebx]\n");
        //operación
        fprintf(fpasm, "cmp ebx, eax\n"); // compara operando 1 y operando 2
        fprintf(fpasm, "je igual_es_igual%d\n", etiqueta); //si se cumple la condición de igualdad salta
        fprintf(fpasm, "mov dword eax, 0\n"); // si no salta es que no se cumple la condición
        fprintf(fpasm, "push dword eax\n"); // mete un 0 en la pila para indicar que no se cumple la condicion
        fprintf(fpasm, "jmp igual_fin%d\n", etiqueta); // saltamos al final para evitar el correcto
        fprintf(fpasm, "igual_es_igual%d:\n", etiqueta); //salto de igualdad
        fprintf(fpasm, "mov dword eax, 1\n"); //mete en la pila un 1 para indicar que se cumple
        fprintf(fpasm, "push dword eax\n");
        fprintf(fpasm, "igual_fin%d:\n", etiqueta); //fin de la comprobación de igualdad
}

void distinto(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; comparar distinto\n");
        //lectura de operandos
        fprintf(fpasm, "pop dword eax\n"); // Op2
        if(es_variable2)
               fprintf(fpasm, "mov dword eax, [eax]\n");
        fprintf(fpasm, "pop dword ebx\n"); // Op1
        if (es_variable1)
                fprintf(fpasm, "mov dword ebx, [ebx]\n");
        //operación
        fprintf(fpasm, "cmp ebx, eax\n"); // compara operando 1 y operando 2
        fprintf(fpasm, "jne distinto_es_distinto%d\n", etiqueta); //si se cumple la condición de desigualdad salta
        fprintf(fpasm, "mov dword eax, 0\n");
        fprintf(fpasm, "push dword eax\n");
        fprintf(fpasm, "jmp distinto_fin%d\n", etiqueta);
        fprintf(fpasm, "distinto_es_distinto%d:\n", etiqueta);
        fprintf(fpasm, "mov dword eax, 1\n");
        fprintf(fpasm, "push dword eax\n");
        fprintf(fpasm, "distinto_fin%d:\n", etiqueta);
}

void menor_igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; comparación menor_igual\n");
        fprintf(fpasm, "pop dword eax\n"); // Op2
        if (es_variable2)
                fprintf(fpasm, "mov dword eax, [eax]\n");
        fprintf(fpasm, "pop dword ebx\n"); // Op1
        if (es_variable1)
                fprintf(fpasm, "mov dword ebx, [ebx]\n");
        fprintf(fpasm, "cmp ebx, eax\n"); // Op1 <= Op2 ?
        fprintf(fpasm, "jle mni_es_mni%d\n", etiqueta);
        fprintf(fpasm, "mov dword eax, 0\n");
        fprintf(fpasm, "push dword eax\n");
        fprintf(fpasm, "jmp mni_fin%d\n", etiqueta);
        fprintf(fpasm, "mni_es_mni%d:\n", etiqueta);
        fprintf(fpasm, "mov dword eax, 1\n");
        fprintf(fpasm, "push dword eax\n");
        fprintf(fpasm, "mni_fin%d:\n", etiqueta);
}

void mayor_igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; comparación mayor_igual\n");
        fprintf(fpasm, "pop dword eax\n"); // Op2
        if (es_variable2)
                fprintf(fpasm, "mov dword eax, [eax]\n");
        fprintf(fpasm, "pop dword ebx\n"); // Op1
        if (es_variable1)
                fprintf(fpasm, "mov dword ebx, [ebx]\n");
        fprintf(fpasm, "cmp ebx, eax\n"); // Op1 >= Op2 ?
        fprintf(fpasm, "jge myi_es_myi%d\n", etiqueta);
        fprintf(fpasm, "mov dword eax, 0\n");
        fprintf(fpasm, "push dword eax\n");
        fprintf(fpasm, "jmp myi_fin%d\n", etiqueta);
        fprintf(fpasm, "myi_es_myi%d:\n", etiqueta);
        fprintf(fpasm, "mov dword eax, 1\n");
        fprintf(fpasm, "push dword eax\n");
        fprintf(fpasm, "myi_fin%d:\n", etiqueta);
}

void menor(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; comparación menor\n");
        fprintf(fpasm, "pop dword eax\n"); // Op2
        if (es_variable2)
                fprintf(fpasm, "mov dword eax, [eax]\n");
        fprintf(fpasm, "pop dword ebx\n"); // Op1
        if (es_variable1)
                fprintf(fpasm, "mov dword ebx, [ebx]\n");
        fprintf(fpasm, "cmp ebx, eax\n"); // Op1 < Op2 ?
        fprintf(fpasm, "jl mn_es_mn%d\n", etiqueta);
        fprintf(fpasm, "mov dword eax, 0\n");
        fprintf(fpasm, "push dword eax\n");
        fprintf(fpasm, "jmp mn_fin%d\n", etiqueta);
        fprintf(fpasm, "mn_es_mn%d:\n", etiqueta);
        fprintf(fpasm, "mov dword eax, 1\n");
        fprintf(fpasm, "push dword eax\n");
        fprintf(fpasm, "mn_fin%d:\n", etiqueta);
}

void mayor(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; comparación mayor\n");
        fprintf(fpasm, "pop dword eax\n"); // Op2
        if (es_variable2)
                fprintf(fpasm, "mov dword eax, [eax]\n");
        fprintf(fpasm, "pop dword ebx\n"); // Op1
        if (es_variable1)
                fprintf(fpasm, "mov dword ebx, [ebx]\n");
        fprintf(fpasm, "cmp ebx, eax\n"); // Op1 > Op2 ?
        fprintf(fpasm, "jg my_es_my%d\n", etiqueta);
        fprintf(fpasm, "mov dword eax, 0\n");
        fprintf(fpasm, "push dword eax\n");
        fprintf(fpasm, "jmp my_fin%d\n", etiqueta);
        fprintf(fpasm, "my_es_my%d:\n", etiqueta);
        fprintf(fpasm, "mov dword eax, 1\n");
        fprintf(fpasm, "push dword eax\n");
        fprintf(fpasm, "my_fin%d:\n", etiqueta);
}

/* FUNCIONES DE ESCRITURA Y LECTURA */
/* Hay que distinguir entre Global, y Parametro o Variable Local*/
void leer(FILE *fpasm, char *nombre, int tipo, int es_global)
{
        if (!fpasm || !nombre) {
                printf("Error fallo en compilador, fichero fpasm o nombre nulo");
                return;
        }
        fprintf(fpasm, "; leer (scan)\n");
        if (es_global)
                fprintf(fpasm, "push dword _%s\n", nombre);
        fprintf(fpasm, (tipo==INT) ? "call scan_int\n" : "call scan_boolean\n");
        fprintf(fpasm, "add esp, 4\n");
}

void escribir(FILE *fpasm, int es_variable, int tipo)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; escribir (print)\n");
        if(es_variable) {
                fprintf(fpasm,
                        "pop eax\n"
                        "push dword [eax]\n");
        }
        if(tipo == INT){
                fprintf(fpasm, "call print_int\n"); 
        }
        else if(tipo == BOOLEAN){
                fprintf(fpasm, "call print_boolean\n");
        }
        fprintf(fpasm, "call print_endofline\n");
        fprintf(fpasm, "add esp, 4\n");
}

void ifthenelse_inicio(FILE *fpasm, int exp_es_variable, int etiqueta)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; ifthenelse_inicio\n");
    fprintf(fpasm, "pop eax\n");
    if(exp_es_variable)
        fprintf(fpasm, "mov dword eax, [eax]\n");
    fprintf(fpasm, "cmp eax, 0\n");
    fprintf(fpasm, "je near fin_then%d\n", etiqueta);
}

void ifthen_inicio(FILE *fpasm, int exp_es_variable, int etiqueta)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; ifthen_inicio\n");
        fprintf(fpasm, "pop eax\n");
        if(exp_es_variable)
            fprintf(fpasm, "mov dword eax, [eax]\n");
        fprintf(fpasm, "cmp eax, 0\n");
        fprintf(fpasm, "je near fin_then%d\n", etiqueta);
}

void ifthen_fin(FILE *fpasm, int etiqueta)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; ifthen_fin\n");
        fprintf(fpasm, "fin_then%d:\n", etiqueta);  
}

void ifthenelse_fin_then(FILE *fpasm, int etiqueta)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; ifthenelse_fin_then\n");
        fprintf(fpasm, "jmp near fin_ifelse%d\n", etiqueta);
        fprintf(fpasm, "fin_then%d:\n", etiqueta);
}

void ifthenelse_fin(FILE *fpasm, int etiqueta)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; ifthenelse_fin\n");
        fprintf(fpasm, "fin_ifelse%d:\n", etiqueta);
}

void while_inicio(FILE *fpasm, int etiqueta)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; while_inicio\n");
        fprintf(fpasm, "inicio_while%d:\n", etiqueta);
        /* Ahora vendria una condicion (mayor, menor o igual, etc.) */
}

void while_exp_pila(FILE *fpasm, int exp_es_variable, int etiqueta)
{
    if (!fpasm) {
            printf("Error fallo en compilador, fichero fpasm nulo");
            return;
    }
    fprintf(fpasm, "; while_exp_pila\n");

    fprintf(fpasm, "pop eax\n");
    if(exp_es_variable)
        fprintf(fpasm, "mov dword eax, [eax]\n");

    fprintf(fpasm,  "cmp eax, 0\n");
    /* Si la condicion no se cumple, salir del loop */
    fprintf(fpasm, "je near fin_while%d\n", etiqueta);
    /* Aqui vendria el contenido del while */
}

void while_fin(FILE *fpasm, int etiqueta)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; while_fin\n");
/* Saltar al comienzo del loop */
        fprintf(fpasm, "jmp near inicio_while%d\n", etiqueta);
        fprintf(fpasm, "fin_while%d:\n", etiqueta);
        /* Codigo posterior al while */
}

void escribir_elemento_vector(FILE *fpasm, char *nombre_vector, int tam_max, int exp_es_direccion)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; escribir_elemento_vector\n");
    NO_USO(nombre_vector);
    NO_USO(tam_max);
    // Extraemos de la pila el valor del índice a un registro
    fprintf(fpasm, "pop dword eax\n");
    
    // En el caso en el que sea una dirección, accedemos al valor
    if (exp_es_direccion == 1) {
        fprintf(fpasm, "mov eax, dword [eax]\n");
    }

    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword [ebx], eax\n");
}

void apilar_valor_elemento_vector(FILE *fpasm)
{
    if (!fpasm) {
        printf("Error fallo en compilador, fichero fpasm nulo");
        return;
    }
    fprintf(fpasm, "; apilar_valor_elemento_vector\n");
    fprintf(fpasm, "pop dword eax\n");
    fprintf(fpasm, "push dword [eax]\n");
}

void comprobar_indice_vector(FILE *fpasm, const char *nombre, int es_direccion, int tam)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; comprobar_indice_vector\n");
        fprintf(fpasm, "pop dword eax\n");
        
        if (es_direccion)
                fprintf(fpasm, "mov dword eax, [eax]\n");
        /* Mirar que indice no sea negativo */
        fprintf(fpasm, "cmp eax, 0\n");
        fprintf(fpasm, "jl fin_indice_fuera_rango\n");

        /* Mirar que indice no sea mayor que tam vector */
        fprintf(fpasm, "cmp eax, %d\n", tam);
        fprintf(fpasm, "jge fin_indice_fuera_rango\n");

        fprintf(fpasm, "lea eax, [4*eax + _%s]\n", nombre); // Dirección del elemento indexado en eax
        fprintf(fpasm, "push dword eax\n");         // Almacenamos la dirección al elemento 
}

void declararFuncion(FILE *fpasm, char *nombre_funcion, int num_var_loc)
{
        if (!fpasm || !nombre_funcion) {
                printf("Error fallo en compilador, fichero fpasm o nombre_funcion nulo");
                return;
        }
        fprintf(fpasm, "; declararFuncion\n");
        fprintf(fpasm, "_%s:\n", nombre_funcion);
        fprintf(fpasm, "push ebp\n");
        fprintf(fpasm, "mov dword ebp, esp\n");
        fprintf(fpasm, "sub esp, %d\n", 4 * num_var_loc);
}

void retornarFuncion(FILE *fpasm, int es_variable)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; retornarFuncion\n");
        fprintf(fpasm, "pop dword eax\n");
        if (es_variable == 1)
                fprintf(fpasm, "mov dword eax, [eax]\n");
        fprintf(fpasm, "mov dword esp, ebp\n");
        fprintf(fpasm, "pop dword ebp\n");
        fprintf(fpasm, "ret\n");
}

void escribirParametro(FILE *fpasm, int direccion, int pos_parametro, int num_total_parametros)
{
        int d_ebp = 4 + 4*(num_total_parametros - pos_parametro);
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; escribirParametro\n");
        if (direccion == 1) {
                fprintf(fpasm, "lea eax, [ebp + %d]\n", d_ebp);
        } else {
                fprintf(fpasm, "mov eax, dword [ebp + %d]\n", d_ebp);
        }
        fprintf(fpasm, "push dword eax\n");
}

void escribirVariableLocal(FILE *fpasm, int direccion, int posicion_variable_local)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; escribirVariableLocal\n");
        int d_ebp = 4 * posicion_variable_local;
        if (direccion == 1) {
                fprintf(fpasm, "lea eax, [ebp - %d]\n", d_ebp);
        } else {
                fprintf(fpasm, "mov eax, dword [ebp - %d]\n", d_ebp);
        }
        fprintf(fpasm, "push dword eax\n");
}

void asignarParametro(FILE* fpasm, int es_variable, int pos_param, int num_params)
{
    int d_ebp = 4 + 4*(num_params - pos_param);
    if (!fpasm) {
            printf("Error fallo en compilador, fichero fpasm nulo");
            return;
    }
    fprintf(fpasm, "; asignarParametro\n");

    fprintf(fpasm, "pop dword eax\n");
    if (es_variable)
        fprintf(fpasm, "mov eax, dword [eax]\n");

    fprintf(fpasm, "lea ebx, [ebp + %d]\n", d_ebp);
    fprintf(fpasm, "mov [ebx], eax\n");
}

void asignarVariableLocal(FILE* fpasm, int es_variable, int pos_var_loc)
{
    int d_ebp = 4*pos_var_loc;
    if (!fpasm) {
            printf("Error fallo en compilador, fichero fpasm nulo");
            return;
    }
    fprintf(fpasm, "; asignarVariableLocal\n");

    fprintf(fpasm, "pop dword eax\n");
    if (es_variable)
        fprintf(fpasm, "mov eax, dword [eax]\n");

    fprintf(fpasm, "lea ebx, [ebp - %d]\n", d_ebp);
    fprintf(fpasm, "mov [ebx], eax\n");  
}

void operandoEnPilaAArgumento(FILE *fpasm, int es_variable)
{
        if(!fpasm){
                printf("Error fallo en compilador, fichero fpasm nulo\n");
                return;
        }
        fprintf(fpasm, "; operandoEnPilaAArgumento\n");
        if (es_variable == 1)
        {
                fprintf(fpasm, "pop dword eax\n"
                               "mov dword eax, [eax]\n"
                               "push dword eax\n");
        }
}

void llamarFuncion(FILE *fpasm, char *nombre_funcion, int num_argumentos)
{
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; llamarFuncion\n");
        fprintf(fpasm, "call _%s\n", nombre_funcion);
        limpiarPila(fpasm, num_argumentos);
        fprintf(fpasm, "push dword eax\n");
}

void limpiarPila(FILE * fpasm, int num_argumentos){
        if (!fpasm) {
                printf("Error fallo en compilador, fichero fpasm nulo");
                return;
        }
        fprintf(fpasm, "; limpiar pila\n");

        fprintf(fpasm, "add esp, %d\n", num_argumentos * 4);
}