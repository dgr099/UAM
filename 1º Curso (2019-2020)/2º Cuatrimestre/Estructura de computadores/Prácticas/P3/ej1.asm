######################################################################
## Fichero: ej1.asm
## Autor: 
## Asignatura: E.C. 1º grado
## Grupo de Prácticas:
## Grupo de Teoría:
## Práctica: 3
## Modelo: B
## Ejercicio: 1
######################################################################

.text
main:	addi $1, $0, 20
	addi $5, $0, 0
Inicio:	beq $1, $5, fin
	lw $2, vectorA($5)
	sra $3, $2, 1
	sw $3, vectorR($5)
	addi $5, $5, 4
	j Inicio
fin:	j fin

.data
vectorA: 4, 7, 8, 20, -5
vectorR: .space 20
