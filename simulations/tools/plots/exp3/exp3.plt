set terminal postscript eps
set style data lines
set style line 2 pt 4
set style line 3 pt 3
set xlabel "Time"
set size noratio 1.5,1
set datafile separator ","
set ylabel "incoming bytes per second"
set output "exp3.eps"
plot "exp3_qlearn.dat" using 1:2 title "QLearnCC", "exp3_aimd.dat" using 1:2 title "AimdCC", "exp3-perfect.dat" using 1:2 title "PerfectCC"
