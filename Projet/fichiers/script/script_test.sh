#!/bin/bash

rm test.data
touch test.data
echo "#NUM_THREAD time/i M/i/s" > result.data

#bash script_test.sh "../bin/atoms -v --omp 0 -i 10 -n 1k"

#Mettre en premier argument la commande d'exécution du programme
#Rajouter OMP_NUM_THREADS

for j in `seq 1 64` 
do
    rm test.data
    touch test.data
    for i in `seq 1 100`;
    do
	`echo "export OMP_NUM_THREADS=$j"`
	`echo "$1"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    done   
    java Parser `echo $j` >> result.data
done



