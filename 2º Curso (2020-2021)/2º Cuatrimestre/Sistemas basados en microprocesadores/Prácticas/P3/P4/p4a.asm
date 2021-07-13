; Autor: David Teófilo Garitagoitia Romero
; Grupo 2262
; Práctica 4: Diseño de programas residentes


;Enunciado:
;Diseñar un programa residente que instale dos vectores de interrupción, en la INT 55h y la int 57h
;proporcionando servicios en AL (position X) y AH (posición Y), para imprimir en pantalla (modo VGA
;320x200) un cuadrado de dimensión 10x10 pixels. La int 55h imprimirá el cuadrado en azul y la int
;57h en rojo. 
codigo SEGMENT
ASSUME cs : codigo
ORG 256 ;la primera instrucción ejecutable debe estár en la dirección 256 respecto al orifen del segmento
;Implementar una rutina de servicio a la interrupción 55h y 57h, que ofrezca los servicios

;Cuando se ejecute sin parámetros, deberá imprimir el estado de instalación del driver, el
    ;nombre del autor y las instrucciones de uso.

;Cuando se ejecute con el parámetro /I, instale el driver caso que no lo esté ya

;Cuando se ejecute con el parámetro /D, desinstale el driver caso de estar instalado 

inicio: jmp instalador
; Variables globales
    textodesinstalar DB "Desinstalado$"
    textoinstalar DB "Instalacion terminada$"
    textoinstalado DB "Instalado Autor D.T. Garitagoitia Romero", 10, 13, "uso:", 10, 13,  "->int 55h, 57h coordenada del cuadrdado en AX (AL=x, AH=y) con modo video", 10, 13, "->int 1ch recibe en BX la siguiente direccion de las serpientes", 10, 13, "retorna resultado en CX$"
    textoError DB "Error en el proceso (operacion hecha anteriormente o parametros de entrada no validos)$"
    MensajeROJOPierde DB 1BH,"[1;5fEl jugador rojo pierde$", 10, 13
    MensajeAZULPierde DB 1BH,"[1;5fEl jugador azul pierde$", 10, 13
    MensajeFINAL DB 1BH,"[2;2fPresione tecla para continuar$"
    ticks DW 18 ;aproximamos un segundo 18 este se ira decrementando cada los 15 segundos
    tick_t DW 18 ;para volver a restaurar los ticks
    tick_t_aux DW 18 ;para recuperar el valor de ticks
    ticks_2 DW 182 ;tiempo restante para poner un cuadrado más 18.2 veces por segundo, 182 veces en 10 segundos
    ticks_t2 DW 182 ;para restaurar los ticks 2
    ticks_3 DW 273 ;15*18.2
    ticks_t3 DW 273
    punto db 0 ;1 si alguien ha conseguido un punto
    cuadrados DW 0 ;números de cuadrados a imprimir - 1 
    CoordenadasR DB 200d, 100d, 47*2 dup(?) ;lista de los cuadrados de la snake roja
    CoordenadasA DB 50d, 100d, 47*2 dup(?) ;lista de los cudrados de la sanke azul
    n_rec DB 0 ;recompensas por pantalla, cuando sea 0 vuelve a poner dos recompensas
    Recompensa1 DB ?, ?
    Recompensa2 DB ?, ?
    fin_juego_por_rojo DB 0

    ; Rutina de servicio a la interrupción del color rojo
    rsi1 PROC Far ;procedimiento de la rutina de servicio a la interrupción para el rojo
    PUSH BP ;Guardo BP
    PUSH CX ;guardo CX
    PUSH BX ;guardo BX
    PUSH DX ;guardo este por si lo necesito
    PUSH AX ;guardo el valor de AX ya que lo voy a utilizar
    ;1º comprobación de parámetros
    ;Comprobamos si el color está entre 0 y 15 incluidos
    JMP inicio_par

    fin_mal: ;devuelvo -1 si hay algún fallos
    POP AX
    POP DX
    POP BX
    POP CX
    POP BP
    MOV AX, -1
    IRET

    inicio_par:

    POP CX ;Recojo en CX el valor de AX que tenía la posición
    PUSH CX ;Vuelvo a guardar el valor de AX
    ;Comprobación de parámetros
    MOV BL, CH ;Ponemos en BL la coordenada Y para hacer la comprobación de parámetros
    MOV CH, 0
    MOV BH, 0
    ;Coordenada X
    CMP CX, 0
    JL fin_mal ;Si la coordenada X es negativa
    CMP CX, 240d ;El máximo que nos dice el enunciado
    JG fin_mal ;Si excede el máximo desde el que se puede imprimir el cuadrado
    
    ;Coordenada Y
    CMP BX, 0
    JL fin_mal ;Si la coordenada X es negativa
    CMP BX, 180d ;El máximo que nos dice el enunciado
    JG fin_mal ;Si excede el máximo desde el que se puede imprimir el cuadrado
    
    MOV CH, BL ;Recuperamos las coordenadas originales
    MOV BX, CX ;Ponemos en BX las coordenadas originales e incrementamos en 10 cada una para tener los limitadores
    ADD BL, 10 ;Delimitador de hasta donde imprimir
    ADD BH, 10 ;Delimitador de hasta donde imprimir

    ;while(y <= delimitador vertical){
        ;x al principio
        ;while(x<=delimitador horizontal){
            ;print(x,y)
        ;}
    ;}

    MOV AL, 0Ch ;EL color es siempre el rojo
    MOV DX, 0
    bucle0:
        ;Pintar linea Vertical
        ;Hacemos el push para quitar valores negativos
        PUSH CX
        PUSH BX
        MOV CH, 0
        MOV BH, 0
        CMP CX, BX ;Compruebas si has terminado de imprimir el cuadrado (todas las columnas pintadas)
        POP BX
        POP CX
        JG fin_bucle0 ;Si ya has dibujado todas las filas termina
        MOV DL, CH ;Cargas el inicio de las Y

        bucle1_2:
        ;Pintamos puntos hasta pasarnos
        PUSH BX
        MOV BL, BH
        MOV BH, 0
        CMP DX, BX ;Comprobamos si ya hemos terminado de imprimir esta columna (La posicion Y es mayor que el delimitador)
        POP BX
        JG fin_bucle1_2 ;Si ya hemos terminado de imprimir el primer lado salimos
        ;Int pintar punto en pantalla: AH=0Ch AL = Color, BH = NumPag, CX = x, DX = y
        mov ah, 0Ch
        PUSH BX ;pongo bx en la pila para poder usarlo (por lo de la página y tal)
        PUSH CX ;Guardamos CX que contiene las posiciones
        MOV CH, 0
        mov bh, 00h ;página a 0
        ;mov cx, 50 ;Posición X donde pintar el punto ya están cargados los valores
        ;mov dx, 45 ; Posición Y donde pintar el punto ya están cargados los valores
        int 10h
        POP CX ;recupero las posiciones
        POP BX ;recupero bx el delimitador
        INC DL ;Incrementamos en 1 la posición de x
        JMP bucle1_2 ;Volvemos al inicio del bucle para comprobar si ya hemos terminado
        fin_bucle1_2:
        INC CL ;Pasamos a la siguiente Columna
        JMP bucle0
    fin_bucle0:
    POP AX
    POP DX
    POP BX
    POP CX
    POP BP
    iret
    rsi1 ENDP

    ;Rutina de servicio a la interrupcion del color azul
    rsi2 PROC Far ;procedimiento de la rutina de servicio a la interrupción para el rojo
    PUSH BP ;Guardo BP
    PUSH CX ;guardo CX
    PUSH BX ;guardo BX
    PUSH DX ;guardo este por si lo necesito
    PUSH AX ;guardo el valor de AX ya que lo voy a utilizar
    ;1º comprobación de parámetros
    ;Comprobamos si el color está entre 0 y 15 incluidos
    JMP inicio_par_2

    fina_mal_2: ;devuelvo -1 si hay algún fallos
    POP AX
    POP DX
    POP BX
    POP CX
    POP BP
    MOV AX, -1
    IRET

    inicio_par_2:

    POP CX ;Recojo en CX el valor de AX que tenía la posición
    PUSH CX ;Vuelvo a guardar el valor de AX
    ;Comprobación de parámetros
    MOV BL, CH ;Ponemos en BL la coordenada Y para hacer la comprobación de parámetros
    MOV CH, 0
    MOV BH, 0
    ;Coordenada X
    CMP CX, 0
    JL fina_mal_2 ;Si la coordenada X es negativa
    CMP CX, 240d ;El máximo que nos dice el enunciado
    JG fina_mal_2 ;Si excede el máximo desde el que se puede imprimir el cuadrado
    
    ;Coordenada Y
    CMP BX, 0
    JL fina_mal_2 ;Si la coordenada X es negativa
    CMP BX, 180d ;El máximo que nos dice el enunciado
    JG fina_mal_2 ;Si excede el máximo desde el que se puede imprimir el cuadrado
    
    MOV CH, BL ;Recuperamos las coordenadas originales
    MOV BX, CX ;Ponemos en BX las coordenadas originales e incrementamos en 10 cada una para tener los limitadores
    ADD BL, 10 ;Delimitador de hasta donde imprimir
    ADD BH, 10 ;Delimitador de hasta donde imprimir

    ;while(y <= delimitador vertical){
        ;x al principio
        ;while(x<=delimitador horizontal){
            ;print(x,y)
        ;}
    ;}

    MOV AL, 09h ;EL color es siempre el rojo
    MOV DX, 0
    bucle0_2:
        ;Pintar linea Vertical
        ;Hacemos el push para quitar valores negativos
        PUSH CX
        PUSH BX
        MOV CH, 0
        MOV BH, 0
        CMP CX, BX ;Compruebas si has terminado de imprimir el cuadrado (todas las columnas pintadas)
        POP BX
        POP CX
        JG fin_bucle0_2 ;Si ya has dibujado todas las filas termina
        MOV DL, CH ;Cargas el inicio de las Y

        bucle1_2_2:
        ;Pintamos puntos hasta pasarnos
        PUSH BX
        MOV BL, BH
        MOV BH, 0
        CMP DX, BX ;Comprobamos si ya hemos terminado de imprimir esta columna (La posicion Y es mayor que el delimitador)
        POP BX
        JG fin_bucle1_2_2 ;Si ya hemos terminado de imprimir el primer lado salimos
        ;Int pintar punto en pantalla: AH=0Ch AL = Color, BH = NumPag, CX = x, DX = y
        mov ah, 0Ch
        PUSH BX ;pongo bx en la pila para poder usarlo (por lo de la página y tal)
        PUSH CX ;Guardamos CX que contiene las posiciones
        MOV CH, 0
        mov bh, 00h ;página a 0
        ;mov cx, 50 ;Posición X donde pintar el punto ya están cargados los valores
        ;mov dx, 45 ; Posición Y donde pintar el punto ya están cargados los valores
        int 10h
        POP CX ;recupero las posiciones
        POP BX ;recupero bx el delimitador
        INC DL ;Incrementamos en 1 la posición de x
        JMP bucle1_2_2 ;Volvemos al inicio del bucle para comprobar si ya hemos terminado
        fin_bucle1_2_2:
        INC CL ;Pasamos a la siguiente Columna
        JMP bucle0_2
    fin_bucle0_2:
    ;Recupero todos los registros que he utilizado
    POP AX
    POP DX
    POP BX
    POP CX
    POP BP
    iret
    rsi2 ENDP

    ;10 pixeles por segundo (aprox 18 ticks)
