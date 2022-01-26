.data 0
num0:  .word 1  # posic 0
num1:  .word 2  # posic 4
num2:  .word 4  # posic 8 
num3:  .word 8  # posic 12 
num4:  .word 16 # posic 16 
num5:  .word 32 # posic 20
num6:  .word 0  # posic 24
num7:  .word 0  # posic 28
num8:  .word 0  # posic 32
num9:  .word 0  # posic 36
num10: .word 0  # posic 40
num11: .word 0  # posic 44

.text 0
main:
  # carga num0 a num5 en los registros 9 a 14
  lw $t1, 0($zero)  # lw $r9,  0($r0)  -> r9  = 1
  lw $t2, 4($zero)  # lw $r10, 4($r0)  -> r10 = 2
  lw $t3, 8($zero)  # lw $r11, 8($r0)  -> r11 = 4 
  lw $t4, 12($zero) # lw $r12, 12($r0) -> r12 = 8 
  lw $t5, 16($zero) # lw $r13, 16($r0) -> r13 = 16
  lw $t6, 20($zero) # lw $r14, 20($r0) -> r14 = 32
  # copia num0 a num5 sobre num6 a num11
  sw $t1, 24($zero) # sw $r9,  24($r0) -> data[24] =  1
  sw $t2, 28($zero) # sw $r10, 28($r0) -> data[28] =  2
  sw $t3, 32($zero) # sw $r11, 32($r0) -> data[32] =  4 
  sw $t4, 36($zero) # sw $r12, 36($r0) -> data[36] =  8 
  sw $t5, 40($zero) # sw $r13, 40($r0) -> data[40] =  16
  sw $t6, 44($zero) # sw $r14, 44($r0) -> data[44] =  32
  # carga num6 a num11 en los registros 9 a 14, deberia ser lo mismo
  lw $t1, 24($zero) # lw $r9, 24($r0)  -> r9  no cambia
  lw $t2, 28($zero) # lw $r10, 28($r0) -> r10 no cambia
  lw $t3, 32($zero) # lw $r11, 32($r0) -> r11 no cambia
  lw $t4, 36($zero) # lw $r12, 36($r0) -> r12 no cambia
  lw $t5, 40($zero) # lw $r13, 40($r0) -> r13 no cambia
  lw $t6, 44($zero) # lw $r14, 44($r0) -> r14 no cambia
  
  # realiza operaciones
  add $t7, $t1, $t2 # add $r15, $r9, $r10  -> r15=r9+r10      = 3
  add $s0, $t3, $t4 # add $r16, $r11, $r12 -> r16=r11+r12     = 12
  xor $s1, $t1, $t2 # xor $r17, $r9, $r10  -> r17=r9 xor r10  = 3
  xor $s2, $t7, $t2 # xor $r18, $r15, $r10 -> r18=r15 xor r10 = ERROR del micro: deberia ser 1, pero por dependencia sale 2
  sub $s2, $t3, $t1 # sub $r18, $r11, $r9  -> r18=r11-r9      = 3
  and $s3, $t1, $t2 # and $r19, $r9, $r10  -> r19=r9 and r10  = 0, no cambia
  and $s4, $t7, $t2 # and $r20, $r15, $r10 -> r20=r15 and r10 = 2
  or $s5, $t1, $t2  # or $r21, $r9, $r10   -> r21=r9 or r10   = 3
  or $s6, $s0, $t2  # or $r22, $r16, $r10  -> r22=r16 or r10  = 14
  slt $s7, $t1, $t2 # slt $r23, $r9, $r10  -> r23=1 si r9 < r10 else 0  = 1
  slt $t8, $s0, $t2 # slt $r24, $r16, $r10 -> r24=1 si r16 < r10 else 0 = 0
  
  # carga datos inmediatos en la parte alta de registros
  lui $t1, 1 # lui $r9, 1  -> queda a 65536  (0x00010000)
  lui $t2, 2 # lui $r10, 2 -> queda a 131072 (0x00020000)
  
  # salto condicional: solo comprobamos por ahora que salte o no y la direccion 
  # de salto, pero el procesador ejecutara incorrectamente varias de las 
  # instrucciones tras el beq:
  #     (nota: tras cada beq el ensamblador insertara un NOP -instruccion 0x000000000-
  #     debido al "delayed branching" de MIPS)
  beq $s1, $s2, salto # beq $r17, $r18, salto -> como $r17=$r18=3, salta
  add $t0, $s0, $s1   # add $r8,  $r16, $r17  -> se ejecuta, r8  = 15
  add $t1, $s2, $s3   # add $r9,  $r18, $r19  -> se ejecuta, r9  = 3
  add $t2, $s4, $s5   # add $r10, $r20, $r21  -> no se ejecuta, r10 no cambia
salto:
  sub $t4, $s0, $t7     # sub $r12, $r16, $r15    -> r12 = 9
  beq $s3, $s4, nosalto # beq $r19, $r20, nosalto -> este branch NO debe ejecutarse
final:
  beq $zero, $zero, final # -> bucle infinito, volvera aqui tras varios NOPs.
  nop
  nop
  nop
  nop
nosalto:
  lui $t2, 0xFFFF  # lui $r10, 0xFFFF -> no debe ejecutarse
  beq $zero, $zero, final
  nop
  nop
  nop
  nop

  

