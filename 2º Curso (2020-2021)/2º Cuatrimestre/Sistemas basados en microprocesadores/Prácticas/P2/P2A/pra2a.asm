; Autor: David Teófilo Garitagoitia Romero
; Grupo 2262
; Práctica 2, ejercicio a
; DEFINICION DEL SEGMENTO DE DATOS
DATOS SEGMENT
 ; DEFINICION DE LOS VECTORES
 vector1 db 1,2,2,4
 vector2 db 4,2,5,1
 vector3 db 3,2,4,1


;DIMENSIONES DE LA MATRIZ
 filas dw 3 ;Filas==Vectores
 columnas dw 4 ;Columnas==Elementos de cada vector

 ;VALOR QUE EXCEDE EL RANGO
 maximo db 5 ;Valor máximo del rango

 errorNumDif DB "FUERA DEL CONJUNTO: 1,2,3,4", 13, 10, '$'
 salidaCorrecta DB "CORRECTO", 13, 10, '$'

DATOS ENDS
;**************************
; DEFINICION DEL SEGMENTO DE PILA
PILA SEGMENT STACK "STACK"
 DB 40H DUP (0) ;ejemplo de inicialización, 64 bytes inicializados a 0
PILA ENDS
;**************************
; DEFINICION DEL SEGMENTO EXTRA
EXTRA SEGMENT
 RESULT DW 0,0 ;ejemplo de inicialización. 2 PALABRAS (4 BYTES)
EXTRA ENDS
;**************************
; DEFINICION DEL SEGMENTO DE CODIGO
CODE SEGMENT
ASSUME CS: CODE, DS: DATOS, ES: EXTRA, SS: PILA
; COMIENZO DEL PROCEDIMIENTO PRINCIPAL
INICIO PROC 
; INICIALIZA LOS REGISTROS DE SEGMENTO CON SU VALOR
    MOV AX, DATOS
    MOV DS, AX
    MOV AX, PILA
    MOV SS, AX
    MOV AX, EXTRA
    MOV ES, AX
    MOV SP, 64 ; CARGA EL PUNTERO DE PILA CON EL VALOR MAS ALTO
    ; FIN DE LAS INICIALIZACIONES
    ; COMIENZO DEL PROGRAMA

    ;Como si fuera un doble for (pseudocódigo)

    ;for(vector in matriz){
        ;for(elementos in vector){
            ;if(fuera limite){
                ;mensaje_error
                ;}
        ;}
        ;if(no ha tenido error){
            ;mensaje_correcto
        ;}
    ;}

    ;Inicializamos valores para la función principal
    MOV CX, 0 ;Cargo 0 en CX que usaré como contador de bucle 1
    MOV SI, 0 ;Fila (Vector)
    MOV BX, 0 ;Columna (Elemento del vector)

Comprobar_vectores:;Bucle para comprobar todas las filas (vectores de la matriz)
    MOV BX, 0 ;Iniciamos a 0 BP para el bucle de los 4 elementos
    ;Indexo para que se vea mejor el 2º bucle
    Comprobar_vector:
        MOV AL, BYTE PTR DS:vector1[SI][BX] ;cargamos en AL el valor a comprobar (fila==SI, columna==BX)
        ;Comprobar si se pasa por arriba (>4)
        CMP AL, maximo ;Comparamos con el máximo (5) que es el 1º valor fuera del límite, 4-5=-1, 5-5=0 ...
        JNS ERROR ;Si ese elemento falla es decir la resta de ese elemento con 5 da >=0 (lo que quiere decir que ese valor es 5 o superior y por tanto fuera de límite)
        
        ;Comprobar si se queda corto (<=0)
        CMP AL, 1 ;Comprobación para el valor negativo, si es 0, 0-1=-1, -1-1=-2...
        JS ERROR
        INC BX ;Incrementamos BX para leer siguiente valor
        CMP BX, columnas ;Comprobamos si ya hemos leido las columnas (4)
        JNE Comprobar_vector ;Si aun faltan elementos por leer, saltamos al inicio
        JMP CORRECTO ;Si ya hemos leido los 4 valores del vector y no hemos tenido errores
    ;Vuelvo al bucle exterior
    COMP: 
    ADD SI, 4; Incrementamos en 4 para pasar al siguiente vector
    INC CX ;Contador de vectores leidos
	CMP CX, filas   ;Comprueba si ya hemos leido los 3 vectores
	JNE Comprobar_vectores ;Si aun no los hemos leido vuelve al bucle

    ;Cuando termine el bucle 
    ;FIN DE PROGRAMA
    MOV AX, 4C00H
    INT 21H

ERROR:
    ;Imprimir fuera del conjunto
    mov dx, offset errorNumDif
    mov ah, 9
    int 21h 
    JMP COMP ;Vuelve a la función principal

CORRECTO:
    ;Imprimir correcto
    mov dx, offset salidaCorrecta
    mov ah, 9
    int 21h 
    JMP COMP ;Vuelve a la función principal

INICIO ENDP
;ESPACIO PARA SUBRUTINAS
; FIN DEL SEGMENTO DE CODIGO
CODE ENDS
; FIN DEL PROGRAMA INDICANDO DONDE COMIENZA LA EJECUCION
END INICIO