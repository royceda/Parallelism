#!/bin/bash

# Test openmp sur le nombre de thread
# Pour machine salle 008, et sur un des serveurs AMD (boursouf, boursouflet et jolicoeur) ; 
# Faire une premiere execution sans le tri selon z
# Faire une deuxieme execution avec le tri selon z:
# /! A la fin de chaque test garder le fichier res_num_thread.data et le renommer /!
# pour tracer 3 courbes sur le mm graphe: - sequentiel (faire un script a part)
#                                         - openmp sans tri z
#                                         - openmp avec tri z



#pr le 3 commenter atom_set_sort dans one_step_move et le premier omp_force et decommanter le second

# Test standard avec n = 1000
# $1 est passe en parametre, c'est "../bin/atoms -v --omp O -i 10 n 1k
rm test.data
touch test.data
echo "#N time/i M/i/s" > res_num_thread.data

for j in `seq 1 64` 
do
    rm test.data
    touch test.data
    echo "export OMP_NUM_THREADS=$j"
    for i in `seq 1 100`;
    do
	`echo "$1"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    done   
    java Parser `echo $j` >> res_num_thread.data
done


