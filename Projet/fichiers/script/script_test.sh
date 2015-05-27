#!/bin/bash

rm data.txt
touch data.txt

#bash script_test.sh "./bin/atoms -v --omp 0 -i 10 -n 1k"

#Mettre en premier argument la commande d'exécution du programme
#Rajouter OMP_NUM_THREADS

for j in `seq 1 64` 
do
    for i in `seq 1 100`;
    do
	`echo "OMP_NUM_THREADS=$j $1"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    done   
    java Parser `echo $j` >> result.data
done

#donner un nom au graphe
./plot.gp


