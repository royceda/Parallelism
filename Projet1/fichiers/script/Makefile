all:
	javac Parser.java

test: test_num, test_schedule, test_seq

test_num:
	./script_num_thread.sh "../bin/atoms -v --omp 1 -i 10 -n 1k"
	./plot_num.gp

test_schedule:
	./script_schedule.sh "../bin/atoms -v --omp 0 -i 10 -n 1k"
	./plot_schedule.gp

test_seq:
	./script_seq.sh  "../bin/atoms -v --omp 0 -i 10 -n 1k"
