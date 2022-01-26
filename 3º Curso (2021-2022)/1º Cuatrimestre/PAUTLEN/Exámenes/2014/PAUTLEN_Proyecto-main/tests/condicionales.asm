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
;D:	y
;declarar_variable
	_y resd 1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	,
;D:	z
;declarar_variable
	_z resd 1
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R19:	<identificadores> ::= <identificador> , <identificadores>
;R19:	<identificadores> ::= <identificador> , <identificadores>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	scanf
;R2:	<declaraciones> ::= <declaracion>
;escribir_segmento_codigo
segment .text
	global main
	extern malloc, free
	extern scan_int, print_int, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
;R21:	<funciones> ::=
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
;D:	scanf
;D:	y
;leer
	push dword _y
	call scan_int
	add esp, 4
;R54:	<lectura> ::= scanf <identificador>
;R35:	<sentencia_simple> ::= <lectura>
;D:	;
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	scanf
;D:	z
;leer
	push dword _z
	call scan_int
	add esp, 4
;R54:	<lectura> ::= scanf <identificador>
;R35:	<sentencia_simple> ::= <lectura>
;D:	;
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	if
;D:	(
;D:	(
;D:	x
;D:	==
;escribir_operando
	push dword _x
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
;D:	&&
;D:	(
;D:	y
;D:	==
;escribir_operando
	push dword _y
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
	je near igual1
	push dword 0
	jmp near fin_igual1
igual1:
	push dword 1
fin_igual1:
;R93:	<comparacion> ::= <exp> == <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;y
	pop dword ebx
	pop dword eax
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
;D:	&&
;D:	(
;D:	z
;D:	==
;escribir_operando
	push dword _z
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
	je near igual2
	push dword 0
	jmp near fin_igual2
igual2:
	push dword 1
fin_igual2:
;R93:	<comparacion> ::= <exp> == <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;y
	pop dword ebx
	pop dword eax
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
;D:	)
;D:	{
; ifthen_inicio 0
	pop eax
	cmp eax, 0
	je near fin_then0
;D:	printf
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	;
;escribir
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelese_fin_then 0
	jmp near fin_ifelse0
fin_then0:
;D:	else
;D:	{
;D:	if
;D:	(
;D:	(
;D:	x
;D:	>
;escribir_operando
	push dword _x
;R80:	<exp> ::= <identificador>
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	)
;mayor
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jg near si_mayor3
	push dword 0
	jmp near fin_mayor3
si_mayor3:
	push dword 1
fin_mayor3:
;R98:	<comparacion> ::= <exp> > <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;D:	&&
;D:	(
;D:	y
;D:	>
;escribir_operando
	push dword _y
;R80:	<exp> ::= <identificador>
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	)
;mayor
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jg near si_mayor4
	push dword 0
	jmp near fin_mayor4
si_mayor4:
	push dword 1
fin_mayor4:
;R98:	<comparacion> ::= <exp> > <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;y
	pop dword ebx
	pop dword eax
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
;D:	)
;D:	{
; ifthen_inicio 1
	pop eax
	cmp eax, 0
	je near fin_then1
;D:	if
;D:	(
;D:	(
;D:	z
;D:	>
;escribir_operando
	push dword _z
;R80:	<exp> ::= <identificador>
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	)
;mayor
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jg near si_mayor5
	push dword 0
	jmp near fin_mayor5
si_mayor5:
	push dword 1
fin_mayor5:
;R98:	<comparacion> ::= <exp> > <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;D:	)
;D:	{
; ifthen_inicio 2
	pop eax
	cmp eax, 0
	je near fin_then2
;D:	printf
;D:	1
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	;
;escribir
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelese_fin_then 2
	jmp near fin_ifelse2
fin_then2:
;D:	else
;D:	{
;D:	printf
;D:	5
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 5
;R81:	<exp> ::= <constante>
;D:	;
;escribir
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelse_fin 2
fin_ifelse2:
;R51:	<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelese_fin_then 1
	jmp near fin_ifelse1
fin_then1:
;D:	if
; ifthenelse_fin 1
fin_ifelse1:
;R50:	<condicional> ::= if ( <exp> ) { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	(
;D:	(
;D:	x
;D:	<
;escribir_operando
	push dword _x
;R80:	<exp> ::= <identificador>
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	)
;menor
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jl near si_menor6
	push dword 0
	jmp near fin_menor6
si_menor6:
	push dword 1
fin_menor6:
;R97:	<comparacion> ::= <exp> < <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;D:	&&
;D:	(
;D:	y
;D:	>
;escribir_operando
	push dword _y
;R80:	<exp> ::= <identificador>
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	)
;mayor
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jg near si_mayor7
	push dword 0
	jmp near fin_mayor7
si_mayor7:
	push dword 1
fin_mayor7:
;R98:	<comparacion> ::= <exp> > <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;y
	pop dword ebx
	pop dword eax
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
;D:	)
;D:	{
; ifthen_inicio 3
	pop eax
	cmp eax, 0
	je near fin_then3
;D:	if
;D:	(
;D:	(
;D:	z
;D:	>
;escribir_operando
	push dword _z
;R80:	<exp> ::= <identificador>
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	)
;mayor
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jg near si_mayor8
	push dword 0
	jmp near fin_mayor8
si_mayor8:
	push dword 1
fin_mayor8:
;R98:	<comparacion> ::= <exp> > <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;D:	)
;D:	{
; ifthen_inicio 4
	pop eax
	cmp eax, 0
	je near fin_then4
;D:	printf
;D:	2
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 2
;R81:	<exp> ::= <constante>
;D:	;
;escribir
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelese_fin_then 4
	jmp near fin_ifelse4
fin_then4:
;D:	else
;D:	{
;D:	printf
;D:	6
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 6
;R81:	<exp> ::= <constante>
;D:	;
;escribir
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelse_fin 4
fin_ifelse4:
;R51:	<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelese_fin_then 3
	jmp near fin_ifelse3
fin_then3:
;D:	if
; ifthenelse_fin 3
fin_ifelse3:
;R50:	<condicional> ::= if ( <exp> ) { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	(
;D:	(
;D:	x
;D:	<
;escribir_operando
	push dword _x
;R80:	<exp> ::= <identificador>
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	)
;menor
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jl near si_menor9
	push dword 0
	jmp near fin_menor9
si_menor9:
	push dword 1
fin_menor9:
;R97:	<comparacion> ::= <exp> < <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;D:	&&
;D:	(
;D:	y
;D:	<
;escribir_operando
	push dword _y
;R80:	<exp> ::= <identificador>
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	)
;menor
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jl near si_menor10
	push dword 0
	jmp near fin_menor10
si_menor10:
	push dword 1
fin_menor10:
;R97:	<comparacion> ::= <exp> < <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;y
	pop dword ebx
	pop dword eax
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
;D:	)
;D:	{
; ifthen_inicio 5
	pop eax
	cmp eax, 0
	je near fin_then5
;D:	if
;D:	(
;D:	(
;D:	z
;D:	>
;escribir_operando
	push dword _z
;R80:	<exp> ::= <identificador>
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	)
;mayor
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jg near si_mayor11
	push dword 0
	jmp near fin_mayor11
si_mayor11:
	push dword 1
fin_mayor11:
;R98:	<comparacion> ::= <exp> > <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;D:	)
;D:	{
; ifthen_inicio 6
	pop eax
	cmp eax, 0
	je near fin_then6
;D:	printf
;D:	3
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 3
;R81:	<exp> ::= <constante>
;D:	;
;escribir
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelese_fin_then 6
	jmp near fin_ifelse6
fin_then6:
;D:	else
;D:	{
;D:	printf
;D:	7
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 7
;R81:	<exp> ::= <constante>
;D:	;
;escribir
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelse_fin 6
fin_ifelse6:
;R51:	<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelese_fin_then 5
	jmp near fin_ifelse5
fin_then5:
;D:	if
; ifthenelse_fin 5
fin_ifelse5:
;R50:	<condicional> ::= if ( <exp> ) { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	(
;D:	(
;D:	x
;D:	>
;escribir_operando
	push dword _x
;R80:	<exp> ::= <identificador>
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	)
;mayor
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jg near si_mayor12
	push dword 0
	jmp near fin_mayor12
si_mayor12:
	push dword 1
fin_mayor12:
;R98:	<comparacion> ::= <exp> > <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;D:	&&
;D:	(
;D:	y
;D:	<
;escribir_operando
	push dword _y
;R80:	<exp> ::= <identificador>
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	)
;menor
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jl near si_menor13
	push dword 0
	jmp near fin_menor13
si_menor13:
	push dword 1
fin_menor13:
;R97:	<comparacion> ::= <exp> < <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;y
	pop dword ebx
	pop dword eax
	and eax, ebx
	push dword eax
;R77:	<exp> ::= <exp> && <exp>
;D:	)
;D:	{
; ifthen_inicio 7
	pop eax
	cmp eax, 0
	je near fin_then7
;D:	if
;D:	(
;D:	(
;D:	z
;D:	>
;escribir_operando
	push dword _z
;R80:	<exp> ::= <identificador>
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	)
;mayor
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, ebx
	jg near si_mayor14
	push dword 0
	jmp near fin_mayor14
si_mayor14:
	push dword 1
fin_mayor14:
;R98:	<comparacion> ::= <exp> > <exp>
;R82:	<exp> ::= ( <exp> )
;R83:	<exp> ::= ( <comparacion> )
;D:	)
;D:	{
; ifthen_inicio 8
	pop eax
	cmp eax, 0
	je near fin_then8
;D:	printf
;D:	4
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 4
;R81:	<exp> ::= <constante>
;D:	;
;escribir
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelese_fin_then 8
	jmp near fin_ifelse8
fin_then8:
;D:	else
;D:	{
;D:	printf
;D:	8
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 8
;R81:	<exp> ::= <constante>
;D:	;
;escribir
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelse_fin 8
fin_ifelse8:
;R51:	<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	}
;R30:	<sentencias> ::= <sentencia>
; ifthenelese_fin_then 7
	jmp near fin_ifelse7
fin_then7:
;D:	}
; ifthenelse_fin 7
fin_ifelse7:
;R50:	<condicional> ::= if ( <exp> ) { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
; ifthenelse_fin 0
fin_ifelse0:
;R51:	<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	}
;R30:	<sentencias> ::= <sentencia>
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
