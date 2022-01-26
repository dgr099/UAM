;escribir_subseccion_data
segment .data
	msg_error_indice_vector db "Indice de vector fuera de rango", 0
	msg_error_division db "Error division por 0", 0
;escribir_cabecera_bss
segment .bss
	__esp resd 1
;D:	main
;D:	{
;D:	boolean
;R11:	<tipo> ::= boolean
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	resultado
;declarar_variable
	_resultado resd 1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	array
;D:	boolean
;R11:	<tipo> ::= boolean
;D:	[
;D:	3
;D:	]
;R15:	<clase_vector> ::= array <tipo> [ <constante_entera> ]
;R7:	<clase> ::= <clase_vector>
;D:	vector
;declarar_variable
	_vector resd 3
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	function
;R2:	<declaraciones> ::= <declaracion>
;R3:	<declaraciones> ::= <declaracion> <declaraciones>
;escribir_segmento_codigo
segment .text
	global main
	extern malloc, free
	extern scan_int, print_int, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
;D:	boolean
;R11:	<tipo> ::= boolean
;D:	or
;D:	(
;D:	boolean
;R11:	<tipo> ::= boolean
;D:	b1
;R27:	<parametro_funcion> ::= <tipo> <identificador>
;D:	;
;D:	boolean
;R11:	<tipo> ::= boolean
;D:	b2
;R27:	<parametro_funcion> ::= <tipo> <identificador>
;D:	;
;D:	boolean
;R11:	<tipo> ::= boolean
;D:	b3
;R27:	<parametro_funcion> ::= <tipo> <identificador>
;D:	)
;R26:	<resto_parametros_funcion> ::=
;R25:	<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>
;R25:	<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>
;R23:	<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>
;D:	{
;D:	boolean
;R11:	<tipo> ::= boolean
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	a
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	a
;R2:	<declaraciones> ::= <declaracion>
;R28:	<declaraciones_funcion> ::= <declaraciones>
; declararFuncion: f() { var1, ... varnum_var_loc...
_or:
	push ebp
	mov ebp, esp
	sub esp, 4
;D:	=
;D:	b1
;D:	||
; escribirParametro: 0 (origen 0)
	lea eax, [ebp + 16]; direccion parametro 0
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	b2
;D:	||
; escribirParametro: 1 (origen 0)
	lea eax, [ebp + 12]; direccion parametro 1
	push dword eax
;R80:	<exp> ::= <identificador>
;o
	pop dword ebx
	mov dword ebx, [ebx]
	pop dword eax
	mov dword eax, [eax]
	or eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
;R78:	<exp> ::= <exp> || <exp>
;D:	b3
;D:	;
; escribirParametro: 2 (origen 0)
	lea eax, [ebp + 8]; direccion parametro 2
	push dword eax
;R80:	<exp> ::= <identificador>
;o
	pop dword ebx
	mov dword ebx, [ebx]
	pop dword eax
	or eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
;R78:	<exp> ::= <exp> || <exp>
; escribirVariableLocal: 1 (origen 1)
	lea eax, [ebp - 4]
	push dword eax
; asignarDestinoEnPila:
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	return
;D:	a
;D:	;
; escribirVariableLocal: 1 (origen 1)
	lea eax, [ebp - 4]
	push dword eax
;R80:	<exp> ::= <identificador>
; retornarFuncion : return <cima_pila>
	pop eax
	mov dword eax, [eax]
	mov esp, ebp
	pop ebp
	ret
;R61:	<retorno_funcion> ::= return <exp>
;R38:	<sentencia_simple> ::= <retorno_funcion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R22:	<funcion> ::=function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }
;D:	vector
;R21:	<funciones> ::=
;R20:	<funciones> ::= <funcion> <funciones>
;escribir_inicio_main
; -----------------------
; PROCEDIMIENTO PRINCIPAL
main:
	mov dword [__esp], esp
;D:	[
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	]
; escribir_elemento_vector vector
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;D:	=
;D:	false
;R103:	<constante_logica> ::= false
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	;
;escribir_operando
	push dword 0
; escribir_elemento_vector vector
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
; asignarDestinoEnPila:
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;R44:	<asignacion> ::= <elemento_vector> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	vector
;D:	[
;D:	1
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	]
; escribir_elemento_vector vector
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;D:	=
;D:	true
;R102:	<constante_logica> ::= true
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	;
;escribir_operando
	push dword 1
; escribir_elemento_vector vector
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
; asignarDestinoEnPila:
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;R44:	<asignacion> ::= <elemento_vector> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	vector
;D:	[
;D:	2
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 2
;R81:	<exp> ::= <constante>
;D:	]
; escribir_elemento_vector vector
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;D:	=
;D:	false
;R103:	<constante_logica> ::= false
;R100:	<constante> ::= <constante_entera>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	;
;escribir_operando
	push dword 2
; escribir_elemento_vector vector
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
; asignarDestinoEnPila:
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;R44:	<asignacion> ::= <elemento_vector> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	resultado
;D:	=
;D:	or
;D:	(
;D:	vector
;D:	[
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	]
; escribir_elemento_vector vector
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;R85:	<exp> ::= <elemento_vector>
;D:	,
;operandoEnPilaAArgumento
	pop eax
	mov eax, [eax]
	push eax
;D:	vector
;D:	[
;D:	1
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	]
; escribir_elemento_vector vector
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;R85:	<exp> ::= <elemento_vector>
;D:	,
;operandoEnPilaAArgumento
	pop eax
	mov eax, [eax]
	push eax
;D:	vector
;D:	[
;D:	2
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 2
;R81:	<exp> ::= <constante>
;D:	]
; escribir_elemento_vector vector
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;R85:	<exp> ::= <elemento_vector>
;D:	)
;operandoEnPilaAArgumento
	pop eax
	mov eax, [eax]
	push eax
;R92:	<resto_lista_expresiones> ::=
;R91:	<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>
;R91:	<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>
;R89:	<lista_expresiones> ::= <exp> <resto_lista_expresiones>
; llamarFuncion: or 3
	call _or
; limpiarPila: 3
	add esp, 12
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
	call print_boolean
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
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