rsi3 PROC FAR
    PUSH AX ;guardo ax
    PUSH BX ;en bx recibo la última dirección (en bL la del azul y en bH la del rojo)
    PUSH CX
    PUSH DX
    PUSH BP
    PUSH SI
    PUSH DI
    MOV AL, 0
    MOV punto, AL
    CMP CX, 1 ;si ha perdido el rojo
    JE fin_q
    CMP CX, 2 ;si ha perdido el azul
    JE fin_q
    ;si alguien ha perdido el juego terminó, toca restablecer parámetros
    CMP BL, 'q' ;si pidió terminar vuelvo a poner todo como estaba al inicio
    JE fin_q
    JMP inicio_int1ch
    fin_q:
    ;reinicio numero de cuadrados
    MOV AX, 0
    MOV cuadrados, AX
    ;reinicio los ticks
    MOV AX, tick_t_aux
    MOV ticks, AX
    MOV tick_t, AX
    MOV AX, ticks_t2
    MOV ticks_2, AX
    MOV AX, ticks_t3
    MOV ticks_3, AX
    XOR BX, BX ;pongo BX a 0
    MOV n_rec, BL ;pongo las recompensas a 0
    ;reinicio las coordenadas
    MOV AL, 200d
    MOV AH, 100d
    MOV WORD PTR CoordenadasR[0], AX
    MOV AL, 50d
    MOV AH, 100d
    MOV WORD PTR CoordenadasA[0], AX
    MOV AX, -1
    ;pongo los siguientes y recompensas a posiciones no válidas
    MOV WORD PTR CoordenadasR[2], AX
    MOV WORD PTR Recompensa1[0], AX
    MOV WORD PTR Recompensa2[0], AX
    MOV WORD PTR CoordenadasA[2], AX
    JMP fin_total
    fin_total:
    POP DI
    POP SI
    POP BP
    POP DX
    POP CX
    POP BX
    POP AX 
    iret
    inicio_int1ch:
    ;actualizamos los ticks para el desplazamiento, aumentar tamaño o velocidad
    ;comprobacion auxiliar para antes de cambiar los ticks
    CMP BH, 'l'
    JG fin_q
    CMP BH, 'i'
    JL fin_q
    MOV AX, ticks
    DEC AX
    MOV ticks, AX

    MOV AX, ticks_2 ;decrementamos el 2º contador para aumentar tamaño
    DEC AX
    MOV ticks_2, AX

    MOV AX, ticks_3 ;decrementamos contador para hacer más rápido
    DEC AX
    MOV ticks_3, AX

    CMP ticks, 0 ;Comprueba si han pasado todos los ticks que corresponden con un segundo
    JG fin_total ;si no han pasado los ticks necesarios para que se actualice
    ;aquí es donde realmente empieza la interrupción
    MOV AX, 0
    MOV AX, tick_t  ;si han pasado los ticks los reestablecemos
    MOV ticks, AX
    CMP ticks_3, 0 ;comprobamos si tenemos que acortar el tiempo de movimiento
    JG inicio_rutina ;si no, vamos al inicio de la rutina
    MOV AX, ticks_t3 ;en caso de que hayan pasado restauramos los ticks
    MOV ticks_3, AX
    PUSH DX ;ponemos los ticks al 90% para que tarde menos en aumentar la posición
    MOV DX, 0
    MOV AX, 0
    MOV DL, BYTE PTR tick_t
    MOV AL, 90
    MUL DL
    MOV DL, 100d
    DIV DL
    POP DX
    MOV AH, 0
    CMP AX, 0
    JLE minimo_1
    MOV tick_t, AX
    JMP inicio_rutina
    minimo_1: ;minimo 1, para que al restar no de un número negativo
    MOV AX, 1
    MOV tick_t, AX
    inicio_rutina:
    CMP n_rec, 0
    JG inicio_dibujo
