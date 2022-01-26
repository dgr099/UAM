;escribir_subseccion_data
segment .data
	msg_error_indice_vector db "Indice de vector fuera de rango", 0
	msg_error_division db "Error division por 0", 0
;escribir_cabecera_bss
segment .bss
	__esp resd 1
;D:	main
;D:	{
;D:	int
;R10:	<tipo> ::= int
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	x
;declarar_variable
	_x resd 1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	,
;D:	resultado
;declarar_variable
	_resultado resd 1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R19:	<identificadores> ::= <identificador> , <identificadores>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	function
;R2:	<declaraciones> ::= <declaracion>
;escribir_segmento_codigo
segment .text
	global main
	extern malloc, free
	extern scan_int, print_int, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
;D:	int
;R10:	<tipo> ::= int
;D:	fibonacci
;D:	(
;D:	int
;R10:	<tipo> ::= int
;D:	num1
;R27:	<parametro_funcion> ::= <tipo> <identificador>
;D:	)
;R26:	<resto_parametros_funcion> ::=
;R23:	<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>
;D:	{
;D:	int
;R10:	<tipo> ::= int
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	res1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	,
;D:	res2
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R19:	<identificadores> ::= <identificador> , <identificadores>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	if
;R2:	<declaraciones> ::= <declaracion>
;R28:	<declaraciones_funcion> ::= <declaraciones>
; declararFuncion: f() { var1, ... varnum_var_loc...
_fibonacci:
	push ebp
	mov ebp, esp
	sub esp, 8
;D:	(
;D:	(
;D:	num1
;D:	==
; escribirParametro: 0 (origen 0)
	lea eax, [ebp + 8]; direccion parametro 0
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	)
;igual
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	je near igual0
	push dword 0
	jmp near fin_igual0
igual0:
	push dword 1
fin_igual0:
;R93:	<comparacion> ::= <exp> == <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;D:	)
;D:	{
; ifthen_inicio 0
	pop eax
	cmp eax, 0
	je near fin_then0
;D:	return
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	;
; retornarFuncion : return <cima_pila>
	pop eax
	mov esp, ebp
	pop ebp
	ret
;R61:	<retorno_funcion> ::= return <exp>
;R38:	<sentencia_simple> ::= <retorno_funcion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelese_fin_then 0
	jmp near fin_ifelse0
fin_then0:
;D:	if
; ifthenelse_fin 0
fin_ifelse0:
;R50:	<condicional> ::= if ( <exp> ) { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	(
;D:	(
;D:	num1
;D:	==
; escribirParametro: 0 (origen 0)
	lea eax, [ebp + 8]; direccion parametro 0
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	1
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	)
;igual
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	je near igual1
	push dword 0
	jmp near fin_igual1
igual1:
	push dword 1
fin_igual1:
;R93:	<comparacion> ::= <exp> == <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;D:	)
;D:	{
; ifthen_inicio 1
	pop eax
	cmp eax, 0
	je near fin_then1
;D:	return
;D:	1
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	;
; retornarFuncion : return <cima_pila>
	pop eax
	mov esp, ebp
	pop ebp
	ret
;R61:	<retorno_funcion> ::= return <exp>
;R38:	<sentencia_simple> ::= <retorno_funcion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelese_fin_then 1
	jmp near fin_ifelse1
fin_then1:
;D:	res1
; ifthenelse_fin 1
fin_ifelse1:
;R50:	<condicional> ::= if ( <exp> ) { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	=
;D:	fibonacci
;D:	(
;D:	num1
;D:	-
; escribirParametro: 0 (origen 0)
	lea eax, [ebp + 8]; direccion parametro 0
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	1
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	)
;restar
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	sub eax, ebx
	push dword eax
;R73:	<exp> ::= <exp> - <exp>
;operandoEnPilaAArgumento
;R92:	<resto_lista_expresiones> ::=
;R89:	<lista_expresiones> ::= <exp> <resto_lista_expresiones>
; llamarFuncion: fibonacci 1
	call _fibonacci
; limpiarPila: 1
	add esp, 4
	push dword eax
;R88:	<exp> ::= <identificador> ( <lista_expresiones> )
;D:	;
; escribirVariableLocal: 1 (origen 1)
	lea eax, [ebp - 4]
	push dword eax
; asignarDestinoEnPila:
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	res2
;D:	=
;D:	fibonacci
;D:	(
;D:	num1
;D:	-
; escribirParametro: 0 (origen 0)
	lea eax, [ebp + 8]; direccion parametro 0
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	2
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 2
;R81:	<exp> ::= <constante>
;D:	)
;restar
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	sub eax, ebx
	push dword eax
;R73:	<exp> ::= <exp> - <exp>
;operandoEnPilaAArgumento
;R92:	<resto_lista_expresiones> ::=
;R89:	<lista_expresiones> ::= <exp> <resto_lista_expresiones>
; llamarFuncion: fibonacci 1
	call _fibonacci
; limpiarPila: 1
	add esp, 4
	push dword eax
;R88:	<exp> ::= <identificador> ( <lista_expresiones> )
;D:	;
; escribirVariableLocal: 2 (origen 1)
	lea eax, [ebp - 8]
	push dword eax
; asignarDestinoEnPila:
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	return
;D:	res1
;D:	+
; escribirVariableLocal: 1 (origen 1)
	lea eax, [ebp - 4]
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	res2
;D:	;
; escribirVariableLocal: 2 (origen 1)
	lea eax, [ebp - 8]
	push dword eax
;R80:	<exp> ::= <identificador>
;sumar
	pop dword ebx
	mov dword ebx, [ebx]
	pop dword eax
	mov dword eax, [eax]
	add eax, ebx
	push dword eax
;R72:	<exp> ::= <exp> + <exp>
; retornarFuncion : return <cima_pila>
	pop eax
	mov esp, ebp
	pop ebp
	ret
;R61:	<retorno_funcion> ::= return <exp>
;R38:	<sentencia_simple> ::= <retorno_funcion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R22:	<funcion> ::=function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }
;D:	scanf
;R21:	<funciones> ::=
;R20:	<funciones> ::= <funcion> <funciones>
;escribir_inicio_main
; -----------------------
; PROCEDIMIENTO PRINCIPAL
main:
	mov dword [__esp], esp
;D:	x
;leer
	push dword _x
	call scan_int
	add esp, 4
;R54:	<lectura> ::= scanf <identificador>
;R35:	<sentencia_simple> ::= <lectura>
;D:	;
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	resultado
;D:	=
;D:	fibonacci
;D:	(
;D:	x
;D:	)
;escribir_operando
	push dword _x
;R80:	<exp> ::= <identificador>
;operandoEnPilaAArgumento
	pop eax
	mov eax, [eax]
	push eax
;R92:	<resto_lista_expresiones> ::=
;R89:	<lista_expresiones> ::= <exp> <resto_lista_expresiones>
; llamarFuncion: fibonacci 1
	call _fibonacci
; limpiarPila: 1
	add esp, 4
	push dword eax
;R88:	<exp> ::= <identificador> ( <lista_expresiones> )
;D:	;
;asignar
	pop dword eax
	mov dword [_resultado], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	resultado
;D:	;
;escribir_operando
	push dword _resultado
;R80:	<exp> ::= <identificador>
;escribir
	pop eax
	mov eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R1:	<programa> ::= main { <declaraciones> <funciones> <sentencias> }
;escribir_fin

	jmp near fin
fin_error_division: 
	push dword msg_error_division
	call print_string
	add esp, 4
	call print_endofline
	jmp near fin
fin_indice_fuera_rango: 
	push dword msg_error_indice_vector
	call print_string
	add esp, 4
	call print_endofline
	jmp near fin
fin: 
	mov esp, [__esp]
	ret
