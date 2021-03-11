;author: David Teófilo Garitagoitia Romero
;_______________________________________________________________
; DEFINICION DEL SEGMENTO DE DATOS
DATOS SEGMENT
	CLR_PANT 	DB 	1BH,"[2","J$"
	CUR_MICRO	DB 	1BH,"[4;27fTECNOLOGIA DE COMPUTADORES$"
	PREG_NOM 	DB 	1BH,"[15;1fESCRIBE TU NOMBRE ? $"
	PREG_AP1 	DB 	1BH,"[16;1fESCRIBE TU APELLIDO 1 ? $"
	PREG_AP2 	DB 	1BH,"[17;1fESCRIBE TU APELLIDO 2 ? $"
	NOMBRE		DB 	80 DUP (0)
	APELLIDO1	DB 	80 DUP (0) ;Para guardar el apellido 1
	APELLIDO2	DB 	80 DUP (0) ;Para guardar el apellido 2
	TEXTO 		DB 	1BH,"[22;1fDON ","$"
	TEXTO2 		DB 	" ES ALUMNO DE 2o CURSO DE "
			DB 	"INGENIERIA INFORMATICA",13,10,"$"
DATOS ENDS
;_______________________________________________________________
; DEFINICION DEL SEGMENTO DE PILA
PILA SEGMENT STACK "STACK"
	DB 40H DUP (0)
PILA ENDS
;_______________________________________________________________
; DEFINICION DEL SEGMENTO DE CODIGO
CODE SEGMENT
ASSUME CS:CODE,DS:DATOS,SS:PILA
; COMIENZO DEL PROCEDIMIENTO PRINCIPAL (START)
START PROC FAR
;INICIALIZACION DE LOS REGISTROS DE SEGMENTO
	MOV AX,DATOS
	MOV DS,AX
	;FIN DE LAS INICIALIZACIONES
	
	;BORRA LA PANTALLA
	MOV AH,9
	MOV DX, OFFSET CLR_PANT
	INT 21H ;LLAMADA AL SISTEMA OPERATIVO, QUE EJECUTA LA FUNCION QUE HAYA EN AH, el 9 corresponde a imprimir la cadena que apunta DX
	
	MOV DX,OFFSET CUR_MICRO		;ESCRIBE "CURSO ...
	INT 21H

	MOV DX,OFFSET PREG_NOM		;MUESTRA "ESCRIBE ...
	INT 21H

	MOV AH,0AH			;ALMACENA EL NOMBRE TECLEADO
	MOV DX,OFFSET NOMBRE ;Se carga en DX la direccion del segmento de memoria donde guardar la linea
	MOV NOMBRE[0],60		;MAXIMO NUMERO DE CARACTERES, en el primer byte se indica el numero maximo de caracteres, no puede superar 255
	INT 21H ;LLamada al SO

	MOV AH,9 ;Se carga en AH el 9 para volver a imprimir por pantalla
	MOV DX,OFFSET PREG_AP1		;MUESTRA "ESCRIBE AP1...
	INT 21H

	MOV AH,0AH			;Cargamos la instrucción para guardar datos
	MOV DX,OFFSET APELLIDO1 ;Cargamos en DX la dirección de APELLIDO1 donde debe guardar la linea
	MOV APELLIDO1[0],60	;Ponemos el limite
	INT 21H ;LLamada al SO

	MOV AH, 9 ;Volvemos a cargar la instruccion de escritura por pantalla
	MOV DX,OFFSET PREG_AP2		;MUESTRA "ESCRIBE AP2...
	INT 21H

	MOV AH,0AH			;Guaramos la instrucción para guardar datos
	MOV DX,OFFSET APELLIDO2 ;Cargamos en DX la dirección de APELLIDO2 donde debe guardar la linea
	MOV APELLIDO2[0],60	;Ponemos el limite
	INT 21H ;LLamada al SO
	

	MOV AH,9			;ESCRIBE "DON ...
	MOV DX, OFFSET TEXTO
	INT 21H

	MOV BX,0
	;Bucle para escribir el nombre
NAME:
	MOV DL,NOMBRE[BX+2]		;ESCRIBIR UN CARACTER DEL NOMBRE
	MOV AH,2
	INT 21H
	
	INC BX
	CMP BL, NOMBRE[1]		;COMPARA CON EL NUMERO DE CARACTERES
	JNE NAME


	CALL ESPACIO	;Funcion para escribir un espacio en blanco

	MOV BX, 0 ;Volvemos a colocar en BX un 0 para volver a realizar un bucle similar a name esta vez para apellido1

;Para imprimir el apellido 1
SURNAME1:
	MOV DL,APELLIDO1[BX+2]		;ESCRIBIR UN CARACTER DEL APELLIDO
	MOV AH,2
	INT 21H
	
	INC BX
	CMP BL, APELLIDO1[1]		;COMPARA CON EL NUMERO DE CARACTERES
	JNE SURNAME1

	CALL ESPACIO ;escribimos el espacio
	MOV BX, 0 ;Volvemos a colocar en BX un 0 para volver a realizar un bucle similar a name esta vez para apellido2
;Para imprimir el apellido 2
SURNAME2:
	MOV DL,APELLIDO2[BX+2]		;ESCRIBIR UN CARACTER DEL APELLIDO
	MOV AH,2
	INT 21H
	
	INC BX
	CMP BL, APELLIDO2[1]		;COMPARA CON EL NUMERO DE CARACTERES
	JNE SURNAME2


	MOV DX, OFFSET TEXTO2		; ESCRIBE "ES ALUMNO ...
	MOV AH,9
	INT 21H
	
	MOV AX,4C00H			; FIN DE PROGRAMA Y VUELTA AL DOS
	INT 21H

;Función para imprimir un espacio
ESPACIO PROC
	;Para imprimir un espacio
	MOV AH, 2 ;PARA IMPRIMIR SOLO UN CARACTER, de esta forma no es necesario crear una variable solo para el espacio
    MOV DX, ' ' ;Caracter de espacio
    INT 21h ;LLamada al SO
	RET
ESPACIO ENDP

START ENDP
;FIN DEL SEGMENTO DE CODIGO
CODE ENDS
;FIN DE PROGRAMA INDICANDO DONDE COMIENZA LA EJECUCION
END START

