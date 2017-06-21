set terminal postscript eps
set style data errorlines
set style line 2 pt 4
set style line 3 pt 3
set xlabel "Time"

set datafile separator ","
set ylabel "incoming bytes per second"
set output "qlearn-longrun.dat.eps"
plot "qlearn-longrun2.dat-bt.dat" using 1 title "QLearnCC" with histeps
