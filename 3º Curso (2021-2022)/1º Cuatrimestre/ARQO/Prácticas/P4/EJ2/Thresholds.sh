fPNG1=Thresholds.png
gnuplot << END_GNUPLOT
#primero imprimo el tiempo
set title "Thresholds"
set ylabel "Execution time (s)"
set xlabel "Matrix Size"
set grid
set term png
set output "$fPNG1"
plot "data_Thresholds.dat" using 1:2 with lines lw 2 title "Serie", \
     "data_Thresholds.dat" using 1:3 with lines lw 2 title "Par 0.8T", \
     "data_Thresholds.dat" using 1:4 with lines lw 2 title "Par 0.8T",
replot
quit
END_GNUPLOT