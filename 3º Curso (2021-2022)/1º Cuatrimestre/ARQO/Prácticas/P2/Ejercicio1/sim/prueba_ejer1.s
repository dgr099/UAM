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
  
  # realiza operaciones
  add $t7, $t1, $t2 # add $r15, $r9, $r10  -> r15=r9+r10 = 3
  add $s0, $t7, $t2 # deberia ser r16 = 5
  add $s1, $t7, $t2 # deberia ser r17 = 5

  add $t7, $t2, $t2 # r15 = 4
  add $s0, $t2, $t7 # deberia ser r16 = 6
  add $s1, $t2, $t7 # deberia ser r17 = 6

  add $t7, $t1, $t2 # r15 = 3
  nop
  nop
  add $s0, $t7, $t2 # deberia ser r16 = 5

  add $t7, $t2, $t2 # r15 = 4
  nop
  nop
  add $s0, $t2, $t7 # deberia ser r16 = 6

  lw $s2, 0($zero)  # lw $r9,  0($r0)  -> r18 = 1
  add $s3, $s2, $t1 # deberia ser r19 = 2

  lw $s2, 4($zero) # lw $r9,  4($r0)  -> r18 = 2
  add $s4, $t1, $s2 # deberia ser r20 = 3

  lw $s2, 8($zero) # r18 = 4
  lui $s2, 0 # r18 = 0

  lw $s2, 12($zero) # r18 = 8
  sw $s2, 48($zero) # pos 12 = 8
