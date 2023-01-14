Ninicio=100000
Npaso=100000
Nfinal=1000000
#ticks=$(echo "$Ninicio/3" | bc -l)
dats=$(((Nfinal-Ninicio)/Npaso)) #número de datos (iteraciones del bucle)
fDAT=simple_vs_intrinsics.dat
# borrar el fichero DAT anterior
rm -f $fDAT
# generar un nuevo fichero DAT vacío
touch $fDAT
#echo $fDAT

#una vez con esos datos en los ficheros auxiliares podemos pasar al plot
echo "Generating values"
#obtenemos los valores
    Simpl="$(./simple2_times $Ninicio)"
    Intr="$(./simple2_intrinsics_times $Ninicio)"
    echo "$((Ninicio/1000)) $Simpl $Intr" >> $fDAT
    min_vect=$Intr
    min_simple=$Simpl

for ((N = Ninicio + Npaso; N < Nfinal ; N += Npaso)); do
    #ya no se necesita porque retorna solamente el valor del tiempo y no de la N
    #Intr="$(./simple2_intrinsics_times $N | awk '{print $2}')" #cojemos solamente los tiempos
    Simpl="$(./simple2_times $N)"
    Intr="$(./simple2_intrinsics_times $N)"
    echo "$((N/1000)) $Simpl $Intr" >> $fDAT
done
    Simpl="$(./simple2_times $Nfinal)"
    Intr="$(./simple2_intrinsics_times $Nfinal)"
    echo "$((Nfinal/1000)) $Simpl $Intr" >> $fDAT
    max_vect=$Intr
    max_simple=$Simpl
    echo "$max_vect $min_vect"
    echo "$max_simple $min_simple"
    ticks_vect=$(echo "($max_vect-$min_vect)/10" | bc -l) # 10 ticks
    ticks_simple=$(echo "($max_simple-$min_simple)/10" | bc -l) # 10 ticks
    echo "Los ticks son: $ticks_simple"
    echo "Los ticks son: $ticks_vect"
    
echo "Generating plot..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
#generamos tres gráficas, dos individuales y una que muestre ambas para comparar
set title "Simple2 intrinsics times"
set ylabel "Tiempo de ejecución (s)"
set xlabel "Número de pruebas en miles"
set ytics $min_vect, $ticks_vect
set term png
set output "Simple2_times_intrinsics.png"
plot "$fDAT" using 1:3  w l title "Execution time vectorized",

set title "Simple2 times"
set ylabel "Tiempo de ejecución (s)"
set xlabel "Número de pruebas en miles"
set ytics $min_simple, $ticks_simple
set term png
set output "Simple2_times.png"
plot "$fDAT" using 1:2  w l title "Execution time simple"

set title "Simple2 times vs simple2 intrinsics times"
set ylabel "Tiempo de ejecución simple (s)"
set y2label "Tiempo de ejecución vectorizado (s)"
set xlabel "Número de pruebas en miles"
set ytics nomirror
set y2tics $min_vect, $ticks_vect
set ytics $min_simple, $ticks_simple
set term png
set output "Simple2_times vs simple2_times_intrinsics.png"
plot "$fDAT" using 1:3 axis x1y2 w l title "Execution time vectorized", \
    "$fDAT" using 1:2 axis x1y1 w l title "Execution time simple"
quit
END_GNUPLOT

#borramos los ficheros auxiliares