######################################################################
## Fichero: ej2.asm
## Autor: David Te�filo Garitagoitia Romero
## Asignatura: E.C. 1º grado
## Grupo de Prácticas: 2113
## Grupo de Teoría 211
## Práctica: 3
## Modelo: B
## Ejercicio: 2
######################################################################

.text
main:	lw $4, A($0)
	jal fun
	sw $3, R($0)
fin:	j fin
fun:	add $2, $4, $0
	addi $3, $2, 2
	jr $31
	
	
.data
A: 20
R:
