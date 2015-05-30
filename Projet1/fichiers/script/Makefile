all:
	javac Parser.java

test:
	./script_num_thread.sh "../bin/atoms -v --omp 1 -i 10 -n 1k"
	./plot_num.gp
test1:
	./script_schedule.sh "../bin/atoms -v --omp 0 -i 10 -n 1k"
	./plot_schedule.gp
