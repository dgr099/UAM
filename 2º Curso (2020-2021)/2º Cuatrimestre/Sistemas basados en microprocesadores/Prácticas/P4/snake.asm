; Autor: David Teófilo Garitagoitia Romero
; Grupo 2262
; Práctica 4: Diseño de programas residentes
; DEFINICION DEL SEGMENTO DE DATOS
DATOS SEGMENT
CLR_PANT 	DB 	1BH,"[2","J$" ;para limpiar la pantalla
;mensajes para cuando se tiene un ganador
MensajeAZUL DB "El jugador rojo se ha chocado, azul gana", 10, 13, "$"
MensajeROJO DB "El jugador azul se ha chocado, rojo gana", 10, 13, "$"
PuntosRojo DB "Puntos del jugador Rojo: $"
PuntosAzul DB 10, 13, "Puntos del jugador Azul: $"
;mensaje introductorio para el juego
MensajeINTRO DB "->El jugador rojo se desplaza con awsd", 10, 13, "->El jugador azul se desplaza con jikl", 10, 13, "->Evita salir del recuadro o golpearte contigo mismo o la otra serpiente", 10, 13, "->Comete las naranjas para ganar puntos (tocalas con la cabeza)", 10, 13, 10, 13, "Cuando alguien pierda se congelara la pantalla a la espera", 10, 13,  "de introducir una tecla, despues se mostrara la puntuacion", 10, 13, "del jugador que no murio (gano)", 10, 13, "Introduce tecla para continuar", 10, 13, "$"
MensajeSALIR DB "Saliendo del juego", "$" ;mensaje de salir del juego (q)
    PRojo DB, 0 ;puntos del jugador rojo
    PAzul DB, 0 ;puntos del jugador azul
DATOS ENDS
;**************************
; DEFINICION DEL SEGMENTO PARA EL ASCII donde retorna el numero a ascii para imprimir los puntos
ASCIINUMBER SEGMENT
  ASCII_N DB 6 dup(?) ;Con dos bytes el máximo es el FFFF que corresponde al 65535, y otro byte para el $
ASCIINUMBER ENDS

;**************************
; DEFINICION DEL SEGMENTO DE PILA
PILA SEGMENT STACK "STACK"
 DB 40H DUP (0) ;ejemplo de inicialización, 64 bytes inicializados a 0
