######################################################################
## Fichero: Vectores.asm
## Descripción: Programa que...
## Fecha última modificación: 

## Autores: 
## Asignatura: E.C. 1º grado
## Grupo de Prácticas:
## Grupo de Teoría:
## Práctica: 3
## Ejercicio: 3
######################################################################

.text

main:		
	#Lee la variable N
	lw $4, N # Se carga N, que es el número de elementos del vector
	
	#Adaptación de N
	#sll $4, $4, 2 #como sll no se puede hacer se deben hacer bucles para las multiplicaciones
	addi $8 $0 0
	addi $9 $0 2
inicio_bucle: beq $8 $9 fin_bucle_inicio
	add $4 $4 $4
	addi $8 $8 1
	j inicio_bucle

	#Inicializa el bucle for
fin_bucle_inicio:	xor $5, $5, $5 # Inicializa $5 a 0
	
	#Comprobación del bucle
	inicioBucle: 	beq $4,$5, fin
	
	#Lectura de A(i)
	lw $1, A($5) # Carga del dato a[$5] en $1
	
	#Lectura de B(i)
	lw $2, B($5) # Carga del dato b[$5] en $2
	
	#Multiplicación por 4 de B(i)
	#sll $2, $2, 2 # b[i]*4 en $3
	addi $8 $0 0
	addi $9 $0 2
inicio_bucle_2:	beq $8 $9 fin_bucle_2
	add $2 $2 $2 
	addi $8 $8 1
	j inicio_bucle_2
	#Suma 
fin_bucle_2:	add $3, $1, $2 # Ahora $4 vale a[i]+b[i]*4
	
	#Escritura en C(i)
	sw $3, C($5) # Se guarda el resultado en c[$5] 
	
	#Operación del bucle
	addi $5, $5, 4
	
	#Salto a la comparación
	j inicioBucle
	
	#Bucle infinito
	fin: j fin

.data # Comienzo de seccion de memoria de datos
N: 6
A: 2,4,6,8,10,12
B: -1,-5,4,10,1,-5
C: .space 28 #.space reserva el espacio determinado en bytes.


