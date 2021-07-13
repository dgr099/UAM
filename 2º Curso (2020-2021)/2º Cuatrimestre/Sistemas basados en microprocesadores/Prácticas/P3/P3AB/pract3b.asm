;*
;* Sistemas Basados en Microprocesador
;* 2020-2021
;* Practica 3a
;* 
;*
;* author: David Teófilo Garitagoitia Romero
;*
;* notas: ejemplo vacío
;*********************************************************************/
;PUBLIC _pintaPixel
;PUBLIC _pintaCuadrado
_TEXT SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS: _TEXT
    ; COMIENZO DEL PROCEDIMIENTO PRINCIPAL
	_MAIN PROC 
    _MV DB 0 ;Variable para guardar el modo de vídeo
		;COMIENZO DEL PROGRAMA 
		PUBLIC _pintaListaPixeles
	_MAIN ENDP 

; procedimiento pinta pixel
    ;pintaListaPixeles(num_pix_array, color_fondo, waitMS, ArrayPixelesX, ArrayPixelesY, ArrayColores);
    _pintaListaPixeles proc far
    ;En teoría se hace comprobación en el .c de todos los valores salvo del color de fondo
    ;Guardamos los valores con los que llega

    PUSH BP ;guardo el valor de BP
    MOV BP, SP ;Cargo en BP el valor del stack pointer
    MOV AH, 0Fh ;Obtenemos el modo de vídeo
    INT 10h ;Interrupción de video
    MOV _MV, AL ;Guardamos el modo video cn el que vino

    ;DEBUG
    ;MOV CX, [BP+6] ;Debug cargar el num_pix
    ;MOV CL, [BP+8] ;Debug color de fondo
    ;MOV CX, [BP+10] ;Debug espera 6000000->5B:8D80
    ;MOV CX, [BP+12] ;5B

    ;LDS BX, [BP + 14] ;información vector inicio de la tabla (2 bytes de offset y 2 bytes de segmento)
    ;MOV DX, [BX] ;11 Bh
    ;MOV DX, [BX + 2] ;12 Ch (los int son 2 bytes)

    ;LDS BX, [BP + 18] ;Posicion tabla de elementos de Y (2 bytes de offset y 2 bytes de segmento)
    ;MOV DX, [BX] ;21 15h
    ;MOV DX, [BX + 2] ;22 26h

    ;LDS BX, [BP + 22] ;Posición del array de colores
    ;MOV DL, [BX] ;0
    ;MOV DL, [BX + 1] ;1
    ;DEBUG

    mov ah, 00h ; configuramos entrada a modo video
    mov al, 12h ; 640x480 16 color graphics (VGA)
    int 10h 
    MOV BX, 0
    MOV BL, [BP + 8] ;Cargamos en BL el color de fondo
    CMP BL, 15 ;Comparamos si es mayor que 15
    JG fin_mal ;Si es un color más alto de lo que debe
    CMP BL, 0
    JL fin_mal ;Si es un color negativo

	; configuramos color fondo con el color establecido
	mov ah, 0bh
	mov bh, 00h
	;mov bl, 02h; 0 color negro 2 ; color verde
	int 10h


    MOV CX, [BP + 6] ;Cargamos el número de píxeles
    MOV SI, 0
    MOV DI, 0
    bucle_lista:
    CMP CX, SI ;Si ya has terminado de imprimir
    JE fin_bucle_lista
    PUSH CX ;Guardamos el valor de CX en la pila para poder usar el registro
    mov ah, 0Ch ;Para imprimir un pixel

    PUSH DS ;Guardo el valor de DS ya que lo voy a modificar
    LDS BX, [BP + 14] ;Cargamos el array de posiciones de x
    MOV CX, [BX + DI] ;Posición X donde pintar el punto, las posiciones son enteros, 2 bytes
    POP DS ;Recuperamos DS después de usarlo

    PUSH DS ;Guardo el valor de DS
    LDS BX, [BP + 18] ;Cargamos el array de posiciones de y
    MOV DX, [BX + DI] ; Posición Y donde pintar el punto, las posiciones son enteros, 2 bytes
    POP DS ;Recuperamos DS

    PUSH DS ;Guardamos el valor de DS
    LDS BX, [BP + 22] ;Cargamos el array de colores
    MOV AL, [BX + SI] ;Cargas el color del pixel correspondiente, los colores son de byte a byte
    POP DS ;Recuperamos el valor de DS

    mov bh, 00h ;Paginacion a 0
    int 10h 
    INC SI
    ADD DI, 2
    POP CX ;Recupero el valor de CX
    JMP bucle_lista
    fin_bucle_lista:

    ;Espera
    MOV CX, [BP + 12] ;1 second = F:4240H --> 3 seconds 2D:C6C0
    MOV DX, [BP + 10]
    MOV AH, 86H ;int 15h con AH=86h para espera de microsegundos en cx:dx
    INT 15H 

    ;Si hemos llegado hasta aqí es que todo correcto
    PUSH 0

    ;Wait tecla para debugeo
    ;MOV AH, 00h
    ;INT 16h


    ;Fin
    ;Recuperamos el modo vino con el que llego
    final_pintaListaPixeles:
    mov AH, 00h
	mov AL, _MV 
	int 10h
    pop AX ;Valor retorno, será 1 si fue por el final malo y 0 en caso contrario
    pop BP ;Recuperamos el BP
    MOV DX, 0
    MOV CX, 0
    RET
    fin_mal:
    PUSH -1
    JMP final_pintaListaPixeles
    _pintaListaPixeles endp
_TEXT ENDS 
END