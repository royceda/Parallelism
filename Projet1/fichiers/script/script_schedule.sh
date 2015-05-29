#!/bin/bash

# Test sur les politiques de distribution
# On présentera les résultats dans un tableau
# Ou alors on fait des courbes mais faut faire tous les test avec NUM_THREADD qui varie

rm test.data
touch test.data

#prendre meilleur num thread (cf script_num_thread)
echo "export OMP_NUM_THREADS=24"

# Mettre différentes valeurs dans export OMP_SCHEDULE

# Test1
echo "#NUM_TEST time/i M/i/s" > res_schedule.data
for i in `seq 1 100`;
do
   
    `echo "OMP_SCHEDULE=\"static\" ../bin/atoms -v --omp 1 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    
    java Parser 1 >> res_schedule1.data
done

# Test2
rm test.data
touch test.data
for i in `seq 1 100`;
do    
    `echo "OMP_SCHEDULE=\"static,2\" ../bin/atoms -v --omp 1 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    
    java Parser 2 >> res_schedule2.data
done

# Test3
rm test.data
touch test.data
for i in `seq 1 100`;
do
   
    `echo "OMP_SCHEDULE=\"static,4\" ../bin/atoms -v --omp 1 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    
    java Parser 3 >> res_schedule3.data
done

# Test4
rm test.data
touch test.data
for i in `seq 1 100`;
do
   
    `echo "OMP_SCHEDULE=\"static,8\" ../bin/atoms -v --omp 1 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    
    java Parser 4 >> res_schedule4.data
done


# Test5
rm test.data
touch test.data
for i in `seq 1 100`;
do
   
    `echo "OMP_SCHEDULE=\"static,16\" ../bin/atoms -v --omp 1 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    
    java Parser 5 >> res_schedule5.data
done

# Test6
rm test.data
touch test.data
for i in `seq 1 100`;
do
   
    `echo "OMP_SCHEDULE=\"dynamic\" ../bin/atoms -v --omp 1 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    
    java Parser 6 >> res_schedule6.data
done

# Test7
rm test.data
touch test.data
for i in `seq 1 100`;
do
   
    `echo "OMP_SCHEDULE=\"dynamic,2\" ../bin/atoms -v --omp 1 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    
    java Parser 7 >> res_schedule7.data
done

# Test8
rm test.data
touch test.data
for i in `seq 1 100`;
do
   
    `echo "OMP_SCHEDULE=\"dynamic,4\" ../bin/atoms -v --omp 1 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    
    java Parser 8 >> res_schedule8.data
done

# Test9
rm test.data
touch test.data
for i in `seq 1 100`;
do
   
    `echo "OMP_SCHEDULE=\"dynamic,8\" ../bin/atoms -v --omp 1 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
    
    java Parser 9 >> res_schedule9.data
done

# Test10
rm test.data
touch test.data
for i in `seq 1 100`;
do
   
    `echo "OMP_SCHEDULE=\"guided\" ../bin/atoms -v --omp 1 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
   
    java Parser 10 >> res_schedule10.data
done

