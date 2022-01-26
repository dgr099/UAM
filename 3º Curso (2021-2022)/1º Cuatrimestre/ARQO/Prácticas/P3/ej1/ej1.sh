# Script Ejercicio1
# David Teófilo Garitagoitia Romero
# Daniel Cerrato Sánchez

#!/bin/bash

# inicializar variables
Ninicio=1024
Npaso=1024
Nfinal=16384
fDAT=time_slow_fast.dat
fPNG=time_slow_fast.png
NBUCLES=15
# borrar el fichero DAT y el fichero PNG
rm -f $fDAT fPNG

# generar el fichero DAT vacío
touch $fDAT
slow[0]=0
fast[0]=0
echo "Running ej1..."
# bucle para N desde P hasta Q 
#for N in $(seq $Ninicio $Npaso $Nfinal);
#primero inicializamos el array
((j=0))
for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
	echo "BUCLE: $((I+1)) -> N: $N / $Nfinal..."
	# ejecutar los programas slow y fast consecutivamente con tamaño de matriz N
	# para cada uno, filtrar la línea que contiene el tiempo y seleccionar la
	# tercera columna (el valor del tiempo). Dejar los valores en variables
	# para poder imprimirlos en la misma línea del fichero de datos
	slowTime=$(./slow $N | grep 'time' | awk '{print $3}')
	fastTime=$(./fast $N | grep 'time' | awk '{print $3}')
	slow[$j]=$slowTime
	fast[$j]=$fastTime
	((j=j+1))
done
#una vez inicializados sumamos los nuevos valores
for((I=1; I!=NBUCLES; I+=1)); do
	((j=0))
	for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
		echo "BUCLE: $((I+1)) -> N: $N / $Nfinal..."
		# ejecutar los programas slow y fast consecutivamente con tamaño de matriz N
		# para cada uno, filtrar la línea que contiene el tiempo y seleccionar la
		# tercera columna (el valor del tiempo). Dejar los valores en variables
		# para poder imprimirlos en la misma línea del fichero de datos
		slowTime=$(./slow $N | grep 'time' | awk '{print $3}')
		fastTime=$(./fast $N | grep 'time' | awk '{print $3}')

		aux=${slow[$j]}
		aux=$(echo $aux + $slowTime | bc)
		slow[$j]=$aux

		aux=${fast[$j]}
		aux=$(echo $aux + $fastTime | bc)
		fast[$j]=$aux
		((j=j+1))
	done
done
((j=0))
for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
	slowCount=${slow[$j]}
	fastCount=${fast[$j]}
	averageSlowTime=$(echo scale=6\; $slowCount / $NBUCLES | bc)
	averageFastTime=$(echo scale=6\; $fastCount / $NBUCLES | bc)
	echo "$N	$averageSlowTime	$averageFastTime" >> $fDAT
	((j+=1))
done
echo "Generating plot..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Slow-Fast Execution Time"
set ylabel "Execution time (s)"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNG"
plot "$fDAT" using 1:2 with lines lw 2 title "slow", \
     "$fDAT" using 1:3 with lines lw 2 title "fast"
replot
quit
END_GNUPLOT