PILA ENDS
;**************************
; DEFINICION DEL SEGMENTO EXTRA
EXTRA SEGMENT
EXTRA ENDS
;**************************
; DEFINICION DEL SEGMENTO DE CODIGO
CODE SEGMENT
ASSUME CS: CODE, DS: DATOS, ES: EXTRA, SS: PILA
_MV DB 0
; COMIENZO DEL PROCEDIMIENTO PRINCIPAL
INICIO PROC 
; INICIALIZA LOS REGISTROS DE SEGMENTO CON SU VALOR
    MOV AX, DATOS
    MOV DS, AX
    MOV AX, PILA
    MOV SS, AX
    MOV AX, EXTRA
    MOV ES, AX
    MOV SP, 64 
    ; CARGA EL PUNTERO DE PILA CON EL VALOR MAS ALTO
    ; FIN DE LAS INICIALIZACIONES
    ; COMIENZO DEL PROGRAMA

    ;Ponemos el modo video
    MOV CX, 0
    MOV PRojo, CL
    MOV PAzul, CL
    MOV AH, 0Fh ;Obtenemos el modo de vídeo
    INT 10h ;Interrupción de video
    MOV _MV, AL ;Guardamos el modo video cn el que vino
    ;mov ah, 00h ; configuramos entrada a modo video
    ;mov al, 0Dh ; 320x200 16 color graphics (EGA,VGA) 
    ;int 10h 
    MOV DX, OFFSET CLR_PANT ;limpiamos la pantalla
    MOV AH,09H
    INT 21H 
    ;mostramos el intro
    MOV DX, OFFSET MensajeINTRO
    MOV AH,09H
    INT 21H 
    MOV AH, 00h
    INT 16h ;espero tecla para seguir

	; configuramos color fondo verde 0010b
	mov ah, 0bh
	mov bh, 00h
	mov bl, 00h; Fondo negro
	int 10h
    ;iniciamos ambos moviendose hacia arriba
    MOV DI, 0
    MOV BL, 'w'
    MOV BH, 'i'
    JMP bucle
    
    gana_azul:
    mov AH, 00h
	mov AL, _MV 
	int 10h
    MOV DX, OFFSET MensajeAZUL
    MOV AH,09H
    INT 21H 
    JMP fin_ganador

    gana_rojo:
    mov AH, 00h
	mov AL, _MV 
	int 10h
    MOV DX, OFFSET MensajeROJO
    MOV AH,09H
    INT 21H 
    JMP fin_ganador

    fin_ganador:
    MOV DX, OFFSET PuntosRojo
    MOV AH,09H
    INT 21H 
    MOV AX, 0
    MOV AL, PRojo
    call CAMBIA_ASCII
    MOV DS, DX
    ;Imprimimos el número
    MOV DX, BX
    MOV AH,09H
    INT 21H
    MOV AX, DATOS
    MOV DS, AX ;recupero mi segmento de datos 
    MOV DX, OFFSET PuntosAzul
    MOV AH,09H
    INT 21H 
    MOV AX, 0
    MOV AL, PAzul
    call CAMBIA_ASCII
    MOV DS, DX
    ;Imprimimos el número
    MOV DX, BX
    MOV AH,09H
    INT 21H
    MOV AX, DATOS
    MOV DS, AX
    ;esperamos lo suficiente para que la interrupción vuelva a poner todos sus valores originales
	MOV     CX, 0h ; CX:DX forman el tiempo de espera: 1 second = F:4240H --> 3 seconds 2D:C6C0 h
	MOV     DX, 0D6D8h
	MOV     AH, 86H ;int 15h con AH=86h para espera de microsegundos en cx:dx
	INT     15H
    MOV BL, 'q'
    MOV AX, 4C00H
    INT 21H

    ;Ponemos la posición del 1º cuadrado
    bucle:
    MOV CX, 0
    MOV AH, 00h ;Lee la tecla pulsada
    INT 16h
    ;comprobamos retorno:
    ;CX==1 ha perdido el rojo
    ;CX==2 ha perdido el azul
    ;CX==3 punto para el rojo
    ;CX==4 punto para el azul
    CMP CX, 1 ;si retorna el que el azul ha ganado (rojo pierde)
    JE gana_azul

    CMP CX, 2 ;si retorna que el rojo ha ganado (azul pierde)
    JE gana_rojo

    CMP CX, 3 ;si retorna que el rojo ha ganado un punto
    JE punto_rojo

    CMP CX, 4 ;si retorna que el azul ha ganado un punto
    JE punto_azul

    CMP AL, 'q' ;si pide salir
    JE salir

    cambio_dir: ;mira a quien de los dos rojos (BL) o azul (BH) ha pedido cambiar 
    CMP AL, 'a'
    JE cambio_rojo
    CMP AL, 's'
    JE cambio_rojo
    CMP AL, 'w'
    JE cambio_rojo
    CMP AL, 'd'
    JE cambio_rojo

    CMP AL, 'j'
    JE cambio_azul
    CMP AL, 'k'
    JE cambio_azul
    CMP AL, 'i'
    JE cambio_azul
    CMP AL, 'l'
    JE cambio_azul
    JMP bucle ;si no es ninguna de las anteriores se ignora el input

    cambio_rojo:
    MOV BL, AL
    JMP bucle

    cambio_azul:
    MOV BH, AL
    JMP bucle

    salir:
    MOV BL, AL ;para que la int sepa que debe terminar le manda la q
    mov AH, 00h
	mov AL, _MV 
    int 10h ;recuperamos el modo de video
    MOV DX, OFFSET MensajeSALIR ;mostramos el mensaje
    MOV AH,09H
    INT 21H 
    ;Int15H espera activa en microsegundos: 1 millon us = 1 segundo
    ;esperamos lo suficiente para que la interrupción vuelva a poner todos sus valores originales
	MOV     CX, 0h ; CX:DX forman el tiempo de espera: 1 second = F:4240H --> 3 seconds 2D:C6C0 h
	MOV     DX, 0D6D8h
	MOV     AH, 86H ;int 15h con AH=86h para espera de microsegundos en cx:dx
	INT     15H
    fin:
    MOV AX, 4C00H
    INT 21H

punto_rojo: ;si retorna la interrupción que nuevo punto para rojo se incrementa los puntos del rojo
    MOV CL, PRojo
    INC CL
    MOV PRojo, CL
    MOV CX, 0
    JMP cambio_dir ;vuelve al bucle para ver si debe cambiar la direccion

punto_azul: ;si retorna la interrupción que nuevo punto de azul se incrementan los puntos de azul
    MOV CL, PAzul
    INC CL
    MOV PAzul, CL
    MOV CX, 0
    JMP cambio_dir ;vuelve al bucle para ver si debe cambiar la direccion

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
INICIO ENDP

;ESPACIO PARA SUBRUTINAS
; FIN DEL SEGMENTO DE CODIGO
CODE ENDS
; FIN DEL PROGRAMA INDICANDO DONDE COMIENZA LA EJECUCION
END INICIO