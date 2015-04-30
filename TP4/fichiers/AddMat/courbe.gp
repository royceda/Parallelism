#!/usr/bin/gnuplot

set term pdf #enhanced monochrome dashed
set output "exemple.pdf"

set key right bottom

set xlabel "TILE"
set ylabel "TILE2"

plot "Data.data" with linespoints title "addmat with -g"
