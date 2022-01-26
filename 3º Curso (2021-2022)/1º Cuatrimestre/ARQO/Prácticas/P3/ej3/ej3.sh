# Script Ejercicio1
# David Teófilo Garitagoitia Romero
# Daniel Cerrato Sánchez

#!/bin/bash

# inicializar variables
P=3
Ninicio=$((256+256*P))
Npaso=32
Nfinal=$((256+256*(P+1)))
fDAT=mult.dat
#fPNG=time_slow_fast.png
NBUCLES=15
# borrar el fichero DAT y el fichero PNG
fPNG1=mult_time.png
fPNG2=mult_cache_D1mr.png
fPNG3=mult_cache_D1mw.png
fDAT_time=mult_time.dat
fDAT_misses=mult_cache.dat
auxMultiMatrices=auxMultiMatrices.dat
auxMultiMatricesTrans=auxMultiMatricesTrans.dat
rm -f $fDAT_time $fPNG1 $fDAT_misses $fPNG2 $fPNG3 $fDAT

# generar el fichero DAT vacío
touch $fDAT
touch $fDAT_time
touch $fDAT_misses
slow[0]=0
fast[0]=0
echo "Running ej3..."
# bucle para N desde P hasta Q 
#for N in $(seq $Ninicio $Npaso $Nfinal);
#primero inicializamos el array, aprovecho esa primera vez para guardar los datos del valgrind
((j=0))
for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
	echo "BUCLE: $((I+1)) -> N: $N / $Nfinal..."
	valgrind --tool=cachegrind --cachegrind-out-file=$auxMultiMatrices --I1=32768,8,64 --D1=32768,8,64 --LL=16777216,16,64 ./multi_matrices $N
    valgrind --tool=cachegrind --cachegrind-out-file=$auxMultiMatricesTrans --I1=32768,8,64 --D1=32768,8,64 --LL=16777216,16,64 ./multi_matrices_transpuesta $N
	D1mrSlow=$(cg_annotate $auxMultiMatrices | head -n 18 | tail -n 1 | awk '{print $5}')
	D1mrFast=$(cg_annotate $auxMultiMatricesTrans | head -n 18 | tail -n 1 | awk '{print $5}')
	D1mwSlow=$(cg_annotate $auxMultiMatrices | head -n 18 | tail -n 1 | awk '{print $8}') 
	D1mwFast=$(cg_annotate $auxMultiMatricesTrans | head -n 18 | tail -n 1 | awk '{print $8}')
	val="$N	$D1mrSlow	$D1mwSlow	$D1mrFast	$D1mwFast"
	val=${val//[,]/} #quitamos las comas
	echo $val
	echo "$val" >> $fDAT_misses #escribimos resultados en el fichero

	# ejecutar los programas slow y fast consecutivamente con tamaño de matriz N
	# para cada uno, filtrar la línea que contiene el tiempo y seleccionar la
	# tercera columna (el valor del tiempo). Dejar los valores en variables
	# para poder imprimirlos en la misma línea del fichero de datos
	slowTime=$(./multi_matrices $N | grep 'time' | awk '{print $3}')
	fastTime=$(./multi_matrices_transpuesta $N | grep 'time' | awk '{print $3}')
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
		slowTime=$(./multi_matrices $N | grep 'time' | awk '{print $3}')
		fastTime=$(./multi_matrices_transpuesta $N | grep 'time' | awk '{print $3}')

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
#haces la media y las pones en el fichero y juntas toda la info
for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
	slowCount=${slow[$j]}
	fastCount=${fast[$j]}
	averageSlowTime=$(echo scale=6\; $slowCount / $NBUCLES | bc)
	averageFastTime=$(echo scale=6\; $fastCount / $NBUCLES | bc)
	D1mrSlow=$(cat $fDAT_misses | head -n $((j+1)) | tail -n 1 | awk '{print $2}')
	D1mwSlow=$(cat $fDAT_misses | head -n $((j+1)) | tail -n 1 | awk '{print $3}')
	D1mrFast=$(cat $fDAT_misses | head -n $((j+1)) | tail -n 1 | awk '{print $4}')
	D1mwFast=$(cat $fDAT_misses | head -n $((j+1)) | tail -n 1 | awk '{print $5}')
	echo "$N	$averageSlowTime	$averageFastTime" >> $fDAT_time
	echo "$N	$averageSlowTime	$D1mrSlow	$D1mwSlow	$averageFastTime	$D1mrFast	$D1mwFast" >> $fDAT
	((j+=1))
done
#por último juntamos todos los datos en un único .dat
gnuplot << END_GNUPLOT
#primero imprimo el tiempo
set title "Mult-Mult trans Execution Time"
set ylabel "Execution time (s)"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNG1"
plot "$fDAT_time" using 1:2 with lines lw 2 title "normal", \
     "$fDAT_time" using 1:3 with lines lw 2 title "trans"
replot

#ahora muestro los fallos, primero para lectura
set title "Mult-Mult trans Misses Read"
set ylabel "Read misses"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNG2"
plot "$fDAT_misses" using 1:2 with lines lw 2 title "normal", \
     "$fDAT_misses" using 1:4 with lines lw 2 title "trans"
replot

#ahora para escritura
set title "Mult-Mult trans Misses Write"
set ylabel "Write misses"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNG3"
plot "$fDAT_misses" using 1:3 with lines lw 2 title "normal", \
     "$fDAT_misses" using 1:5 with lines lw 2 title "trans"
replot
quit
END_GNUPLOT
#eliminamos los ficheros auxiliares
rm -f $auxMultiMatrices $auxMultiMatricesTrans
