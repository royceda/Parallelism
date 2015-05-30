#!/usr/bin/gnuplot

set term pdf #enhanced monochrome dashed
set output "num_thread.pdf"

set key right bottom

set xlabel "N"
set ylabel "Time (#micro sec)"

plot "res_schedule.data" with linespoints title "schedule"

