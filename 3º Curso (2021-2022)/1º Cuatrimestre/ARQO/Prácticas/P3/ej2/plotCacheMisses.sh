#!/bin/bash
TamCacheIni=1024
TamCacheFin=8192
P=3
TamCache=(1024, 2048, 4096, 8192.)
Ninicio=$((1024 + 1024*P)) #con N variando entre 1024+1024*P
Npaso=256
Nfinal=$((1024 + 1024*(P + 1))) #1024+1024*(P+1)
#ficheros auxiliares para el plot
fDATslowRead=cache_lectura_slow.dat
fDATslowWrite=cache_escritura_slow.dat
fDATfastRead=cache_lectura_fast.dat
fDATfastWrite=cache_escritura_fast.dat
#creamos los ficheros auxiliares que emplearemos para el plot
touch -f $fDATslowRead $fDATslowWrite $fDATfastRead $fDATfastWrite
echo "Ejecutando plot cacheMisses.sh ..."
#generamos ficheros auxiliares para lectura fast, escritura fast...
#para cada N generamos una columna con N (tamaño de matriz) 
#y los fallos para esa N
((j=0))
for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
    echo Sumando valores para tam matriz: $N/$Nfinal
    #vacio las arrays y tambien el valor de 
    declare -a slowReads=()
    declare -a slowWrite=()
    declare -a fastRead=()
    declare -a fastWrite=()
    for Cache in "${TamCache[@]}"; do #iteramos en los tamaños de cache
        Cache=${Cache:0:${#Cache}-1} #para obtener los errores en ese tamaño para esa cache
    	echo Concatenando valores para $Cache
        slowReads+=($(cat "cache_$Cache.dat" | head -n $((j+1)) | tail -n 1 | awk '{print $2}')) #se obtiene D1r del programa slow
		slowWrite+=($(cat "cache_$Cache.dat" | head -n $((j+1)) | tail -n 1 | awk '{print $3}')) #se obtiene D1w del programa slow
		fastRead+=($(cat "cache_$Cache.dat" | head -n $((j+1)) | tail -n 1 | awk '{print $4}')) #se obtiene D1r del programa fast
		fastWrite+=($(cat "cache_$Cache.dat" | head -n $((j+1)) | tail -n 1 | awk '{print $5}')) #se obtiene D1w del programa fast
    done
    ((j=j+1))
    #guardamos los datos obtenidos para ese cache size en los ficheros correspondientes
	echo "$N 	${slowReads[@]}" >> $fDATslowRead #tenemos el tamaño de la matriz
	echo "$N 	${slowWrite[@]}" >> $fDATslowWrite #seguidos de la concatenación de los errores en los dist tam de caches
	echo "$N 	${fastRead[@]}" >> $fDATfastRead
	echo "$N 	${fastWrite[@]}" >> $fDATfastWrite
done
#una vez con esos datos en los ficheros auxiliares podemos pasar al plot
echo "Generating plot..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
# primero para mostrar el slow read
set title "${fDATslowRead:6:${#fDATslowRead}-4-6}"
set ylabel "Number of misses"
set xlabel "Matrix Size (Bytes)"
set term png
set output "${fDATslowRead:0:${#fDATslowRead}-4}.png"
plot for [i=2:$j] "$fDATslowRead" using 1:i w l title sprintf("Cache= %s", word("${TamCache[@]}", i-1))

#ahora toca el slow write
set title "${fDATslowWrite:6:${#fDATslowWrite}-4-6}"
set ylabel "Number of misses"
set xlabel "Matrix Size (Bytes)"
set term png
set output "${fDATslowWrite:0:${#fDATslowWrite}-4}.png"
plot for [i=2:$j] "$fDATslowWrite" using 1:i w l title sprintf("Cache= %s", word("${TamCache[@]}", i-1))

#repetimos para el fast
# primero mostramos el fast read
set title "${fDATfastRead:6:${#fDATfastRead}-4-6}"
set ylabel "Number of misses"
set xlabel "Matrix Size (Bytes)"
set term png
set output "${fDATfastRead:0:${#fDATfastRead}-4}.png"
plot for [i=2:$j] "$fDATfastRead" using 1:i w l title sprintf("Cache= %s", word("${TamCache[@]}", i-1))

#ahora toca el fast write
set title "${fDATfastWrite:6:${#fDATfastWrite}-4-6}"
set ylabel "Number of misses"
set xlabel "Matrix Size (Bytes)"
set term png
set output "${fDATfastWrite:0:${#fDATfastWrite}-4}.png"
plot for [i=2:$j] "$fDATfastWrite" using 1:i w l title sprintf("Cache= %s", word("${TamCache[@]}", i-1))
quit
END_GNUPLOT
#borramos los ficheros auxiliares
rm -f $fDATslowRead $fDATslowWrite $fDATfastRead $fDATfastWrite

