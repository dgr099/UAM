;-------------------------------
; tests/test_examen.alfa
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
_a resd 1
; declarar_variable
_b resd 1
; declarar_variable
_c resd 1
; escribir_segmento_codigo
segment .text
global main
extern print_int, print_boolean, print_string, print_blank
extern print_endofline, scan_int, scan_boolean
; escribir_inicio_main
main:
mov dword [__esp], esp
; leer (scan)
push dword _a
call scan_int
add esp, 4
; leer (scan)
push dword _b
call scan_int
add esp, 4
; leer (scan)
push dword _c
call scan_int
add esp, 4
; escribir_operando
mov eax, [_a]
push eax
; escribir_operando
mov eax, [_b]
push eax
; restar
pop dword eax
pop dword ebx
sub ebx, eax
push dword ebx
; compare inicio
pop eax
cmp eax, 0
je near equal1
jg near greater1
; escribir_operando
mov eax, [_a]
push eax
; escribir_operando
mov eax, [_b]
push eax
; restar
pop dword eax
pop dword ebx
sub ebx, eax
push dword ebx
; escribir (print)
call print_int
call print_endofline
add esp, 4
; escribir_operando
mov eax, 1
push eax
; cambiar signo
pop dword eax
neg eax
push dword eax
; escribir (print)
call print_int
call print_endofline
add esp, 4
; escribir_operando
mov eax, [_a]
push eax
; escribir_operando
mov eax, [_b]
push eax
; sumar
pop dword eax
pop dword ebx
add ebx, eax
push dword ebx
; escribir_operando
mov eax, [_c]
push eax
; restar
pop dword eax
pop dword ebx
sub ebx, eax
push dword ebx
; compare inicio
pop eax
cmp eax, 0
je near equal2
jg near greater2
; escribir_operando
mov eax, 1000
push eax
; cambiar signo
pop dword eax
neg eax
push dword eax
; escribir (print)
call print_int
call print_endofline
add esp, 4
; equal_inicio
jmp near fin_compare2
equal2:
; escribir_operando
mov eax, 0
push eax
; escribir (print)
call print_int
call print_endofline
add esp, 4
; greater_inicio
jmp near fin_compare2
greater2:
; escribir_operando
mov eax, 1000
push eax
; escribir (print)
call print_int
call print_endofline
add esp, 4
; compare_fin
fin_compare2:
; equal_inicio
jmp near fin_compare1
equal1:
; escribir_operando
mov eax, [_a]
push eax
; escribir_operando
mov eax, [_b]
push eax
; restar
pop dword eax
pop dword ebx
sub ebx, eax
push dword ebx
; escribir (print)
call print_int
call print_endofline
add esp, 4
; escribir_operando
mov eax, 0
push eax
; escribir (print)
call print_int
call print_endofline
add esp, 4
; greater_inicio
jmp near fin_compare1
greater1:
; escribir_operando
mov eax, [_a]
push eax
; escribir_operando
mov eax, [_b]
push eax
; restar
pop dword eax
pop dword ebx
sub ebx, eax
push dword ebx
; escribir (print)
call print_int
call print_endofline
add esp, 4
; escribir_operando
mov eax, 1
push eax
; escribir (print)
call print_int
call print_endofline
add esp, 4
; compare_fin
fin_compare1:
; escribir_fin
jmp near fin ; termina sin errores
fin_error_division: ; división por cero
push dword msg_error_division
call print_string
call print_endofline
add esp, 4
jmp near fin ; salta al final
fin_indice_fuera_rango: ; error de índice fuera de rango
push dword msg_error_indice_vector
call print_string
call print_endofline
add esp, 4
jmp near fin ; salta al final
fin:
mov dword esp, [__esp] ; recupera el puntero de pila
ret
