#!/bin/bash

# Test sur les politiques de distribution 

rm test.data
touch test.data

#prendre meilleur num thread (cf script_num_thread)
echo "export OMP_NUM_THREADS=24"

# Mettre différentes valeurs dans export OMP_SCHEDULE

# Test1
echo "#NUM_THREAD time/i M/i/s" > res_schedule1.data
echo "export OMP_SCHEDULE=TODO"
for i in `seq 1 100`;
do
   
    `echo "../bin/atoms -v --omp 0 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    done   
    java Parser >> res_schedule1.data
done

# Test2
rm test.data
touch test.data
echo "#NUM_THREAD time/i M/i/s" > res_schedule2.data
echo "export OMP_SCHEDULE=TODO"
for i in `seq 1 100`;
do
   
    `echo "../bin/atoms -v --omp 0 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    done   
    java Parser >> res_schedule2.data
done

# Test3
rm test.data
touch test.data
echo "#NUM_THREAD time/i M/i/s" > res_schedule3.data
echo "export OMP_SCHEDULE=TODO"
for i in `seq 1 100`;
do
   
    `echo "../bin/atoms -v --omp 0 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    done   
    java Parser >> res_schedule3.data
done


