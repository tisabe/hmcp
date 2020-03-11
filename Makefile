main: geometry.c vmath.c metropolis.c init_config.c
	gcc main.c -lm -fopenmp geometry.c vmath.c metropolis.c init_config.c observables.c -L/usr/local/lib -lgsl -o main.exe
	./main.exe

test_md: utils.c init_config.c steps.c
	gcc test_md.c -lm init_config.c utils.c steps.c -lgsl -o test_md.exe
	./test_md.exe

observables: utils.c
	gcc observables.c -lm utils.c -o observables.exe
	./observables.exe