;si está aqui es que no hay recompensas
    MOV AL, 2
    MOV n_rec, AL
    ;primero la pos x de la 1º
    MOV AH, 00h  ; cojo el tiempo de reloj      
    INT 1AH      
    mov  ax, dx
    xor  dx, dx
    mov  cx, 240    
    div  cx
    MOV Recompensa1[0], BYTE PTR DL
    ;luego la pos y de la 1º
    MOV AH, 00h  ; cojo el tiempo de reloj      
    INT 1AH      
    mov  ax, dx
    xor  dx, dx
    mov  cx, 180 
    div  cx
    MOV Recompensa1[1], BYTE PTR DL
    ;repetimos con la 2º
    ;primero la pos x de la 2º
    MOV AH, 00h  ; cojo el tiempo de reloj      
    INT 1AH      
    mov  ax, dx
    MUL cl
    ADD AX, 0ABh
    xor  dx, dx
    mov  cx, 240    
    div  cx
    MOV Recompensa2[0], BYTE PTR DL
    ;luego la pos y de la 2º
    MOV AH, 00h  ; cojo el tiempo de reloj      
    INT 1AH      
    mov  ax, dx
    MUL cl
    ADD AX, 0CDH
    xor  dx, dx
    mov  cx, 180 
    div  cx
    MOV Recompensa2[1], BYTE PTR DL
    inicio_dibujo:
    ;Guardas la pos inicial de la cabeza
    MOV DX, WORD PTR CoordenadasR[0] ;guardo en DX auxiliar la posición del ultimo rojo antes de la interrupcion
    
    ;comprobamos dirección de rojo
    CMP BL, 'd' ;si quiere ir a la derecha
    JE rojoDer

    CMP BL, 's' ;si quiere ir hacia abajo
    JE rojoAbajo

    CMP BL, 'w' ;si quiere ir hacia arriba
    JE rojoArriba

    CMP BL, 'a' ;si quiere ir a la izq
    JE rojoIzq

    JMP fin_total ;si no, no cambioo ninguna coordenada
    rojoDer:
        MOV AL, BYTE PTR CoordenadasR[0] ;lees la posición X del ultimo cuadrado
        ADD AL, 10 ;sumas 5 a la posición del primero
        MOV BYTE PTR CoordenadasR[0], AL ;actualizas la posición del último
        JMP comp_azul

    rojoIzq:                        ;igual que BP*2
        MOV AL, BYTE PTR CoordenadasR[0] ;lees la posición X del ultimo cuadrado
        Sub AL, 10 ;sumas 5 a la posición del primero
        MOV BYTE PTR CoordenadasR[0], AL ;actualizas la posición del último
        JMP comp_azul

    rojoAbajo:
        MOV AL, BYTE PTR CoordenadasR[1] ;lees la posición Y del ultimo cuadrado
        ADD AL, 10 ;sumas 5 a la posición del primero
        MOV BYTE PTR CoordenadasR[1], AL ;actualizas la posición del último
        JMP comp_azul
    rojoArriba:
        MOV AL, BYTE PTR CoordenadasR[1] ;lees la posición Y del ultimo cuadrado
        SUB AL, 10 ;sumas 5 a la posición del primero
        MOV BYTE PTR CoordenadasR[1], AL ;actualizas la posición del último
        JMP comp_azul
    
    ;comprobamos las azules
    comp_azul:
    MOV CX, WORD PTR CoordenadasA[0] ;guardo en cx la posición original a modo de aux
    CMP BH, 'l' ;si quiere ir a la derecha
    JE azulDer

    CMP BH, 'k' ;si quiere ir hacia abajo
    JE azulAbajo

    CMP BH, 'i' ;si quiere ir hacia arriba
    JE azulArriba

    CMP BH, 'j' ;si quiere ir a la izq
    JE azulIzq

    JMP fin_total ;si no tiene posición valida, termino

    azulDer:
        MOV AL, BYTE PTR CoordenadasA[0] ;lees la posición X del ultimo cuadrado
        ADD AL, 10 ;sumas 5 a la posición del primero
        MOV BYTE PTR CoordenadasA[0], AL ;actualizas la posición del último
        JMP imp_linea

    azulIzq:                        ;igual que BP*2
        MOV AL, BYTE PTR CoordenadasA[0] ;lees la posición X del ultimo cuadrado
        Sub AL, 10 ;sumas 5 a la posición del primero
        MOV BYTE PTR CoordenadasA[0], AL ;actualizas la posición del último
        JMP imp_linea

    azulAbajo:
        MOV AL, BYTE PTR CoordenadasA[1] ;lees la posición Y del ultimo cuadrado
        ADD AL, 10 ;sumas 5 a la posición del primero
        MOV BYTE PTR CoordenadasA[1], AL ;actualizas la posición del último
        JMP imp_linea
    azulArriba:
        MOV AL, BYTE PTR CoordenadasA[1] ;lees la posición Y del ultimo cuadrado
        SUB AL, 10 ;sumas 5 a la posición del primero
        MOV BYTE PTR CoordenadasA[1], AL ;actualizas la posición del último
        JMP imp_linea

    ;imprimes el recuadro de la pantalla
    imp_linea:
    PUSH CX ;guardo CX ya que la empleo en linea
    PUSH DX ;guardas dx ya que la utilizas para la linea
    mov ah, 00h ; configuramos entrada a modo video
    mov al, 0Dh ; 320x200 16 color graphics (EGA,VGA) 
    int 10h 
    ;primero imprimo la línea que marca hasta donde pueden moverse
        mov ah, 0Ch
        ;lee de la pila el valor apropiado para el color
        mov al, 0Fh ; color blanco 1111b
        mov bh, 00h ; numero pagina (dejar siempre a cero)
        mov cx, 240+11 ; posicion X donde pintar
        MOV DX, 0
        bucle_linea1: ;linea vertical
        int 10h ;imprimo
        INC DX
        CMP DX, 180+11
        JNE bucle_linea1
        bucle_linea2:
        int 10h
        DEC CX
        CMP CX, -1
        JNE bucle_linea2
    POP DX
    POP CX
    PUSH AX
    MOV AX, WORD PTR Recompensa1[0]
    ;call recompensas

    PUSH BP ;Guardo BP
    PUSH CX ;guardo CX
    PUSH BX ;guardo BX
    PUSH DX ;guardo este por si lo necesito
    PUSH AX ;guardo el valor de AX ya que lo voy a utilizar

    POP CX ;Recojo en CX el valor de AX que tenía la posición
    PUSH CX ;Vuelvo a guardar el valor de AX
    ;Comprobación de parámetros
    MOV BL, CH ;Ponemos en BL la coordenada Y para hacer la comprobación de parámetros
    MOV CH, 0
    MOV BH, 0
    ;Coordenada X
    CMP CX, 0
    JL fin_bucle0_recompensas ;Si la coordenada X es negativa
    CMP CX, 240d ;El máximo que nos dice el enunciado
    JG fin_bucle0_recompensas ;Si excede el máximo desde el que se puede imprimir el cuadrado
    
    ;Coordenada Y
    CMP BX, 0
    JL fin_bucle0_recompensas ;Si la coordenada X es negativa
    CMP BX, 180d ;El máximo que nos dice el enunciado
    JG fin_bucle0_recompensas ;Si excede el máximo desde el que se puede imprimir el cuadrado
    
    MOV CH, BL ;Recuperamos las coordenadas originales
    MOV BX, CX ;Ponemos en BX las coordenadas originales e incrementamos en 10 cada una para tener los limitadores
    ADD BL, 10 ;Delimitador de hasta donde imprimir
    ADD BH, 10 ;Delimitador de hasta donde imprimir

    ;while(y <= delimitador vertical){
        ;x al principio
        ;while(x<=delimitador horizontal){
            ;print(x,y)
        ;}
    ;}

    MOV AL, 0Eh ;EL color es siempre el amarillo
    MOV DX, 0
    bucle0_recompensas:
        ;Pintar linea Vertical
        ;Hacemos el push para quitar valores negativos
        PUSH CX
        PUSH BX
        MOV CH, 0
        MOV BH, 0
        CMP CX, BX ;Compruebas si has terminado de imprimir el cuadrado (todas las columnas pintadas)
        POP BX
        POP CX
        JG fin_bucle0_recompensas ;Si ya has dibujado todas las filas termina
        MOV DL, CH ;Cargas el inicio de las Y

        bucle1_2_recompensas:
        ;Pintamos puntos hasta pasarnos
        PUSH BX
        MOV BL, BH
        MOV BH, 0
        CMP DX, BX ;Comprobamos si ya hemos terminado de imprimir esta columna (La posicion Y es mayor que el delimitador)
        POP BX
        JG fin_bucle1_2_recompensas ;Si ya hemos terminado de imprimir el primer lado salimos
        ;Int pintar punto en pantalla: AH=0Ch AL = Color, BH = NumPag, CX = x, DX = y
        mov ah, 0Ch
        PUSH BX ;pongo bx en la pila para poder usarlo (por lo de la página y tal)
        PUSH CX ;Guardamos CX que contiene las posiciones
        MOV CH, 0
        mov bh, 00h ;página a 0
        ;mov cx, 50 ;Posición X donde pintar el punto ya están cargados los valores
        ;mov dx, 45 ; Posición Y donde pintar el punto ya están cargados los valores
        int 10h
        POP CX ;recupero las posiciones
        POP BX ;recupero bx el delimitador
        INC DL ;Incrementamos en 1 la posición de x
        JMP bucle1_2_recompensas ;Volvemos al inicio del bucle para comprobar si ya hemos terminado
        fin_bucle1_2_recompensas:
        INC CL ;Pasamos a la siguiente Columna
        JMP bucle0_recompensas
    fin_bucle0_recompensas:
    POP AX
    POP DX
    POP BX
    POP CX
    POP BP


    MOV AX, WORD PTR Recompensa2[0]
    ;call recompensas

    PUSH BP ;Guardo BP
    PUSH CX ;guardo CX
    PUSH BX ;guardo BX
    PUSH DX ;guardo este por si lo necesito
    PUSH AX ;guardo el valor de AX ya que lo voy a utilizar

    POP CX ;Recojo en CX el valor de AX que tenía la posición
    PUSH CX ;Vuelvo a guardar el valor de AX
    ;Comprobación de parámetros
    MOV BL, CH ;Ponemos en BL la coordenada Y para hacer la comprobación de parámetros
    MOV CH, 0
    MOV BH, 0
    ;Coordenada X
    CMP CX, 0
    JL fin_bucle0_recompensas_2 ;Si la coordenada X es negativa
    CMP CX, 240d ;El máximo que nos dice el enunciado
    JG fin_bucle0_recompensas_2 ;Si excede el máximo desde el que se puede imprimir el cuadrado
    
    ;Coordenada Y
    CMP BX, 0
    JL fin_bucle0_recompensas_2 ;Si la coordenada X es negativa
    CMP BX, 180d ;El máximo que nos dice el enunciado
    JG fin_bucle0_recompensas_2 ;Si excede el máximo desde el que se puede imprimir el cuadrado
    
    MOV CH, BL ;Recuperamos las coordenadas originales
    MOV BX, CX ;Ponemos en BX las coordenadas originales e incrementamos en 10 cada una para tener los limitadores
    ADD BL, 10 ;Delimitador de hasta donde imprimir
    ADD BH, 10 ;Delimitador de hasta donde imprimir

    ;while(y <= delimitador vertical){
        ;x al principio
        ;while(x<=delimitador horizontal){
            ;print(x,y)
        ;}
    ;}

    MOV AL, 0Eh ;EL color es siempre el amarillo
    MOV DX, 0
    bucle0_recompensas_2:
        ;Pintar linea Vertical
        ;Hacemos el push para quitar valores negativos
        PUSH CX
        PUSH BX
        MOV CH, 0
        MOV BH, 0
        CMP CX, BX ;Compruebas si has terminado de imprimir el cuadrado (todas las columnas pintadas)
        POP BX
        POP CX
        JG fin_bucle0_recompensas_2 ;Si ya has dibujado todas las filas termina
        MOV DL, CH ;Cargas el inicio de las Y

        bucle1_2_recompensas_2:
        ;Pintamos puntos hasta pasarnos
        PUSH BX
        MOV BL, BH
        MOV BH, 0
        CMP DX, BX ;Comprobamos si ya hemos terminado de imprimir esta columna (La posicion Y es mayor que el delimitador)
        POP BX
        JG fin_bucle1_2_recompensas_2 ;Si ya hemos terminado de imprimir el primer lado salimos
        ;Int pintar punto en pantalla: AH=0Ch AL = Color, BH = NumPag, CX = x, DX = y
        mov ah, 0Ch
        PUSH BX ;pongo bx en la pila para poder usarlo (por lo de la página y tal)
        PUSH CX ;Guardamos CX que contiene las posiciones
        MOV CH, 0
        mov bh, 00h ;página a 0
        ;mov cx, 50 ;Posición X donde pintar el punto ya están cargados los valores
        ;mov dx, 45 ; Posición Y donde pintar el punto ya están cargados los valores
        int 10h
        POP CX ;recupero las posiciones
        POP BX ;recupero bx el delimitador
        INC DL ;Incrementamos en 1 la posición de x
        JMP bucle1_2_recompensas_2 ;Volvemos al inicio del bucle para comprobar si ya hemos terminado
        fin_bucle1_2_recompensas_2:
        INC CL ;Pasamos a la siguiente Columna
        JMP bucle0_recompensas_2
    fin_bucle0_recompensas_2:
    POP AX
    POP DX
    POP BX
    POP CX
    POP BP



    POP AX
    MOV SI, 0
    MOV BP, cuadrados
    bucle_rojo:
        MOV AX, WORD PTR CoordenadasR[SI] ; lees las coordenadas del últio
        int 55h ;imprimes el último
        CMP AX, -1 ;comprueba si el iretorno es que ha perdido el rojo
        JE perd_rojo
        iret_perd_rojo:
        DEC BP
        CMP BP, -1 ;si he terminado de imprimir los cuadrados
        JE fin_bucle_rojo
        ;En DX tienes la anterior posición
        ;haces un swap
        swap_0:
        ADD SI, 2
        MOV AX, WORD PTR CoordenadasR[SI] ;guardas la posición del siguiente
        MOV WORD PTR CoordenadasR[SI], DX ;le pones la del anterior
        MOV DX, AX ;y guardas la que tenía
        JMP bucle_rojo

    perd_rojo: ;esto es para poder imprimir todo la serpiente roja
        push ax
        MOV AL, 1
        MOV BYTE PTR fin_juego_por_rojo, AL
        pop ax
    JMP iret_perd_rojo

    fin_bucle_rojo:
        ;compruebas si hay que añadir un cuadrado
        CMP ticks_2, 0 ;Comprueba si han pasado todos los ticks
        JG continuar
        ;Pones la nueva posición (la del último)
        MOV BP, cuadrados
        CMP BP, 47 ;comprobamos si ya alcanzamos el máximo antes
        JGE continuar
        ADD SI, 2
        MOV WORD PTR CoordenadasR[SI], DX ;le pones la del anterior
        MOV AX, DX
        int 55h ;imprimes ese último cuadrado
        CMP AX, -1
        JE perd_rojo

        continuar:
        MOV DX, CX ;recupero el valor del anterior
        MOV SI, 0
        MOV BP, cuadrados ;leo el número de cuadrados a imprimir
        bucle_azul:
        MOV AX, WORD PTR CoordenadasA[SI] ; lees las coordenadas del últio
        int 57h ;imprimes el último rojo
        CMP AX, -1 ;comprueba si el iretorno es que ha perdido el azul
        JE perd_azul
        iret_per_azul:
        DEC BP
        CMP BP, -1 ;si he terminado de imprimir los cuadrados
        JE fin_bucle_azul
        ;En DX tienes la anterior posición
        ;haces un swap
        ADD SI, 2
        MOV AX, WORD PTR CoordenadasA[SI] ;guardas la posición del siguiente
        MOV WORD PTR CoordenadasA[SI], DX ;le pones la del anterior
        MOV DX, AX ;y guardas
        JMP bucle_azul

    terminar_juego_por_rojo:
        MOV AL, 0
        MOV fin_juego_por_rojo, AL ;vuelvo a restaurar el fin_juego_por_rojo
        POP DI
        POP SI
        POP BP
        POP DX
        POP CX
        POP BX ;en bx recibo la última dirección (en bL la del azul y en bH la del rojo)
        POP AX ;guardo ax
        MOV CX, 1 ;pongo queha perdido el azul
        iret
    
    terminar_juego_por_azul:
        MOV AL, 0
        MOV fin_juego_por_rojo, AL ;vuelvo a restaurar el fin_juego_por_rojo
        POP DI
        POP SI
        POP BP
        POP DX
        POP CX
        POP BX ;en bx recibo la última dirección (en bL la del azul y en bH la del rojo)
        POP AX ;guardo ax
        MOV CX, 2 ;pongo queha perdido el azul
        iret

    perd_azul: ;recupero los valores y pongo CX a 2 pa que sepa el programa
    push ax
    MOV AL, 2
    MOV fin_juego_por_rojo, AL
    pop ax
    JMP iret_per_azul

    fin_bucle_azul:
    ;esto es para poder ver como quedan ambos por pantalla
    CMP fin_juego_por_rojo, 1
    JE terminar_juego_por_rojo ;si ya se perdió por culpa del rojo
    CMP fin_juego_por_rojo, 2
    JE terminar_juego_por_azul ;si ya se perdió por culpa del azul
    ;comprobamos si la cabeza de alguna serpiente está tocando la fruta 1
    ;primero con la roja
    MOV AX, 0
    MOV BX, 0
    MOV CX, 0
    MOV AL, CoordenadasR[0]
    MOV BL, Recompensa1[0]
    CMP BX, AX
    JLE comp_p1_recompensa
    JMP comp_p11_recompensa
    comp_p1_recompensa:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 entonces la está tocandp
    JG fin_comp_recompensa_1_rojo ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp1_recompensa
    comp_p11_recompensa:
    SUB BX, AX
    CMP BX, 10
    JG fin_comp_recompensa_1_rojo
    INC CX
    fin_comp1_recompensa:
    MOV AX, 0
    MOV BX, 0
    MOV AL, CoordenadasR[1]
    MOV BL, Recompensa1[1]
    CMP BX, AX
    JLE comp_p2_recompensa
    JMP comp_p2_1_recompensa
    comp_p2_recompensa:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 entonces la está tocandp
    JG fin_comp_recompensa_1_rojo ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp2_recompensa
    comp_p2_1_recompensa:
    SUB BX, AX
    CMP BX, 10
    JG fin_comp_recompensa_1_rojo
    INC CX
    fin_comp2_recompensa:
    CMP CX, 2
    JNE fin_comp_recompensa_1_rojo
    MOV SI, -1
    MOV WORD PTR Recompensa1[0], SI
    MOV BL, n_rec
    DEC BL
    MOV n_rec, BL
    MOV CX, 3
    PUSH CX ;si tiene recompensa la meto en la pila
    MOV CL, 1
    MOV punto, CL ;pongo punto a 1 para saber que tengo que hacer otro pop
    fin_comp_recompensa_1_rojo:
    CMP punto, 1
    JE fin_comp_recompensa2_1_rojo ;solo se incrementa los puntos de 1 serpiente por turno
    ;comprobamos la cabeza roja con la recompensa2
    MOV AX, 0
    MOV BX, 0
    MOV CX, 0
    MOV AL, CoordenadasR[0]
    MOV BL, recompensa2[0]
    CMP BX, AX
    JLE comp_p1_recompensa2
    JMP comp_p11_recompensa2
    comp_p1_recompensa2:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 entonces la está tocandp
    JG fin_comp_recompensa2_1_rojo ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp1_recompensa2
    comp_p11_recompensa2:
    SUB BX, AX
    CMP BX, 10
    JG fin_comp_recompensa2_1_rojo
    INC CX
    fin_comp1_recompensa2:
    MOV AX, 0
    MOV BX, 0
    MOV AL, CoordenadasR[1]
    MOV BL, recompensa2[1]
    CMP BX, AX
    JLE comp_p2_recompensa2
    JMP comp_p2_1_recompensa2
    comp_p2_recompensa2:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 entonces la está tocandp
    JG fin_comp_recompensa2_1_rojo ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp2_recompensa2
    comp_p2_1_recompensa2:
    SUB BX, AX
    CMP BX, 10
    JG fin_comp_recompensa2_1_rojo
    INC CX
    fin_comp2_recompensa2:
    CMP CX, 2
    JNE fin_comp_recompensa2_1_rojo
    MOV SI, -1
    MOV WORD PTR recompensa2[0], SI
    MOV BL, n_rec
    DEC BL
    MOV n_rec, BL
    MOV CX, 3
    PUSH CX ;si tiene recompensa2 la meto en la pila
    MOV CL, 1
    MOV punto, CL ;pongo punto a 1 para saber que tengo que hacer otro pop
    fin_comp_recompensa2_1_rojo:
    cmp punto, 1
    JE fin_comp_recompensa_azul_1_azul ;salto auxiliar que despues saltará al fin de comprobaciones de puntos
    ;turno de las comprobaciones de recompensa con azules
    MOV AX, 0
    MOV BX, 0
    MOV CX, 0
    MOV AL, CoordenadasA[0]
    MOV BL, recompensa1[0]
    CMP BX, AX
    JLE comp_p1_recompensa_azul
    JMP comp_p11_recompensa_azul
    comp_p1_recompensa_azul:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 entonces la está tocandp
    JG fin_comp_recompensa_azul_1_azul ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp1_recompensa_azul
    comp_p11_recompensa_azul:
    SUB BX, AX
    CMP BX, 10
    JG fin_comp_recompensa_azul_1_azul
    INC CX
    fin_comp1_recompensa_azul:
    MOV AX, 0
    MOV BX, 0
    MOV AL, CoordenadasA[1]
    MOV BL, recompensa1[1]
    CMP BX, AX
    JLE comp_p2_recompensa_azul
    JMP comp_p2_1_recompensa_azul
    comp_p2_recompensa_azul:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 entonces la está tocandp
    JG fin_comp_recompensa_azul_1_azul ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp2_recompensa_azul
    comp_p2_1_recompensa_azul:
    SUB BX, AX
    CMP BX, 10
    JG fin_comp_recompensa_azul_1_azul
    INC CX
    fin_comp2_recompensa_azul:
    CMP CX, 2
    JNE fin_comp_recompensa_azul_1_azul
    MOV SI, -1
    MOV WORD PTR recompensa1[0], SI
    MOV BL, n_rec
    DEC BL
    MOV n_rec, BL
    MOV CX, 4
    PUSH CX ;si tiene recompensa_azul la meto en la pila
    MOV CL, 1
    MOV punto, CL ;pongo punto a 1 para saber que tengo que hacer otro pop
    fin_comp_recompensa_azul_1_azul:
    CMP punto, 1
    JE inicio_compr_posiciones ;solo se incrementa los puntos de 1 serpiente por turno
    ;comprobamos la cabeza roja con la recompensa_azul2
    MOV AX, 0
    MOV BX, 0
    MOV CX, 0
    MOV AL, CoordenadasA[0]
    MOV BL, recompensa2[0]
    CMP BX, AX
    JLE comp_p1_recompensa_azul2
    JMP comp_p11_recompensa_azul2
    comp_p1_recompensa_azul2:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 entonces la está tocandp
    JG fin_comp_recompensa_azul2_1_azul ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp1_recompensa_azul2
    comp_p11_recompensa_azul2:
    SUB BX, AX
    CMP BX, 10
    JG fin_comp_recompensa_azul2_1_azul
    INC CX
    fin_comp1_recompensa_azul2:
    MOV AX, 0
    MOV BX, 0
    MOV AL, CoordenadasA[1]
    MOV BL, recompensa2[1]
    CMP BX, AX
    JLE comp_p2_recompensa_azul2
    JMP comp_p2_1_recompensa_azul2
    comp_p2_recompensa_azul2:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 entonces la está tocandp
    JG fin_comp_recompensa_azul2_1_azul ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp2_recompensa_azul2
    comp_p2_1_recompensa_azul2:
    SUB BX, AX
    CMP BX, 10
    JG fin_comp_recompensa_azul2_1_azul
    INC CX
    fin_comp2_recompensa_azul2:
    CMP CX, 2
    JNE fin_comp_recompensa_azul2_1_azul
    MOV SI, -1
    MOV WORD PTR recompensa2[0], SI
    MOV BL, n_rec
    DEC BL
    MOV n_rec, BL
    MOV CX, 4
    PUSH CX ;si tiene recompensa_azul2 la meto en la pila
    MOV CL, 1
    MOV punto, CL ;pongo punto a 1 para saber que tengo que hacer otro pop
    fin_comp_recompensa_azul2_1_azul:


    ;fin comprobaciones de azul
    inicio_compr_posiciones:
    MOV SI, 0
    MOV DI, 0
    MOV BX, 0
    ;despues de imprimir las nuevas posiciones compruebas si están chocando
    ;1º Comprobacion de rojo con azul
    MOV CX, 0
    MOV BP, cuadrados
    bucle_compr_nueva_pos: ;compara la cabeza con las partes de la otra serpiente
    CMP DI, BP
    JG fin_comprobaciones_bucle_1
    MOV AX,0
    MOV BX, 0
    MOV CX, 0
    ;compruebas por partes por tema de numeros negativos
    MOV AL, CoordenadasR[0] ;comprueba su cabeza con todas las pos azul
    MOV BL, CoordenadasA[SI]
    CMP BX, AX ;comprobación para tener valor absoluto de diferencias
    JLE comp_p1
    JMP comp_p11
    comp_p1:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 ojo cuidao
    JG bucle_compr_nueva_pos_1 ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp1
    comp_p11:
    SUB BX, AX
    CMP BX, 10
    JG bucle_compr_nueva_pos_1
    INC CX

    fin_comp1:
    MOV AX,0
    MOV BX, 0
    ;compruebas por partes por tema de numeros negativos
    MOV AL, CoordenadasR[0 + 1] ;comprueba su cabeza con todas las pos azul
    MOV BL, CoordenadasA[SI +1]
    CMP BX, AX
    JLE comp_p2
    JMP comp_p22
    
    comp_p2:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 ojo cuidao
    JG bucle_compr_nueva_pos_1 ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp_pos_1
    comp_p22:
    SUB BX, AX
    CMP BX, 10
    JG bucle_compr_nueva_pos_1
    INC CX
    fin_comp_pos_1:
    CMP CX, 2
    JNE bucle_compr_nueva_pos_1 ;hay un relative jump así que copio lo de pierde rojo
    cmp punto, 1
    JNE p_1 ;si no tengo que hacer el pop del punto
    POP CX ;quitas el punto
    p_1:
    POP DI
    POP SI
    POP BP
    POP DX
    POP CX
    POP BX ;en bx recibo la última dirección (en bL la del azul y en bH la del rojo)
    POP AX ;guardo ax
    MOV CX, 1 ;pongo que ha perdido el rojo
    iret
    bucle_compr_nueva_pos_1:
    ADD SI, 2
    INC DI
    JMP bucle_compr_nueva_pos

    fin_comprobaciones_bucle_1:


    MOV CX, 0
    MOV BP, cuadrados
    DEC BP
    MOV DI, 0
    MOV SI, 2
    ;2º Rojo con Rojo
    bucle_compr_nueva_pos_2: ;compara la cabeza con sus propias partes
    CMP DI, BP
    JG fin_comprobaciones_bucle_1_2
    MOV CX, 0
    MOV AX,0
    MOV BX, 0
    ;compruebas por partes por tema de numeros negativos
    MOV AL, CoordenadasR[0] ;comprueba su cabeza con todas las pos suyas
    MOV BL, CoordenadasR[SI]
    CMP BX, AX ;comprobación para tener valor absoluto de diferencias
    JLE comp_p1_2
    JMP comp_p11_2
    comp_p1_2:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 ojo cuidao
    JGE bucle_compr_nueva_pos_1_2 ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp1_2
    comp_p11_2:
    SUB BX, AX
    CMP BX, 10
    JGE bucle_compr_nueva_pos_1_2
    INC CX

    fin_comp1_2:
    MOV AX,0
    MOV BX, 0
    ;compruebas por partes por tema de numeros negativos
    MOV AL, CoordenadasR[0 + 1] ;comprueba su cabeza con todas las pos suyas
    MOV BL, CoordenadasR[SI +1]
    CMP BX, AX
    JLE comp_p2_2
    JMP comp_p22_2
    
    comp_p2_2:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 ojo cuidao
    JGE bucle_compr_nueva_pos_1_2 ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp_pos_1_2
    comp_p22_2:
    SUB BX, AX
    CMP BX, 10
    JGE bucle_compr_nueva_pos_1_2
    INC CX
    fin_comp_pos_1_2:
    CMP CX, 2
    JNE bucle_compr_nueva_pos_1_2 ;hay un relative jump así que copio lo de pierde rojo
    MOV BX, '0'
    CMP punto, 1
    JNE p_2
    POP CX ;quitas el punto
    p_2:
    POP DI
    POP SI
    POP BP
    POP DX
    POP CX
    POP BX ;en bx recibo la última dirección (en bL la del azul y en bH la del rojo)
    POP AX ;guardo ax
    MOV CX, 1 ;pongo que ha perdido el rojo
    iret
    bucle_compr_nueva_pos_1_2:
    ADD SI, 2
    INC DI
    JMP bucle_compr_nueva_pos_2

    fin_comprobaciones_bucle_1_2:


    ;comprobamos si hay que añadir
    CMP ticks_2, 0 ;Comprueba si han pasado todos los ticks
    JG continuar_2
    MOV AX, ticks_t2 ;los vuelvo a poner
    MOV ticks_2, AX ;restauras los ticks
    MOV BP, cuadrados 
    CMP BP, 47;si ya está el máximo alcanzado
    JGE continuar_2 ;si hay más cuadrados de los que puedo guardae
    ;Pones la nueva posición (la del último)
    ADD SI, 2
    MOV WORD PTR CoordenadasA[SI], DX ;le pones la del anterior
    MOV AX, DX
    int 57h ;imprimes ese último cuadrado azul
    CMP AX, -1
    JNE cont_aumento
    MOV BX, '0'
    CMP punto, 1
    JNE p_3
    POP CX ;quitas el punto
    p_3:
    POP DI
    POP SI
    POP BP
    POP DX
    POP CX
    POP BX ;en bx recibo la última dirección (en bL la del azul y en bH la del rojo)
    POP AX ;guardo ax
    MOV CX, 2 ;pongo queha perdido el azul
    iret
    cont_aumento:
    MOV BP, cuadrados
    INC BP
    MOV cuadrados, BP ;pones un cuadrado más en la variable de números de cuadrados
    continuar_2:
    ;comprobaciones azul
    
    ;1º Comprobacion de azul con rojo
    MOV CX, 0
    MOV BP, cuadrados
    MOV SI, 0
    MOV DI, 0
    bucle_compr_nueva_pos_azul: ;compara la cabeza con las partes de la otra serpiente
    CMP DI, BP
    JG fin_comprobaciones_bucle_1_azul
    MOV AX,0
    MOV BX, 0
    MOV CX, 0
    ;compruebas por partes por tema de numeros negativos
    MOV AL, CoordenadasA[0] ;comprueba su cabeza con todas las de rojo
    MOV BL, CoordenadasR[SI]
    CMP BX, AX ;comprobación para tener valor absoluto de diferencias
    JLE comp_p1_azul
    JMP comp_p1_azul1
    comp_p1_azul:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 ojo cuidao
    JG bucle_compr_nueva_pos_azul_1_azul ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp1_azul
    comp_p1_azul1:
    SUB BX, AX
    CMP BX, 10
    JG bucle_compr_nueva_pos_azul_1_azul
    INC CX

    fin_comp1_azul:
    MOV AX,0
    MOV BX, 0
    ;compruebas por partes por tema de numeros negativos
    MOV AL, CoordenadasA[0 + 1] ;comprueba su cabeza con todas las pos azul
    MOV BL, CoordenadasR[SI +1]
    CMP BX, AX
    JLE comp_p2_azul
    JMP comp_p2_azul2
    
    comp_p2_azul:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 ojo cuidao
    JG bucle_compr_nueva_pos_azul_1_azul ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp_pos_azul_1_azul
    comp_p2_azul2:
    SUB BX, AX
    CMP BX, 10
    JG bucle_compr_nueva_pos_azul_1_azul
    INC CX
    fin_comp_pos_azul_1_azul:
    CMP CX, 2
    JNE bucle_compr_nueva_pos_azul_1_azul ;hay un relative jump así que copio lo de pierde rojo
    MOV BX, '0'
    CMP punto, 1
    JNE p_4
    POP CX ;quitas el punto
    p_4:
    POP DI
    POP SI
    POP BP
    POP DX
    POP CX
    POP BX ;en bx recibo la última dirección (en bL la del azul y en bH la del rojo)
    POP AX ;guardo ax
    MOV CX, 2 ;pongo que ha perdido el azul
    iret
    bucle_compr_nueva_pos_azul_1_azul:
    ADD SI, 2
    INC DI
    JMP bucle_compr_nueva_pos_azul

    fin_comprobaciones_bucle_1_azul:


    MOV CX, 0
    MOV BP, cuadrados
    DEC BP
    MOV DI, 0
    MOV SI, 2

    ;2º Azul con Azul
    bucle_compr_nueva_pos_azul_2: ;compara la cabeza con sus propias partes
    CMP DI, BP
    JG fin_comprobaciones_bucle_1_azul_2
    MOV CX, 0
    MOV AX,0
    MOV BX, 0
    ;compruebas por partes por tema de numeros negativos
    MOV AL, CoordenadasA[0] ;comprueba su cabeza con todas las pos suyas
    MOV BL, CoordenadasA[SI]
    CMP BX, AX ;comprobación para tener valor absoluto de diferencias
    JLE comp_p1_azul_2
    JMP comp_p1_azul1_2
    comp_p1_azul_2:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 ojo cuidao
    JGE bucle_compr_nueva_pos_azul_1_azul_2 ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp1_azul_2
    comp_p1_azul1_2:
    SUB BX, AX
    CMP BX, 10
    JGE bucle_compr_nueva_pos_azul_1_azul_2
    INC CX

    fin_comp1_azul_2:
    MOV AX,0
    MOV BX, 0
    ;compruebas por partes por tema de numeros negativos
    MOV AL, CoordenadasA[0 + 1] ;comprueba su cabeza con todas las pos suyas
    MOV BL, CoordenadasA[SI +1]
    CMP BX, AX
    JLE comp_p2_azul_2
    JMP comp_p2_azul2_2
    
    comp_p2_azul_2:
    SUB AX, BX
    CMP AX, 10 ;si la diferencia es menor que 10 ojo cuidao
    JGE bucle_compr_nueva_pos_azul_1_azul_2 ;si hay mas de 10 de distancia no pueden estarse tocando
    INC CX
    JMP fin_comp_pos_azul_1_azul_2
    comp_p2_azul2_2:
    SUB BX, AX
    CMP BX, 10
    JGE bucle_compr_nueva_pos_azul_1_azul_2
    INC CX
    fin_comp_pos_azul_1_azul_2:
    CMP CX, 2
    JNE bucle_compr_nueva_pos_azul_1_azul_2 ;hay un relative jump así que copio lo de pierde rojo
    MOV BX, '0'
    CMP punto, 1
    JNE p_5
    POP CX ;quitas el punto
    p_5:
    POP DI
    POP SI
    POP BP
    POP DX
    POP CX
    POP BX ;en bx recibo la última dirección (en bL la del azul y en bH la del rojo)
    POP AX ;guardo ax
    MOV CX, 2 ;pongo que ha perdido el azul
    iret
    bucle_compr_nueva_pos_azul_1_azul_2:
    ADD SI, 2
    INC DI
    JMP bucle_compr_nueva_pos_azul_2

    fin_comprobaciones_bucle_1_azul_2:




    ;final_comprobaciones azul
    CMP punto, 1
    JE iretornar_valor ;si tengo que retornar el punto
    POP DI
    POP SI
    POP BP
    POP DX
    POP CX
    POP BX ;en bx recibo la última dirección (en bL la del azul y en bH la del rojo)
    POP AX ;guardo ax
    iret
    iretornar_valor:
    POP CX
    POP DI
    MOV DI, 0
    MOV DI, CX
    POP SI
    POP BP
    POP DX
    POP CX
    MOV CX, DI
    POP BX ;en bx recibo la última dirección (en bL la del azul y en bH la del rojo)
    POP AX ;guardo ax
    iret
    rsi3 ENDP



    fin: ;termina con el mensaje de error
        MOV AH,9
        MOV DX, offset textoError
        INT 21H
        MOV AX, 4C00H
        INT 21H

    instalador PROC
    ;compruebo parámetros
    XOR AX, AX ;inicializo ax a 0
    MOV AL, ds:[80h] ;cargo el número de parámetros
    CMP AL, 0
    JLE sin_parametros_jump
    JMP com_p1
    sin_parametros_jump:
        call sin_parametros
    ;el 81 es el espacio
    com_p1:
    MOV AL, ds:[82h] ;debería recibir /
    CMP AL, "/"
    JNE fin ;si no recibe el / ninguno es valido
    MOV AL, ds:[83h] ;recibe el siguiente valor
    CMP AL, "I"
    JE seguir
    CMP AL, "D" ;si recibe una D
    JE Desinstalar_aux
    JMP fin
    desinstalar_aux:
        call desinstalar
    seguir:
    call comprobar
    CMP AX, 1
    JE fin ;si ya estaba instalado
    ;si no estaba instalado las instala

    ;primero la int 1Ch
    mov ax, 0
    mov es, ax ;pones 0 en es porq las interrupciones empiezan por la posición 0
    mov ax, OFFSET rsi3 ;guardas el offset en ax
    mov bx, cs ;guardas el segmento en bx
    cli
    mov es:[ 4*1Ch+2 ], bx ;guardas el segmento
    mov es:[ 4*1Ch ], ax ;guardas el offset
    mov ds, es:[ 4*1Ch+2 ] ; Lee segmento de la rutina de servicio
    ;firma digital
    mov bx, ds:[2Ch]  ;Lee segmento de entorno del PSP de RSI
    mov es, bx
    mov es:[0], "In" ;Instalado
    sti
    
    ;ahora la int 55h
    mov ax, 0
    mov es, ax ;pones 0 en es porq las interrupciones empiezan por la posición 0
    mov ax, OFFSET rsi1 ;guardas el offset en ax
    mov bx, cs ;guardas el segmento en bx
    cli
    mov es:[ 4*55h+2 ], bx ;guardas el segmento
    mov es:[ 4*55h ], ax ;guardas el offset
    mov ds, es:[ 4*55h+2 ] ; Lee segmento de la rutina de servicio
    ;firma digital
    mov bx, ds:[2Ch]  ;Lee segmento de entorno del PSP de RSI
    mov es, bx
    mov es:[0], "In" ;Instalado
    sti
    ;ahora la int 57h
    mov ax, 0
    mov es, ax ;pones 0 en es porq las interrupciones empiezan por la posición 0
    mov ax, OFFSET rsi2 ;guardas el offset en ax
    mov bx, cs ;guardas el segmento en bx
    cli
    mov es:[ 4*57h+2 ], bx ;guardas el segmento
    mov es:[ 4*57h ], ax ;guardas el offset
    mov ds, es:[ 4*57h+2 ] ; Lee segmento de la rutina de servicio
    ;firma digital
    mov bx, ds:[2Ch]  ;Lee segmento de entorno del PSP de RSI
    mov es, bx
    mov es:[0], "In" ;Instalado
    sti
    ;imprime que lo instalo
    MOV AH,9
    MOV DX, offset textoinstalar
    INT 21H
    mov dx, OFFSET fin ;offset de la posición siguiente a la ultima que se quiere dejar residente
    int 27h ; Acaba y deja residente
    instalador ENDP ;termina el instalador
    ;si se ejcuta sin parámetros
    sin_parametros PROC
    call comprobar ;comprueba si está instalado
    CMP AX, 1
    JE imp_instalado ;imprime en función de si estaba instalado
    JMP imp_no
    RET
    imp_instalado:
        MOV AH,9
        MOV DX, offset textoinstalado
        INT 21H
        MOV AX, 4C00H
        INT 21H
    imp_no:
        MOV AH,9
        MOV DX, offset textodesinstalar
        INT 21H
        MOV AX, 4C00H
        INT 21H
    sin_parametros ENDP

    Desinstalar PROC
        call comprobar ;comprueba que este instalado
        CMP AX, 0
        JE no_desins
        PUSH DS
        PUSH ES
        ;si se puede desintalar (es decir está instalada)
        xor cx, cx
        mov ds, cx ; Segmento de vectores interrupción (0)
        mov es, ds:[ 55h*4+2 ] ; Lee segmento de RSI
        mov bx, es:[ 2Ch ] ; Lee segmento de entorno del PSP de RSI
        mov ah, 49h
        int 21h ; Libera segmento de RSI (es)
        mov es, bx
        int 21h ; Libera segmento de variables de entorno de RSI
        cli
        mov ds:[ 55h*4 ], cx ; cx = 0
        mov ds:[ 55h*4+2 ], cx
        sti

        xor cx, cx
        mov ds, cx ; Segmento de vectores interrupción (0)
        mov es, ds:[ 57h*4+2 ] ; Lee segmento de RSI
        mov bx, es:[ 2Ch ] ; Lee segmento de entorno del PSP de RSI
        mov ah, 49h
        int 21h ; Libera segmento de RSI (es)
        mov es, bx
        int 21h ; Libera segmento de variables de entorno de RSI
        cli
        mov ds:[ 57h*4 ], cx ; cx = 0
        mov ds:[ 57h*4+2 ], cx
        sti
        ;se cuelga con este no sé pq
        ;xor cx, cx
        ;mov ds, cx ; Segmento de vectores interrupción (0)
        ;mov es, ds:[ 1Ch*4+2 ] ; Lee segmento de RSI
        ;mov bx, es:[ 2Ch ] ; Lee segmento de entorno del PSP de RSI
        ;mov ah, 49h
        ;int 21h ; Libera segmento de RSI (es)
        ;mov es, bx
        ;int 21h ; Libera segmento de variables de entorno de RSI
        ;cli
        ;mov ds:[ 1Ch*4 ], cx ; cx = 0
        ;mov ds:[ 1Ch*4+2 ], cx
        ;sti

        ;imprime que la desinstalo
        pop ES
        pop DS
        MOV AH,9
        MOV DX, offset textodesinstalar
        INT 21H
        MOV AX, 4C00H
        INT 21H
        RET
        no_desins:
        MOV AH,9
        MOV DX, offset textoError
        INT 21H
        MOV AX, 4C00H
        INT 21H
    Desinstalar ENDP

    ;retorna 1 en AX si está instalado, 0 en caso contrario
    comprobar PROC ;deben estar ambas, si una falla no está instalado correctamente
    PUSH AX
    PUSH ES
    PUSH DS
    PUSH BX
    mov ax, 0
    mov es, ax ;pones 0 en es porq las interrupciones empiezan por la posición 0
    mov ds, es:[4*55h+2] ;lees el segmento de la rutina
    mov bx, ds:[2Ch] ;lee segmento de entorno del PSP de RSI
    mov es, bx
    mov bx, es:[0] ;lee el primer byte
    CMP bx, "In" ;Comprueba si esta la firmilla
    JNE nope
    mov ax, 0
    mov es, ax ;pones 0 en es porq las interrupciones empiezan por la posición 0
    mov ds, es:[4*57h+2] ;lees el segmento de la rutina
    mov bx, ds:[2Ch] ;lee segmento de entorno del PSP de RSI
    mov es, bx
    mov bx, es:[0] ;lee el primer byte
    CMP bx, "In" ;Comprueba si esta la firmilla
    JNE nope
    mov ax, 0
    mov es, ax ;pones 0 en es porq las interrupciones empiezan por la posición 0
    mov ds, es:[4*1Ch+2] ;lees el segmento de la rutina
    mov bx, ds:[2Ch] ;lee segmento de entorno del PSP de RSI
    mov es, bx
    mov bx, es:[0] ;lee el primer byte
    CMP bx, "In" ;Comprueba si esta la firmilla
    JNE nope
    JE sipi
    RET
    fin_comprobar:
    RET
    sipi:
        Pop BX
        pop DS
        pop ES
        pop AX
        mov ax, 1
        JMP fin_comprobar
    nope:
        pop BX
        pop DS
        pop ES
        pop AX
        mov ax, 0
        JMP fin_comprobar
    comprobar ENDP

codigo ENDS
END inicio