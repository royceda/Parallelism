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
echo "export OMP_SCHEDULE=\"static\""
for i in `seq 1 100`;
do
    `echo "../bin/atoms -v --omp 0 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data  
done
java Parser 1 >> res_schedule.data

# Test2
rm test.data
touch test.data
echo "export OMP_SCHEDULE=\"static,2\""
for i in `seq 1 100`;
do    
    `echo "../bin/atoms -v --omp 0 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
done
java Parser 2 >> res_schedule.data

# Test3
rm test.data
touch test.data
echo "export OMP_SCHEDULE=\"static,4\""   
for i in `seq 1 100`;
do
    `echo "../bin/atoms -v --omp 0 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
done
java Parser 3 >> res_schedule.data

# Test4
rm test.data
touch test.data
echo "export OMP_SCHEDULE=\"static,8\""   
for i in `seq 1 100`;
do
    `echo "../bin/atoms -v --omp 0 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
done
java Parser 4 >> res_schedule.data


# Test5
rm test.data
touch test.data
echo "export OMP_SCHEDULE=\"static,16\""
for i in `seq 1 100`;
do
    `echo "../bin/atoms -v --omp 0 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
done
java Parser 5 >> res_schedule.data

# Test6
rm test.data
touch test.data
echo "export OMP_SCHEDULE=\"dynamic\""
for i in `seq 1 100`;
do
    `echo "../bin/atoms -v --omp 0 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
done
java Parser 6 >> res_schedule.data

# Test7
rm test.data
touch test.data
echo "export OMP_SCHEDULE=\"dynamic,2\""
for i in `seq 1 100`;
do
    `echo "../bin/atoms -v --omp 0 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data  
done
java Parser 7 >> res_schedule.data

# Test8
rm test.data
touch test.data
echo "export OMP_SCHEDULE=\"dynamic,4\""
for i in `seq 1 100`;
do
    `echo " ../bin/atoms -v --omp 0 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
done
java Parser 8 >> res_schedule.data

# Test9
rm test.data
touch test.data
echo "export OMP_SCHEDULE=\"dynamic,8\""
for i in `seq 1 100`;
do
    `echo "../bin/atoms -v --omp 0 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
done
java Parser 9 >> res_schedule.data

# Test10
rm test.data
touch test.data
echo "export OMP_SCHEDULE=\"dynamic,16\""
for i in `seq 1 100`;
do
    `echo "../bin/atoms -v --omp 0 -i 10 -n 1k"` 2>&1 | grep -oE "([[:space:]]+([0-9]*.[0-9])+){3}" >> test.data
done
java Parser 10 >> res_schedule.data

