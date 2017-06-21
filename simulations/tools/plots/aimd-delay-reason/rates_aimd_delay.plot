set terminal postscript eps
set style data lines
set style line 2 pt 4
set style line 3 pt 3
set xlabel "Time"
set size noratio 1.5,1.5
set datafile separator ","
set ylabel "rate to one peer"
set output "rates_aimd_delay.eps"
plot "rates_aimd_delay.dat" using 1:2 title "AimdCC-delay=200ms", "aimd_rates_delay_low.dat" using 1:2 title "AimdCC-delay=50ms"
