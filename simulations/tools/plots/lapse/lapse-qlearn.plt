set terminal postscript eps
set style data lines
set style line 2 pt 4
set style line 3 pt 3
set xlabel "Time"
set size noratio 1.5,1
set datafile separator ","
set ylabel "Rate of one peer to another"
set output "lapse-qlearn.eps"
plot "lapse-qlearn.dat" using 1:2 title "QLearnCC"
