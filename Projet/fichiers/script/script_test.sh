#!/bin/bash

rm data.txt
touch data.txt

# a voir
touch data.txt
bash script_test.sh "./bin/atoms -v --omp 0 -i 10 -n 1k"

#Mettre en premier argument la commande d'exécution du programme
#Rajouter OMP_NUM_THREADS

for i in `seq 1 100`;
do
    `echo "$1"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> data.txt
done   



