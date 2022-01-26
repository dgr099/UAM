;-------------------------------
; tests/test_vector.alfa
;   Autor: Carlos Anivarro
;   Autor: Daniel Barahona
;   Autor: David Garitagoitia
;-------------------------------
segment .data
msg_error_division db "**** Division por 0 no permitida", 0
msg_error_indice_vector db "**** Indice fuera de rango", 0
segment .bss
__esp resd 1
; declarar_variable
_vector resd 3
; declarar_variable
_a resd 1
; escribir_segmento_codigo
segment .text
global main
extern print_int, print_boolean, print_string, print_blank
extern print_endofline, scan_int, scan_boolean
; escribir_inicio_main
main:
mov dword [__esp], esp
; escribir_operando
mov eax, 1
push eax
; asignar
pop dword eax
mov dword [_a], eax
