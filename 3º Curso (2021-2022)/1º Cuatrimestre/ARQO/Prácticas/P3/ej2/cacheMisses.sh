#!/bin/bash

#somos la pareja 3
P=3
# Array con los tamaños
TamCache=(1024, 2048, 4096, 8192.)
Ninicio=$((1024 + 1024*P)) #con N variando entre 1024+1024*P
Npaso=256
Nfinal=$((1024 + 1024*(P + 1))) #1024+1024*(P+1) y


# Valor en base 2 de 8MB.
cacheSuperior=8388608 #2³*2²⁰, se utiliza para la cache fija 8MB
# Nombre de ficheros temporales
auxSlow=auxSlow.dat
auxFast=auxFast.dat

echo "Ejecutando cacheMisses.sh ..."
for Cache in "${TamCache[@]}"; do #iteramos en los tamaños de cache
#echo "$Cache"
#fichero dat
Cache=${Cache:0:${#Cache}-1}
fDAT=cache_$Cache.dat
# borrar el fichero DAT anterior
rm -f $fDAT 
# generar un nuevo fichero DAT vacío
touch $fDAT
#echo $fDAT

N=Ninicio
    for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
        #valgrind para funciones fast y slow empleando el TamCache que toque
        #una caché de nivel superior de
        #tamaño fijo igual a 8 Mbytes. Para todaslas cachés asumir que son de correspondencia directa
        #(es decir, con una única vía) y con tamaño de línea igual a 64 bytes.
        valgrind --tool=cachegrind --cachegrind-out-file=$auxSlow --I1=$Cache,1,64 --D1=$Cache,1,64 --LL=$cacheSuperior,1,64 ./slow $N
        valgrind --tool=cachegrind --cachegrind-out-file=$auxFast --I1=$Cache,1,64 --D1=$Cache,1,64 --LL=$cacheSuperior,1,64 ./fast $N
        #se generan ficheros valgrind auxiliares para leer con cg_annotate
        #Para acceder a estos datos de una forma cómoda, se dispone de la herramienta cg_annotate
        D1mrSlow=$(cg_annotate $auxSlow | head -n 18 | tail -n 1 | awk '{print $5}')
        D1mrFast=$(cg_annotate $auxFast | head -n 18 | tail -n 1 | awk '{print $5}')
        D1mwSlow=$(cg_annotate $auxSlow | head -n 18 | tail -n 1 | awk '{print $8}') 
        D1mwFast=$(cg_annotate $auxFast | head -n 18 | tail -n 1 | awk '{print $8}')
        val="$N	$D1mrSlow	$D1mwSlow	$D1mrFast	$D1mwFast"
        val=${val//[,]/} #quitamos las comas
        echo $val
        echo "$val" >> $fDAT #escribimos resultados en el fichero
    done
    
done

# borrar el fichero auxiliar
rm -f $auxSlow $auxFast