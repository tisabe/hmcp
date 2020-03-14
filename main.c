#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "utils.h"
#include "init_config.h"
#include "steps.h"
#include "observables.h"
#include "optimal_m.h"


int main(int argc, char *argv[]) {

    if(argc!=7)
   {
      printf("Usage guidelines: <time_max> <N> <P> <M> <v0> <beta> \n");
      printf("If <M> = 0, you will be promted to enter a target value for the acceptance rate. The corresponding M will be found by a bisection algorithm for time_max = 1000.\n\n");
      exit(-1);
   }

    int time_max = atoi(argv[1]);

    parameters params;
    params.N = atoi(argv[2]);
    params.P = atoi(argv[3]);
    params.M = atoi(argv[4]);
    params.v0 = atof(argv[5]);
    params.beta = atof(argv[6]);
    params.size = params.P * params.N;

    if (params.M == 0) {
        params.M = find_optimal_M(params);
    }

    double *h = malloc(params.size*sizeof(double));
    double *p = malloc(params.size*sizeof(double));
    double *potential = malloc(time_max*sizeof(double));
    int *acceptance = malloc(time_max*sizeof(int));

    double *delta_h = malloc(time_max*sizeof(double));
    for (int i=0; i<time_max; i++){
        delta_h[i] = 0.1;
    }

    int acceptance_sum = 0;

    init_config_rng(h, 42, params);

    printf("Time\tAcc.\tAcc. rate\tV_beta\n");

    for (int time=1; time<=time_max; time++) {
	    gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
	    gsl_rng_set(r, time); //use time as seed

	    heat_bath(p, r, params);

        acceptance[time] = step_mc(p, h, r, params);

	    potential[time] = potential_energy(h, params);

	    acceptance_sum += acceptance[time];
        if (time % 100 == 0){ printf("%i\t%i\t%lf\t%lf\n", time, acceptance[time], (double) acceptance_sum/time, potential_energy(h, params)); }
    }

    print_file(potential, delta_h, acceptance, time_max, params);

    free(h);
    free(p);
    free(potential);
    free(acceptance);

    free(delta_h);

    return 0;
}
