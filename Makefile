main: utils.c init_config.c steps.c observables.c optimal_m.c
	gcc main.c -lm init_config.c utils.c steps.c observables.c optimal_m.c -L/usr/local/lib -lgsl -O3 -Wall -o main.exe
	./main.exe

test_md: utils.c init_config.c steps.c
	gcc test_md.c -lm init_config.c utils.c steps.c -lgsl -o test_md.exe
	./test_md.exe

observables: utils.c
	gcc observables.c -lm utils.c -o observables.exe
	./observables.exe

optimal_m: utils.c init_config.c steps.c observables.c
	gcc optimal_m.c -lm init_config.c utils.c steps.c observables.c -L/usr/local/lib -lgsl -o optimal_m.exe
	./optimal_m.exe

heatbath_test: steps.c utils.c
	gcc heatbath_test.c -lm steps.c utils.c -lgsl -o heatbath_test.exe
	./heatbath_test.exe

tup2ind_test: utils.c
	gcc tup2ind_test.c -lm utils.c -o tup2ind_test.exe
	./tup2ind_test.exe
