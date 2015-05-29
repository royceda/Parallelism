#!/usr/bin/gnuplot

set term pdf #enhanced monochrome dashed
set output "./Bi\ Xeon/num_thread.pdf"

set key right bottom

set xlabel "N"
set ylabel "Time (#micro sec)"

plot "res_num_thread.data" with linespoints title "num thread"
