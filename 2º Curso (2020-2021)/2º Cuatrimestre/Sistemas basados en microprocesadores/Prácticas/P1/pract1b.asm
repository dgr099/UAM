;AUTHOR: David Teófilo Garitagoitia Romero
;GROUP: 2262
;**************************************************************************
; SBM 2020. ESTRUCTURA BÁSICA DE UN PROGRAMA EN ENSAMBLADOR
;**************************************************************************
; DEFINICION DEL SEGMENTO DE DATOS
DATOS SEGMENT
MARCADOR DB ?
BEBE DW 0CAFEH
TABLA200 DB 200 dup(?)
ERRORTOTAL1 DB "Este programa se cuelga siempre"

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
    ;MOV [TABLA200 + 060h], ERRORTOTAL1[3] ;Esto no se puede, necesitas pasar por registro para emplear mov
    MOV AH, [ERRORTOTAL1 + 2] ;Se pasa el 3 byte de ERRORTOTAL1 a AH, también se puede hacer ERRORTOTAL1[2]
    MOV TABLA200[060h], AH
   
    MOV AX, [BEBE] ;cargo el contenido de BEBE en AX
    ;Como la tabla está formada de bytes mientrás que AX son dos Bytes así que lo pasamos por partes
    MOV [TABLA200 + 023h], AL ;Copiamos el más significativo en la posición más pequeña (little endian)
    MOV [TABLA200 + 024h], AH ;El más significativo en la más alta
    
    MOV MARCADOR, AL ;Copiamos el más significativo de la variable BEBE en MARCADOR

    ; FIN DE PROGRAMA
    MOV AX, 4C00H
    INT 21H
INICIO ENDP
; FIN DEL SEGMENTO DE CODIGO
CODE ENDS
; FIN DEL PROGRAMA INDICANDO DONDE COMIENZA LA EJECUCION
END INICIO 