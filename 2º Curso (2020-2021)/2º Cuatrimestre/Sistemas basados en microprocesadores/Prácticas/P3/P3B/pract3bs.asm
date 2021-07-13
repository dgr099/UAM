;*
;* Sistemas Basados en Microprocesador
;* 2020-2021
;* Practica 3bs
;* 
;*
;* author: David Teófilo Garitagoitia Romero
;*
;* notas: ejemplo vacío
;*********************************************************************/
;PUBLIC _encuentraSubcadena
_TEXT SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS: _TEXT
    ; COMIENZO DEL PROCEDIMIENTO PRINCIPAL
	_MAIN PROC 
		;COMIENZO DEL PROGRAMA 
        _Tabla DB 1, 2, 4, 8, 5, 10, 9, 7, 3, 6 ;Tabla con los valores a multiplicar
		PUBLIC _encuentraSubcadena
        PUBLIC _calculaSegundoDC
	_MAIN ENDP 

; procedimiento para buscar una subcadena
;encuentraSubcadena (char* str, char* substr)
    _encuentraSubcadena proc far
    PUSH BP ;guardo el valor de BP
    MOV BP, SP ;Cargo en BP el valor del stack pointer
    PUSH BX DX CX SI DI
    PUSH ES ;Guardamos segmento extra de datos
    PUSH DS ;Guardamos segmento de datos
    LES DI, [BP + 6] ;Cargas la tabla de cadena
    LDS SI, [BP + 10] ;Cargas la tabla subcadena
    ;Ya no vamos a necesitar para nada más BP del stack pointer
    ;Bucle para recorrer toda la cadena
    MOV BX, 0
    MOV BP, 0
    MOV DX, 0
    MOV CX, 0
    MOV AX, -1
    inicio_bucle:
    MOV CL, DS:[SI + BP] ;cargas la siguiente letra de la subcadena
    CMP CL, 0 ;Si has terminado de leer la subcadena es que has encontrado una posicion donde está en ambas
    JE final
    MOV DL, ES:[DI + BX] ;cargas la siguiente letra de la cadena
    CMP DL, 0 ;final de la cadena
    JE final_mal ;si has recorrido toda la cadena sin encontrar la subcadena
    CMP CL, DL ;comparas si son iguales
    JNE reinicio ;si no son iguales vuelta a empezar
    CMP BP, 0 ;comparamos con 0
    JE asig_ax ;Si es la primera coincidencia asignamos AX la posicion dde DX
    INC BP
    INC BX
    JMP inicio_bucle

    final:
    POP DS ;Recuperamos el segmento de datos
    POP ES ;Recuperamos el segmento extra
    POP DI ;Recuperamos el valor de los registros usados
    POP SI
    POP CX
    POP DX
    POP BX
    POP BP ;Recupero el valor del BP
    RET
    final_mal:
    MOV AX, -1 ;ponemos -1 en AX porque no encontro la subcadena
    JMP final
    reinicio:
    CMP AX, -1
    JNE reinicio_1 ;Si ya hubo una primera coincidencia
    MOV BP, 0 ;Volvemos al inicio de la subcadena
    INC BX ;Incrementamos BX para leer el siguiente caracter de la cadena
    JMP inicio_bucle
    reinicio_1:
    MOV BX, AX
    INC BX
    MOV AX, -1
    MOV BP, 0
    JMP inicio_bucle
    asig_ax:
    MOV AX, BX
    INC BP
    INC BX
    JMP inicio_bucle
    _encuentraSubcadena endp

    ;calculaSegundoDC (char* numCuenta)
    _calculaSegundoDC proc far
    ;Debug
    ;MOV DX, 0
    ;MOV AX, 10
    ;MOV BX, 2
    ;DIV BX  ; Ax=Ax/2
    PUSH BP ;guardo el valor de BP
    MOV BP, SP ;Cargo en BP el valor del stack pointer
    PUSH DS ;Guardamos el valor del data segment
    PUSH DI CX DX BX ;guardamos los registros que vamos a usar
    LDS DI, [BP + 6] ;Cargo la cuenta con el offset en DI y el segmento en DS
    MOV BX, 0 ;Contador para las multiplicaciones
    MOV DX, 0 ;En DX guardas las sumas de los productos
    bucle:
    MOV CL, DS:[DI] ;Leemos el siguiente char
    CMP CL, 0 ;Compruebas si has llegado al fin de la cadena
    JE fin_bucle
    CMP BX, 10 ;Si hay más valores de los que debería
    JE fin_mal ;Salta al final malo
    SUB CL, '0' ;Le quitas '0' para tener el valor numérico y no su código ascii
    MOV BYTE PTR AL, _Tabla[BX] ;Cargamos el valor a multiplicar 
    MUL CL ;Multiplicamos AL*CL y guardamos el valor en AX
    ADD DX, AX ;Sumamos es DX el resultado de la multiplicación
    INC BX ;Incrementamos BX para multiplicar por el siguiente
    INC DI ;Incrementamos DI para leer el siguiente caracter 
    JMP bucle
    fin_bucle:
    ;Tenemos en DX la suma de todos los productos
    CMP BX, 10 ;Si no habia 10 numeros en la cuenta
    JNE fin_mal
    MOV AX, DX ;Guardamos en AX el resultado de todas las sumas
    MOV CX, 11 ;Ponemos en CX el resultado de las sumas
    MOV DX, 0
    DIV CX ;Hacemos la division entre 11 ;AX=AX/11
    SUB CX, DX ;le restamos a 11 el módulo 11 de la suma
    CMP CX, 10 ;Si el resultado es 10 retorna 1
    JE EXC
    MOV AX, CX ;Ponemos en AX el resultado
    fin:
    POP BX DX CX DI DS BP ;recuperamos los registros empleados
    RET
    EXC:
    MOV AX, 1
    JMP fin
    fin_mal:
    MOV AX, -1
    JMP fin
    _calculaSegundoDC endp
_TEXT ENDS 
END
