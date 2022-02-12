# Prog de prueba para Práctica 2. Ej 1

.data 0
num0: .word 1 # posic 0
num1: .word 2 # posic 4
num2: .word 4 # posic 8 
num3: .word 8 # posic 12 
num4: .word 16 # posic 16 
num5: .word 32 # posic 20
num6: .word 0 # posic 24
num7: .word 0 # posic 28
num8: .word 0 # posic 32
num9: .word 0 # posic 36
num10: .word 0 # posic 40
num11: .word 0 # posic 44
.text 0
main:
  # carga num0 a num5 en los registros 9 a 14
  lw $t1, 0($zero) # lw $r9, 0($r0)
  lw $t2, 4($zero) # lw $r10, 4($r0)
  lw $t3, 8($zero) # lw $r11, 8($r0)
  lw $t4, 12($zero) # lw $r12, 12($r0)
  lw $t5, 16($zero) # lw $r13, 16($r0)
  lw $t6, 20($zero) # lw $r14, 20($r0)
  nop
  nop
  nop
  nop
  # RIESGOS REGISTRO REGISTRO
  add $t3, $t1, $t2 # en r11 un 3 = 1 + 2
  add $t1, $t3, $t2 # dependencia con la anterior # en r9 un 5 = 2 + 3
  nop
  nop
  nop
  add $t3, $t1, $t2 # en r11 un 7 = 5 + 2
  nop
  add $t2, $t4, $t3 #dependencia con la 2º anterior # en r10 un 15 = 7 + 8
  nop
  nop
  nop
  add $t3, $t1, $t2  # en r11 un 20 = 5 + 15
  nop
  nop
  add $t2, $t3, $t5 #dependencia con la 3º anterior  # en r10 un 36 = 20 + 16
  nop
  nop
  nop
  add $s0, $t1, $t2  # en r16 un 20 = 5 + 15
  add $s0, $s0, $s0  # Dependencia con la anterior  # en r16 un 40 = 20 + 20. 
  add $s1, $s0, $s0  # dependencia con la anterior  # en r16 un 80 = 40 + 40
  nop
  nop
  nop
  nop
  # RIESGOS REGISTRO MEMORIA
  add $t3, $t1, $t2 # en r11 un 41 = 5 + 36
  sw $t3, 24($zero) # dependencia con la anterior
  nop
  nop
  nop
  add $t4, $t1, $t2 # en r11 un 41 = 5 + 36
  nop
  sw $t4, 28($zero) # dependencia con la 2ª anterior
  nop
  nop
  nop
  add $t5, $t1, $t2 # en r11 un 41 = 5 + 36
  nop
  nop
  sw $t5, 32($zero) # dependencia con la 3ª anterior
  nop
  nop
  nop
  nop
  # RIESGOS MEMORIA REGISTRO
  lw $t3, 0($zero) # en r9 un 1
  add $t4, $t2, $t3 # dependencia con la anterior # en r12 37 = 36 + 1
  nop
  nop
  nop
  lw $t3, 4($zero) # en r9 un 2
  nop
  add $t4, $t2, $t3 # dependencia con la 2ª anterior # en r12 38 = 36 + 2
  nop
  nop
  lw $t3, 8($zero) # en r9 un 4
  nop
  nop
  add $t4, $t2, $t3 # dependencia con la 3ª anterior # en r12 40 = 36 + 4
  nop
  nop
  nop
  # RIESGOS MEMORIA MEMORIA
  sw $t4, 0($zero)
  lw $t2, 0($zero) # en r10 un 40
  nop
  nop
  nop
  nop
  lw $t2, 4($zero) # en r10 un 2
  sw $t2, 0($zero) # Guarda el 2 en posicion 0 de memoria
  
