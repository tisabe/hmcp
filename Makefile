main: utils.c init_config.c steps.c observables.c optimal_m.c
	gcc main.c -lm init_config.c utils.c steps.c observables.c optimal_m.c -L/usr/local/lib -lgsl -O3 -Wall -o main.exe

test_md: utils.c init_config.c steps.c
	gcc test_md.c -lm init_config.c utils.c steps.c -L/usr/local/lib -lgsl -O3 -Wall -o test_md.exe
	./test_md.exe

heatbath_test: steps.c utils.c
	gcc heatbath_test.c -lm steps.c utils.c -L/usr/local/lib -lgsl -O3 -Wall -o heatbath_test.exe
	./heatbath_test.exe

tup2ind_test: utils.c
	gcc tup2ind_test.c -lm utils.c -O3 -Wall -o tup2ind_test.exe
	./tup2ind_test.exe

configuration_test: steps.c utils.c observables.c
		gcc configuration_test.c -lm steps.c utils.c observables.c -L/usr/local/lib -lgsl -O3 -Wall -o configuration_test.exe
		./configuration_test.exe
