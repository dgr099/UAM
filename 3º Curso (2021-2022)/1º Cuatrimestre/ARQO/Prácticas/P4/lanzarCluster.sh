#!/bin/bash

#
#$ -S /bin/bash
#$ -cwd
#$ -o salida.out
#$ -j y
# Anadir valgrindy gnuplotal path
export PATH=$PATH:/share/apps/tools/valgrind/bin:/share/apps/tools/gnuplot/bin
# Indicar ruta librerías valgrind
export VALGRIND_LIB=/share/apps/tools/valgrind/lib/valgrind
# Pasamos el nombre del script como parámetro
echo "Ejecutando script $1..."
echo ""
source $1