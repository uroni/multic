set terminal postscript eps
set style data lines
set style line 2 pt 4
set style line 3 pt 3
set xlabel "Time"

set datafile separator ","
set ylabel "incoming_bytes"
set output "exp3-perfect.eps"
plot "exp3-perfect.dat" using 1:2 title "PerfectCC-"
