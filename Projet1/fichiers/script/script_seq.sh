#!/bin/bash

rm test.data
touch test.data
echo "#time/i M/i/s" > res_seq.data

for i in `seq 1 100`;
    do
	`echo "../bin/atoms -v -s 1 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    done   
java Parser >> res_seq.data
