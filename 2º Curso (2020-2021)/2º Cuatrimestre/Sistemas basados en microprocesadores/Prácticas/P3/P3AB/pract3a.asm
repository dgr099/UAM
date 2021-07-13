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
		PUBLIC _pintaPixel
        PUBLIC _pintaCuadrado	
	_MAIN ENDP 

; procedimiento pinta pixel
    ;pintaPixel(color,pos_x, pos_y)
    _pintaPixel proc far

    ;Guardamos los valores con los que llega
    PUSH BP ;guardo el valor de BP
    MOV BP, SP ;Cargo en BP el valor del stack pointer
    MOV AH, 0Fh ;Obtenemos el modo de vídeo
    INT 10h ;Interrupción de video
    MOV _MV, AL ;Guardamos el modo video cn el que vino

    mov ah, 00h ; configuramos entrada a modo video
    mov al, 12h ; 640x480 16 color graphics (VGA)
    int 10h 

	; configuramos color fondo verde 0010b
	mov ah, 0bh
	mov bh, 00h
	mov bl, 02h; 0 color negro 2 ; color verde
	int 10h

    ;Int pintar punto en pantalla: AH=0Ch AL = Color, BH = NumPag, CX = x, DX = y
    mov ah, 0Ch
    mov bh, 00h ;Número de página lo dejamos a 0
    ; Por como el cabacera, con el valor más bajo en la pila es color
    mov al, [BP + 6] ; color rojo 4, color blanco 15
    
    ;Si es mayor que 15 no puede ser porque solo hay 15 colores
    CMP AL, 15 ;Comparamos si se ha pasado de colores
    JG fin_mal

    ;Si es menor que 0 no puede ser porque no hay colores negativos
    CMP AL, 0 ;Comparamos si ha puesto un color negativo
    JL fin_mal

    ; Lo siguiente es la pos_x
    mov cx, [BP + 6 + 2] ;Posición X donde pintar el punto
    ;Comparamos si ha puesto un pixel fuera de rango
    CMP CX, 640 ;Comparamos si se pasó de 640 que son los píxeles en x
    JG fin_mal
    CMP CX, 0 ;Comparamos si ha puesto un píxel negativo
    JL fin_mal
    ;Por último la posición Y
    mov dx, [BP + 6 + 2 + 2] ; Posición Y donde pintar el punto
    ;Comprobamos si puso un píxel fuera de rango
    CMP DX, 480 ;Comparamos si se pasó de 480
    JG fin_mal
    CMP DX, 0 ;Comparamos si ha puesto un píxel negativo
    JL fin_mal
    int 10h 

    ;Una vez pintado hacemos una espera activa
    MOV CX, 0FH ;1 second = F:4240H --> 3 seconds 2D:C6C0
    MOV DX, 4240H
    MOV AH, 86H ;int 15h con AH=86h para espera de microsegundos en cx:dx
    INT 15H 

    ;Si hemos llegado hasta aqí es que todo correcto
    PUSH 0

    ;Wait tecla para debugeo
    ;MOV AH, 00h
    ;INT 16h


    ;Fin
    ;Recuperamos el modo vino con el que llego
    final_pintaPixel:
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
    JMP final_pintaPixel
    _pintaPixel endp

    ;procedimiento pinta cuadro
                   ;6      ;8     ;10    ;12
    ;pintaCuadrado(color, tamano, pos_x, pos_y);
    _pintaCuadrado PROC FAR
    ;Guardamos los valores con los que llega
    PUSH BP ;guardo el valor de BP
    MOV BP, SP ;Cargo en BP el valor del stack pointer
    MOV AH, 0Fh ;Obtenemos el modo de vídeo
    INT 10h ;Interrupción de video
    MOV _MV, AL ;Guardamos el modo video con el que vino

    mov ah, 00h ; configuramos entrada a modo video
    mov al, 12h ; 640x480 16 color graphics (VGA)
    int 10h 

	; configuramos color fondo verde 0010b
	mov ah, 0bh
	mov bh, 00h
	mov bl, 02h; 0 color negro 2 ; color verde
	int 10h
    
    ;1º comprobación de parámetros
    ;Comprobamos si el color está entre 0 y 15 incluidos
    JMP inicio_par

    fin_mal_pC:
    PUSH -1 ;Ponemos en la pila el -1 de error 
    JMP final_pintaCuadro

    inicio_par:
    ;Comprobamos los colores
    MOV AX, [BP + 6] 
    CMP AX, 15
    JG fin_mal_pC
    CMP AX, 0
    JL fin_mal_pC

    ;Comprobamos si el tamaño es positivo
    MOV BX, [BP + 8] ;Guardamos el tamaño
    CMP BX, 0 ;Si el tamaño del cuadrado es negativo
    JL fin_mal_pC
    
    ;Comprobamos si se puede dibujar la parte horizontal del cuadrado
    MOV CX, [BP + 10] ;Guardamos la posición x
    CMP CX, 640 ;Comparamos si se pasó de 640
    JG fin_mal_pC ;Final malo pinta cuadro
    CMP CX, 0 ;Comparamos si ha puesto un píxel negativo
    JL fin_mal_pC
    ADD CX, BX ;Comprobamos que exista hueco para hacer el cuadrado
    CMP CX, 640
    JG fin_mal_pC

    ;Comprobamos si se puede dibujar la parte vertical del cuadrado
    MOV BX, [BP + 8] ;Guardamos el tamaño
    MOV CX, [BP + 12] ;Guardamos la posición x
    CMP CX, 480 ;Comparamos si se pasó de 480
    JG fin_mal_pC ;Final malo pinta cuadro
    CMP CX, 0 ;Comparamos si ha puesto un píxel negativo
    JL fin_mal_pC
    ADD CX, BX ;Comprobamos que exista hueco para hacer el cuadrado
    CMP CX, 480
    JG fin_mal_pC

    ;Una vez comprobado los parámetros pasamos a dibujar el cuadrado
    MOV BX, [BP + 8] ;Guardamos el tamaño
    MOV CX, [BP + 10] ;Cargamos la posición x
    MOV DX, [BP + 12] ;Cargamos la posición y

    MOV DI, CX
    ADD DI, BX ;Delimitador de X si empieza en el 1 y tiene tamaño 4, imprime hasta el 5
    MOV SI, DX 
    ADD SI, BX ;Delimitador de la Y
    ;En CX el inicio del bucle y en DI el final

    ;while(y <= delimitador vertical){
        ;x al principio
        ;while(x<=delimitador horizontal){
            ;print(x,y)
        ;}
    ;}
    bucle0:
        ;Pintar linea horizontal
        CMP DX, SI ;Compruebas si ya has llegado al final del eje vertical
        JG fin_bucle0 ;Si ya has dibujado todas las filas termina
        MOV CX, [BP + 10] ;Cargamos el inicio de las x
        bucle1:
        ;Pintamos puntos hasta pasarnos
        CMP CX, DI
        JG fin_bucle1 ;Si ya hemos terminado de imprimir el primer lado salimos
        ;Int pintar punto en pantalla: AH=0Ch AL = Color, BH = NumPag, CX = x, DX = y
        mov ah, 0Ch
        ;mov al, [BP + 6] ;el color ya está cargado y AL no cambia
        mov bh, 00h ;página a 0
        ;mov cx, 50 ;Posición X donde pintar el punto ya están cargados los valores
        ;mov dx, 45 ; Posición Y donde pintar el punto ya están cargados los valores
        int 10h
        INC CX ;Incrementamos en 1 la posición de x
        JMP bucle1 ;Volvemos al inicio del bucle para comprobar si ya hemos terminado
        fin_bucle1:
        INC DX ;Pasamos a la siguiente fila
        JMP bucle0
    fin_bucle0:

    ;Una vez pintado hacemos una espera activa
    MOV CX, 0FH ;1 second = F:4240H --> 3 seconds 2D:C6C0
    MOV DX, 4240H
    MOV AH, 86H ;int 15h con AH=86h para espera de microsegundos en cx:dx
    INT 15H 

    ;Si hemos llegado hasta aqí es que todo correcto así que guardamos el 0 de correcto
    PUSH 0
    final_pintaCuadro:
    ;Recuperamos el correcto
    mov AH, 00h
	MOV AL, _MV
	int 10h
    pop AX ;Valor retorno, será 1 si fue por el final malo y 0 en caso contrario
    pop BP ;Recuperamos el BP
    MOV DX, 0
    MOV CX, 0
    RET
    _pintaCuadrado ENDP
; FIN DEL SEGMENTO DE CODIGO
_TEXT ENDS 
END