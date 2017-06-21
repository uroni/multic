set terminal postscript eps
set style data lines
set style line 2 pt 4
set style line 3 pt 3
set xlabel "Time"

set datafile separator ","
set ylabel "drops"
set output "qleancc-exp2-drops.eps"
plot "qleancc-exp2-drops.dat" using 1:2 title "QLearnCC-"
