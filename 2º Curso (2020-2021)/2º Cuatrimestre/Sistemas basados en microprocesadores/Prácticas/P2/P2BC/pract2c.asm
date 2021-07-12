; Autor: David Teófilo Garitagoitia Romero
; Grupo 2262
; Práctica 2, ejercicio a
; DEFINICION DEL SEGMENTO DE DATOS
DATOS SEGMENT
 ; DEFINICION DE LOS VECTORES
 STRING DB 'This is a sample string', '$'
 vector1 db 1,2,2,4
 vector2 db 4,2,5,1
 vector3 db 3,2,4,1
 NUM db 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ;Creo una variable donde pongo los 4 numeros (que se iran tachando/descartando/convirtiendo a -1 a medida que se usen)
 ESPACIO db ' '


;DIMENSIONES DE LA MATRIZ
 FILAS dw 3 ;Filas==Vectores
 COLUMNAS dw 4 ;Columnas==Elementos de cada vector

 ;VALOR QUE EXCEDE EL RANGO
 maximo db 5 ;Valor máximo del rango

 errorNumDif DB "FUERA DEL CONJUNTO: 1,2,3,4", 13, 10, '$'
 salidaCorrecta DB "CORRECTO", 13, 10, '$'
 entradarepetida DB "Repeticion", 13, 10, '$'

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
; DEFINICION DEL SEGMENTO PARA EL ASCII
ASCIINUMBER SEGMENT
  ASCII_N DB 6 dup(?) ;Con dos bytes el máximo es el FFFF que corresponde al 65535, y otro byte para el $
ASCIINUMBER ENDS
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
    MOV AX, FILAS ;En el guardaremos los número de los vectores
    MOV CX, COLUMNAS ;Pasamos las columnas a CX
    MUL CX ;Multiplicamos las filas por las columnas, esto servirá para indicar el fin de bucle
    MOV FILAS, AX ;Cambiamos filas por filas*columnas
    MOV AX, 0
    MOV CX, 0 ;Columna
    MOV SI, 0 ;Fila (Vector)
    MOV BX, 0 ;posicion retorno ascii
    MOV DL, -1
    
    
    ;DEBUG Probar la función con el ejemplo de prueba
    ;MOV AX, 0100h 
    ;call CAMBIA_ASCII
    ;load address of the string 
    ;MOV DS, DX
    ;MOV DX, BX
    ;output the string
    ;loaded in dx 
    ;MOV AH,09H
    ;INT 21H 
    ;MOV AX, 4C00H
    ;INT 21H
    ;DEBUG  



Comprobar_vectores:;Bucle para comprobar todas las filas (vectores de la matriz)
    ;Indexo para que se vea mejor el 2º bucle
    JMP SET_VALUES ;Saltamos a inicio para iniciar todo los que necesitemos
    Comprobar_vector:
        MOV AL, BYTE PTR DS:vector1[SI][BP] ;cargamos en AL el valor a comprobar (fila==SI, columna==BX)
        ;Comprobar si se pasa por arriba (>4)
        CMP AL, maximo ;Comparamos con el máximo (5) que es el 1º valor fuera del límite, 4-5=-1, 5-5=0 ...
        JNS ERROR ;Si ese elemento falla es decir la resta de ese elemento con 5 da >=0 (lo que quiere decir que ese valor es 5 o superior y por tanto fuera de límite)

        ;Comprobar si se queda corto (<=0)
        CMP AL, 1 ;Comprobación para el valor negativo, si es 0, 0-1=-1, -1-1=-2...
        JS ERROR
        MOV DI, AX        ;Comprobar repetición
        CMP DL, [NUM+DI] ;Comprobamos si ese número ya estaba
        JE REPETICION;Si esta saltamos a repetición
        MOV [NUM+DI], DL ;Si no era -1, lo ponemos a -1 (lo descartamos)

        ;Comprobar salida de bucle
        INC BP ;Incrementamos BX para leer siguiente valor
        CMP BP, columnas ;Comprobamos si ya hemos leido las columnas (4)
        JNE Comprobar_vector ;Si aun faltan elementos por leer, saltamos al inicio
        JMP CORRECTO ;Si ya hemos leido los 4 valores del vector y no hemos tenido errores
    ;Vuelvo al bucle exterior
    COMP: 
    ADD SI, Columnas; Incrementamos en los columnas [4] para leer el siguiente vector
	CMP SI, filas   ;Comprueba si ya hemos leido los 3 vectores
	JNE Comprobar_vectores ;Si aun no los hemos leido vuelve al bucle

    ;Cuando termine el bucle 
    ;FIN DE PROGRAMA
    MOV AX, 4C00H
    INT 21H



