.text 0x0000
	lw $a0, X($0)
	lw $a1, Y($0)
	jal func
	sw $v0, F($0)
fin:	j fin
func:	add $v0, $a0, $a1
	sll $v0, $v0, 1
	jr $ra	
.data 0x2000
X:	0x000A
Y:	0x0004
F:	0x0000
