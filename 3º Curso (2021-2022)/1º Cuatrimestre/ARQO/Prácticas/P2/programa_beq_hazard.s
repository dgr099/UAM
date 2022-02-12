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

  add $s0, $t1, $t1 # r16 = 2
  beq $s0, $s0, efectiva_r
  add $s0, $t1, $t2 # no deberia terminar (r16 != 3)
  add $s0, $t1, $t3 # no deberia terminar (r16 != 5)
  add $s0, $t1, $t4 # no deberia terminar (r16 != 9)
  nop
  nop
  
efectiva_r:
  add $s0, $t1, $t5 # r16 = 17
  beq $s0, $t1, no_efectiva

  add $s0, $t1, $t2 # r16 = 3
  add $s0, $t1, $t3 # r16 = 5
  add $s0, $t1, $t4 # r16 = 9
  add $s0, $t1, $t5 # r16 = 17
  nop
  nop

  lw $s0, 16($zero) # r16 = 16
  beq $s0, $s0, efectiva_lw
  add $s0, $t1, $t2 # no deberia terminar (r16 != 3)
  add $s0, $t1, $t3 # no deberia terminar (r16 != 5)
  add $s0, $t1, $t4 # no deberia terminar (r16 != 9)
  nop
  nop

efectiva_lw:
  lw $s0, 20($zero) # r16 = 32
  beq $s0, $t1, no_efectiva

  add $s0, $t1, $t2 # r16 = 3
  add $s0, $t1, $t3 # r16 = 5
  add $s0, $t1, $t4 # r16 = 9
  add $s0, $t1, $t5 # r16 = 17
  nop
  nop

  beq $t1, $t1, no_efectiva # deberia saltar sin parar pipeline
  lw $s0, 12($zero) # no deberia terminar (r16 != 8)
  add $s0, $t1, $t2 # no deberia terminar (r16 != 3)
  add $s0, $t1, $t3 # no deberia terminar (r16 != 5)
  nop
  nop

no_efectiva:  
  xor $s0, $s0, $s0 # r16 = 0 
