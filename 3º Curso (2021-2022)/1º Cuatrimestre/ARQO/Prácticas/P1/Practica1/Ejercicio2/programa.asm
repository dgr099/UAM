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
  addi $t1, 1 # addi $r9, 1 -> r9 = 1
  slti $t2, $t1, 2 # slti $r10, $r9, 2 -> r10=1 si r9 < 2 else 0 = 1
  andi $t3, $t1, 1 # andi $r11, $r9, 1 -> r11=r9 and 1 = 1
  j etiqueta
vuelta:
  j nosalto

etiqueta:
  j vuelta

nosalto:
  j main