ERROR:
    ;Imprimir fuera del conjunto
    call Imprimir_num
    mov dx, offset errorNumDif
    mov ah, 9
    int 21h 
    JMP COMP ;Vuelve a la función principal

CORRECTO:
    ;Imprimir correcto
    call Imprimir_num
    mov dx, offset salidaCorrecta
    mov ah, 9
    int 21h 
    JMP COMP ;Vuelve a la función principal

REPETICION:
    ;Imprimir repetición
    call Imprimir_num
    mov dx, offset entradarepetida
    mov ah, 9
    int 21h 
    JMP COMP ;Vuelve a la función principal

;Inicializa los valores para el bucle interior
SET_VALUES:
    mov BL, 0
    mov AX, DATOS
    MOV DS, AX
    MOV AX, 0
    B_I: ;Bucle de inicio
    MOV NUM[BX], BL
    INC BL
    CMP BL, 10
    JNE B_I
    MOV BX, 0
    MOV BP, 0 
    MOV DL, -1
    JMP Comprobar_vector

;Cambia el valor de AX a ASCII

CAMBIA_ASCII PROC
    MOV DX, ASCIINUMBER ;Cargas el segmento en DX
    MOV DS, DX ;lo pongo en DS
    MOV BX, OFFSET ASCII_N ;Pongo en BX el offset
    MOV BP, OFFSET ASCII_N ;Lo pongo tambien en BP para que sea más fácil comparar
    MOV CX, 0ah ;Cargo 10 en CX para ir haciendo las divisiones
    MOV BP, 0 ;BP lo voy a usar como contador de Bytes
    MOV DX, 0
    B_CA: ;Bucle cambia ascii
    MOV DX, 0 ;Lo pones a 0 para evitar restos de otras operaciones
    DIV CX ;Divides el número entre 10, te quedas en AX con el número menos el ultimo que se va a DX 
    ;(ese número esta entre 0 y 9, se puede cambiar a ascii directo)
    add DL, BYTE PTR '0' ;Convertimos el número a ASCII
    PUSH DX ;Hay que usar la pila, este numeró tiene que estar lo + a la derecha posible
    INC BP ;Incrementas BX para escribir en el siguiente Byte
    CMP AX, 0Ah ;Comprobamos si aun tienes que hacer divisiones porque no se puede transformar directamente
    JGE B_CA ;Si no es un numero entre 0 y 9 (de conversión inmediata, sigues dividiendo)
    
    ;En cambio si es de conversión inmediata, significa que solo queda el último
    ADD AL, '0' ;Lo conviertes a ASCII
    CMP AL, '0'
    JE E_M_2 ;Si solo queda el 0, salto a E_M_2 para que me acorte BP
    MOV [BX], AL
    ;Bucle para escribir en el orden correcto usando la pila
    E_M: ;Escribir en memoria
    CMP BX, BP
    JE E_M_F
    INC BX
    POP AX
    MOV [BX], AL
    JMP E_M_F
    E_M_F:
    INC BX
    MOV [BX], BYTE PTR '$'
    MOV BX, OFFSET ASCII_N ;Coloco BX al inicio
    MOV DX, ASCIINUMBER ;Cargas el segmento en DX
    MOV AX, DATOS ;Recupero el DS original
    MOV DS, AX
    Ret
    E_M_2:
    DEC BX ;Si es 0 decrementas BP para que no imprime el ultimo 0
    DEC BP ;Decrementas BP dado que has decrementado BX
    JMP E_M
CAMBIA_ASCII ENDP

Imprimir_num PROC ;Bucle para imprimir los números
    MOV BP, 0
    B_IM:
    MOV AX, 0
    MOV AL, DS:vector1[SI][BP]
    PUSH BP ;BP lo voy a necesitar para el cambia ascii
    call CAMBIA_ASCII
    POP BP ;Recupero BP para saber por que columna voy
    MOV DS, DX

    ;Imprimimos el número
    MOV DX, BX
    MOV AH,09H
    INT 21H 

    ;Imprimimos el espacio
    MOV AX, DATOS
    MOV DS, AX
    MOV DL, ESPACIO
    MOV AH, 02H
    INT 21H 

    ;Incrementamos el contador
    INC BP
    CMP BP, Columnas
    JNE B_IM
    RET ;Cuando se termina de imprimir toda la cadena salimos
Imprimir_num ENDP

INICIO ENDP
;ESPACIO PARA SUBRUTINAS
; FIN DEL SEGMENTO DE CODIGO
CODE ENDS
; FIN DEL PROGRAMA INDICANDO DONDE COMIENZA LA EJECUCION
END INICIO