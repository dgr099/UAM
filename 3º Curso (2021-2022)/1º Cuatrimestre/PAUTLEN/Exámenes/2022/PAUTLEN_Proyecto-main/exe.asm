;-------------------------------
; tests/pruebas_examen/test_examen_funciones.alfa
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
_x resd 1
; declarar_variable
_resultado resd 1
; escribir_segmento_codigo
segment .text
global main
extern print_int, print_boolean, print_string, print_blank
extern print_endofline, scan_int, scan_boolean
; declararFuncion
_pow:
push ebp
mov dword ebp, esp
sub esp, 4
; escribirParametro
mov eax, dword [ebp + 12]
push dword eax
; asignarVariableLocal
pop dword eax
lea ebx, [ebp - 4]
mov [ebx], eax
; do_while_inicio
inicio_do_while1:
; escribirVariableLocal
mov eax, dword [ebp - 4]
push dword eax
; escribirParametro
mov eax, dword [ebp + 12]
push dword eax
; multiplicar
pop dword eax
pop dword ebx
mov dword ecx, ebx
imul ecx
push dword eax
; asignarVariableLocal
pop dword eax
lea ebx, [ebp - 4]
mov [ebx], eax
; escribirParametro
mov eax, dword [ebp + 8]
push dword eax
; escribir_operando
mov eax, 1
push eax
; restar
pop dword eax
pop dword ebx
sub ebx, eax
push dword ebx
; asignarParametro
pop dword eax
lea ebx, [ebp + 8]
mov [ebx], eax
; escribirParametro
mov eax, dword [ebp + 8]
push dword eax
; escribir_operando
mov eax, 1
push eax
; comparación mayor
pop dword eax
pop dword ebx
cmp ebx, eax
jg my_es_my2
mov dword eax, 0
push dword eax
jmp my_fin2
my_es_my2:
mov dword eax, 1
push dword eax
my_fin2:
; while_exp_pila
pop eax
cmp eax, 0
jne near inicio_do_while1
; escribirVariableLocal
mov eax, dword [ebp - 4]
push dword eax
; retornarFuncion
pop dword eax
mov dword esp, ebp
pop dword ebp
ret
; escribir_inicio_main
main:
mov dword [__esp], esp
; escribir_operando
mov eax, 2
push eax
; escribir_operando
mov eax, 8
push eax
; llamarFuncion
call _pow
; limpiar pila
add esp, 8
push dword eax
; asignar
pop dword eax
mov dword [_resultado], eax
; escribir_operando
mov eax, [_resultado]
push eax
; escribir (print)
call print_int
call print_endofline
add esp, 4
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
