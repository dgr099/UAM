;author: David Teófilo Garitagoitia Romero
;**************************************************************************
; SBM 2020. ESTRUCTURA BÁSICA DE UN PROGRAMA EN ENSAMBLADOR
;**************************************************************************
; DEFINICION DEL SEGMENTO DE DATOS
DATOS SEGMENT
;-- rellenar con los datos solicitados
DATOS ENDS
;**************************************************************************
; DEFINICION DEL SEGMENTO DE PILA
PILA SEGMENT STACK "STACK"
DB 40H DUP (0) ;ejemplo de inicialización, 64 bytes inicializados a 0
PILA ENDS
;**************************************************************************
; DEFINICION DEL SEGMENTO EXTRA
EXTRA SEGMENT
RESULT DW 0,0 ;ejemplo de inicialización. 2 PALABRAS (4 BYTES)
EXTRA ENDS
;**************************************************************************
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
    
    ;EJERCICIO 1
    MOV AX, 9Bh ;Direccionamiento inmediato, cargar 9BH en AX, simplemente direccionamiento inmediato

    ;MOV BL, 178 ;Otra forma para el apartado de abajo sería cargar B2H en BL pasando por decimal
    
    MOV BL, 0B2h ;Direccionamiento inmediato, necesitas indicarle que es un dato empezando por un número
    
    MOV CX, 3412h ;Direccionamiento inmediato, Cargar 3412H en CX 
    
    MOV DX, 01001001b ;Direccionamiento inmediato, auxiliar dado que no se puede emplear direccionamiento inmediato para DS
    
    MOV DS, DX ;Direccionamiento por registro, cargar 01001001b (que corresponde con el valor de DX guardado en la linea anterior) en DS 
    
    MOV DX, CX ;Direccionamiento por registro, cargar el contenido de CX en DX 
    
    MOV AX, 5000h ;Direccionamiento inmediato auxiliar para cargar Ds en la siguiente linea

    MOV DS, AX ;Direccionamiento por registro, cargo en DS el valor 5000h
    ;Como el segmento se multiplica por 16, al sumarle 5235 llegas a la posición 55235h
    MOV BH, DS:[5235] ;Direccionamiento directo, cargar en BH el contenido de la posición de memoria 55235H, mediante direccionamiento directo
    
    MOV BL, DS:[5236H] ;y en BL el contenido de la posición 55236H 

    MOV AX, 7000h ;Direccionamiento inmediato auxiliar, cargo en AX el valor 7000h por direccionamiento inmediato para cargar ese valor a DS
    
    MOV DS, AX ;Direccionamiento por registro para cargar en el segmento de datos el valor 7000h
    
    MOV DS:[8H], CH ;Direccionamiento directo, cargar en la posición de memoria 70008H el contenido de CH, la parte del segmento se multiplica por 16
                    ;De esa forma llega tomar el valor 70000 y al sumarle los 8 del offset llega al valor indicado

    ;Recupero el valor de DS del enunciado
    MOV AX, 01001001b ;Direccionamiento inmediato, auxiliar dado que no se puede emplear direccionamiento inmediato para DS
    
    MOV DS, AX ;Direccionamiento por registro, para cargar 01001001b (que corresponde con el valor de AX guardado en la linea anterior) en DS 


    MOV AX, [SI] ;Direccionamiento directo, cargar en AX el contenido de la dirección de memoria apuntada por SI
    
    MOV BX, [BP] + 10 ;Direccionamiento relativo a base, para cargar en BX el contenido de la dirección de memoria que está 10 bytes por encima de la dirección apuntada por BP
    

    ;EJERCICIO 2, para probar con el debugger
    ;Cargo los datos del enunciado
    ;MOV AX, 0362H
    ;MOV DS, AX ;Cargamos DS
    
    ;MOV AX, 0300H
    ;MOV ES, AX ;Cargamos ES

    ;MOV BX, 0212H ;Cargamos BX
    ;MOV DI, 1010H;Cargamos DI
    ;Datos Cargados

    ;MOV BYTE PTR DS:[0211H], 99h ;Valor de prueba para comprobar
    ;MOV AL, DS:[0211H] ;En AL debería estar 99h

    ;MOV WORD PTR [BX], 22h ;Valor de prueba para comprobar
    ;MOV AX,[BX] ;En AX debería estar 22h
    ;MOV [DI], AL
    ;MOV CL, [DI] ;Para comprobar si a ido todo bien, si es así debería haber un 22h en cl

; FIN DEL PROGRAMA
MOV AX, 4C00H
INT 21H
INICIO ENDP
; FIN DEL SEGMENTO DE CODIGO
CODE ENDS
; FIN DEL PROGRAMA INDICANDO DONDE COMIENZA LA EJECUCION
END INICIO 