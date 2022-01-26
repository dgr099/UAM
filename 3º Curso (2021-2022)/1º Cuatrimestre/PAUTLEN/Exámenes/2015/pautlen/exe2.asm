;-------------------------------
; tests/prueba.alfa
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
_v resd 4
; escribir_segmento_codigo
segment .text
global main
extern print_int, print_boolean, print_string, print_blank
extern print_endofline, scan_int, scan_boolean
; escribir_inicio_main
main:
mov dword [__esp], esp
; escribir_operando
mov eax, 0
push eax
; comprobar_indice_vector
pop dword eax
cmp eax, 0
jl fin_indice_fuera_rango
cmp eax, 4
jge fin_indice_fuera_rango
lea eax, [4*eax + _v]
push dword eax
; escribir_operando
mov eax, 10
push eax
; escribir_elemento_vector
pop dword eax
pop dword ebx
mov dword [ebx], eax
; escribir_operando
mov eax, 1
push eax
; comprobar_indice_vector
pop dword eax
cmp eax, 0
jl fin_indice_fuera_rango
cmp eax, 4
jge fin_indice_fuera_rango
lea eax, [4*eax + _v]
push dword eax
; escribir_operando
mov eax, 20
push eax
; escribir_elemento_vector
pop dword eax
pop dword ebx
mov dword [ebx], eax
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
