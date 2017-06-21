set terminal postscript enhanced color eps lw 5 "Helvetica-Bold" 20 solid
set encoding iso_8859_1
set border 31 linewidth 0.3
set pointsize 2.5
set style line 1 pt 7
set style line 2 pt 5
set style line 3 pt 6
set style line 4 pt 11
set style line 5 pt 4 lc 9
set style line 6 pt 2 lc 8
set style line 7 pt 8 lc 5
set style increment user
set size noratio 1.5,1.5
set datafile separator ","
set terminal postscript eps
set style data linespoints
set xlabel "lambda"
set ylabel "Drops per second - mean"
set output "gnup.p.eps"
plot "gnup.p.dat" using 1:2 title "QLearnCC-alpha=0.2","gnup.p.dat" using 1:3 title "QLearnCC-alpha=0.25","gnup.p.dat" using 1:4 title "QLearnCC-alpha=0.3"
