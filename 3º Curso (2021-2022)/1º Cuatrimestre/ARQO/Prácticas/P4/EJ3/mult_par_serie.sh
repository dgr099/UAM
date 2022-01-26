# Script tiempos medio de pi
# David Teófilo Garitagoitia Romero
# Daniel Cerrato Sánchez

#!/bin/bash
fDAT=time_serie_hilos_2000.dat
NBUCLES=5
rm -f $fDAT
touch $fDAT
declare -a hilos=(2 3 4)

#primero tiempo medio de pi_serie
time_s=0
#primero para N=2000

time_p1=0
time_p2=0
time_p3=0
echo "1"
		for ((N = 1 ; N <= NBUCLES ; N += 1)); do
		aux=$(./exe/serie 2000)
		aux=($aux)
		aux_t=${aux[2]}
		time_s=$(echo $aux_t + $time_s | bc)
        aux=$(./exe/par_b1 2000 1)
		aux=($aux)
		aux_t=${aux[2]}
		time_p1=$(echo $aux_t + $time_p1 | bc)

        aux=$(./exe/par_b2 2000 1)
		aux=($aux)
		aux_t=${aux[2]}
		time_p2=$(echo $aux_t + $time_p2 | bc)

        aux=$(./exe/par_b3 2000 1)
		aux=($aux)
		aux_t=${aux[2]}
		time_p3=$(echo $aux_t + $time_p3 | bc)
	done
	averageTimeS=$(echo scale=6\; $time_s / $NBUCLES | bc)
	echo "1 $averageTimeS  $(echo scale=6\; $time_p1 / $NBUCLES | bc) $(echo scale=6\; $time_p2 / $NBUCLES | bc) $(echo scale=6\; $time_p3 / $NBUCLES | bc)" >> $fDAT

for hilo in "${hilos[@]}"; do
    echo $hilo
	for ((N = 1 ; N <= NBUCLES ; N += 1)); do
		aux=$(./exe/serie 2000)
		aux=($aux)
		aux_t=${aux[2]}
		time_s=$(echo $aux_t + $time_s | bc)
        aux=$(./exe/par_b1 2000 $hilo)
		aux=($aux)
		aux_t=${aux[2]}
		time_p1=$(echo $aux_t + $time_p1 | bc)

        aux=$(./exe/par_b2 2000 $hilo)
		aux=($aux)
		aux_t=${aux[2]}
		time_p2=$(echo $aux_t + $time_p2 | bc)

        aux=$(./exe/par_b3 2000 $hilo)
		aux=($aux)
		aux_t=${aux[2]}
		time_p3=$(echo $aux_t + $time_p3 | bc)
	done
	echo "$hilo $averageTimeS  $(echo scale=6\; $time_p1 / $NBUCLES | bc) $(echo scale=6\; $time_p2 / $NBUCLES | bc) $(echo scale=6\; $time_p3 / $NBUCLES | bc)" >> $fDAT
done

#ahora imprimo los tiempos para cada numero de hilos
