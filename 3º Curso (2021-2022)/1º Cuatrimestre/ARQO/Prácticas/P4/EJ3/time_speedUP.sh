
gnuplot << END_GNUPLOT
#primero imprimo el tiempo
set title "Par vs Serie"
set ylabel "Execution time (s)"
set xlabel "Matrix Size"
set grid
set term png
set output "Timevs.png"
plot "speedUP.dat" using 1:3 with lines lw 2 title "Serie", \
     "speedUP.dat" using 1:4 with lines lw 2 title "Par"
replot
set title "SpeedUp"
set ylabel "SpeedUp"
set xlabel "Matrix Size"
set grid
set term png
set output "SpeedUpvs.png"
plot "speedUP.dat" using 1:2 with lines lw 2 title "SpeedUp"
replot
quit
END_GNUPLOT