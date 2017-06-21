set terminal postscript eps
set style data histeps
set style line 2 pt 4
set style line 3 pt 3
set xlabel "Time"

set datafile separator ","
set ylabel "incoming_bytes"
set output "gnup.eps"
plot "gnup.dat-bt.dat" using 1:2 title "AimdCC"
