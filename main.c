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
      printf("Usage: <time_max> <N> <P> <M> <v0> <beta> \n\n");
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

    if (params.M == 0) { params.M = find_optimal_M(1024, time_max); }

    double *h = malloc(params.size*sizeof(double));
    double *p = malloc(params.size*sizeof(double));
    double *potential = malloc(time_max*sizeof(double));
    int *acceptance = malloc(time_max*sizeof(int));

    int acceptance_sum = 0;

    init_config_rng(h, 42, params);

    for (int time=1; time<=time_max; time++) {
	gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
	gsl_rng_set(r, time); //use time as seed

	heat_bath(p, r, params);

        acceptance[time] = step_mc(p, h, r, params);

	potential[time] = potential_energy(h, params);

	if (acceptance[time]==1){
        	printf("step %d was accepted \n", time);
	} else if (acceptance[time]==0){
 		printf("step %d got not accepted \n", time);
	}
	acceptance_sum += acceptance[time];
    }

    double acceptance_rate = acceptance_sum * 1.0/time_max;
    printf("the acceptance rate is %f \n", acceptance_rate);

    free(h);
    free(p);
    free(potential);
    free(acceptance);

    return 0;
}
