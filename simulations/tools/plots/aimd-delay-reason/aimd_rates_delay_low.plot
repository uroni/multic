set terminal postscript eps
set style data lines
set style line 2 pt 4
set style line 3 pt 3
set xlabel "Time"

set datafile separator ","
set ylabel "max9RateOf1To0"
set output "aimd_rates_delay_low.eps"
plot "aimd_rates_delay_low.dat" using 1:2 title "AimdCC-delay=50ms"
