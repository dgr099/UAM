# Script tiempos medio de pi
# David Teófilo Garitagoitia Romero
# Daniel Cerrato Sánchez

#!/bin/bash
fDAT=pi_times.dat
NBUCLES=30
rm -f $fDAT
touch $fDAT
#primero tiempo medio de pi_serie
echo "Serie: " >> $fDAT
time=0
pi=0
for ((N = 1 ; N <= NBUCLES ; N += 1)); do
	aux=$(./pi_serie)
	aux=($aux)
	aux_t=${aux[4]}
	aux_pi=${aux[2]}
	time=$(echo $aux_t + $time | bc)
	pi=$(echo $aux_pi + $pi | bc)
done
averageTime=$(echo scale=6\; $time / $NBUCLES | bc)
averagePi=$(echo scale=6\; $pi/$NBUCLES | bc)
echo "Average time: $averageTime, Average pi: $averagePi" >> $fDAT

echo "Par1: " >> $fDAT
time=0
pi=0
for ((N = 1 ; N <= NBUCLES ; N += 1)); do
	aux=$(./pi_par1)
	aux=($aux)
	aux_t=${aux[6 + 4]}
	aux_pi=${aux[6 + 2]}
	time=$(echo $aux_t + $time | bc)
	pi=$(echo $aux_pi + $pi | bc)
done
averageTime=$(echo scale=6\; $time / $NBUCLES | bc)
averagePi=$(echo scale=6\; $pi/$NBUCLES | bc)
echo "Average time: $averageTime, Average pi: $averagePi" >> $fDAT

echo "Par2: " >> $fDAT
time=0
pi=0
for ((N = 1 ; N <= NBUCLES ; N += 1)); do
	aux=$(./pi_par2)
	aux=($aux)
	aux_t=${aux[6+4]}
	aux_pi=${aux[6+2]}
	time=$(echo $aux_t + $time | bc)
	pi=$(echo $aux_pi + $pi | bc)
done
averageTime=$(echo scale=6\; $time / $NBUCLES | bc)
averagePi=$(echo scale=6\; $pi/$NBUCLES | bc)
echo "Average time: $averageTime, Average pi: $averagePi" >> $fDAT

echo "Par3: " >> $fDAT
time=0
pi=0
for ((N = 1 ; N <= NBUCLES ; N += 1)); do
	aux=$(./pi_par3)
	aux=($aux)
	aux_t=${aux[19+4]}
	aux_pi=${aux[19+2]}
	time=$(echo $aux_t + $time | bc)
	pi=$(echo $aux_pi + $pi | bc)
done
averageTime=$(echo scale=6\; $time / $NBUCLES | bc)
averagePi=$(echo scale=6\; $pi/$NBUCLES | bc)
echo "Average time: $averageTime, Average pi: $averagePi" >> $fDAT

echo "Par4: " >> $fDAT
time=0
pi=0
for ((N = 1 ; N <= NBUCLES ; N += 1)); do
	aux=$(./pi_par4)
	aux=($aux)
	aux_t=${aux[6+4]}
	aux_pi=${aux[6+2]}
	time=$(echo $aux_t + $time | bc)
	pi=$(echo $aux_pi + $pi | bc)
done
averageTime=$(echo scale=6\; $time / $NBUCLES | bc)
averagePi=$(echo scale=6\; $pi/$NBUCLES | bc)
echo "Average time: $averageTime, Average pi: $averagePi" >> $fDAT

echo "Par5: " >> $fDAT
time=0
pi=0
for ((N = 1 ; N <= NBUCLES ; N += 1)); do
	aux=$(./pi_par5)
	aux=($aux)
	aux_t=${aux[4]}
	aux_pi=${aux[2]}
	time=$(echo $aux_t + $time | bc)
	pi=$(echo $aux_pi + $pi | bc)
done
averageTime=$(echo scale=6\; $time / $NBUCLES | bc)
averagePi=$(echo scale=6\; $pi/$NBUCLES | bc)
echo "Average time: $averageTime, Average pi: $averagePi" >> $fDAT

echo "Par6: " >> $fDAT
time=0
pi=0
for ((N = 1 ; N <= NBUCLES ; N += 1)); do
	aux=$(./pi_par6)
	aux=($aux)
	aux_t=${aux[6+4]}
	aux_pi=${aux[6+2]}
	time=$(echo $aux_t + $time | bc)
	pi=$(echo $aux_pi + $pi | bc)
done
averageTime=$(echo scale=6\; $time / $NBUCLES | bc)
averagePi=$(echo scale=6\; $pi/$NBUCLES | bc)
echo "Average time: $averageTime, Average pi: $averagePi" >> $fDAT

echo "Par7: " >> $fDAT
time=0
pi=0
for ((N = 1 ; N <= NBUCLES ; N += 1)); do
	aux=$(./pi_par7)
	aux=($aux)
	aux_t=${aux[4]}
	aux_pi=${aux[2]}
	time=$(echo $aux_t + $time | bc)
	pi=$(echo $aux_pi + $pi | bc)
done
averageTime=$(echo scale=6\; $time / $NBUCLES | bc)
averagePi=$(echo scale=6\; $pi/$NBUCLES | bc)
echo "Average time: $averageTime, Average pi: $averagePi" >> $fDAT