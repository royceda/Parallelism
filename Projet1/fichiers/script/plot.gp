#!/usr/bin/gnuplot

set term pdf #enhanced monochrome dashed
set output "result.pdf"

set key right bottom

set xlabel "N"
set ylabel "Performance (#items/s)"

plot "res.txt" with linespoints title "Un truk qu'on veut",\
     "res2.txt" with linespoints title "OK"
