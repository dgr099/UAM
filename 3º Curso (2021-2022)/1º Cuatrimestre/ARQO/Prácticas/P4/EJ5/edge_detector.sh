# Script tiempos medio de pi
# David Teófilo Garitagoitia Romero
# Daniel Cerrato Sánchez

#!/bin/bash
fDAT=edge_detector.dat
NBUCLES=5
rm -f $fDAT
touch $fDAT
declare -a imagenes=("SD.jpg" "HD.jpg" "FHD.jpg" "4k.jpg" "8k.jpg")

#primero tiempo medio de pi_serie
time_s=0
time_p=0
for imagen in "${imagenes[@]}"; do
	echo $imagen
	for ((N = 1 ; N <= NBUCLES ; N += 1)); do
		aux=$(./exe/edgeDetector ./images/$imagen)
		aux=($aux)
		aux_t=${aux[13]}
		time_s=$(echo $aux_t + $time_s | bc)
		aux=$(./exe/edgeDetector_omp ./images/$imagen)
		aux=($aux)
		aux_t=${aux[13]}
		time_p=$(echo $aux_t + $time_p | bc)
	done
	averageTimeS=$(echo scale=6\; $time_s / $NBUCLES | bc)
	averageTimeP=$(echo scale=6\; $time_p / $NBUCLES | bc)
	echo "$imagen: Average Time Serie: $averageTimeS Average Time Par: $averageTimeP SpeedUp: $(echo scale=6\; $averageTimeS / $averageTimeP | bc)" >> $fDAT
done