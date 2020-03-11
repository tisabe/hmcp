#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "utils.h"
#include "init_config.h"


int main() {
    
    int time_max = 50;

    parameters params;
    params.M = 100;
    params.N = 10;
    params.v0 = 0.2;
    params.beta = 0.7;
    params.P = 50;
    params.size = params.P * params.N;

    double *h = malloc(params.size*sizeof(double));
    double *p = malloc(params.size*sizeof(double));
    int *acceptance = malloc(time*sizeof(int));

    init_config_rng(h, 42, params);
    
    for (unsigned int time=1; time<=time_max; time++) {
	gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
	gsl_rng_set(r, time); //use time as seed


	heat_bath(p, r, params);
        
        acceptance[time] = step_mc(p, h, r, params);

	if (acceptance[time]==1){
        	printf("step %d was accepted", time);
	} else if (acceptance[time]==0){
 		printf("step %d got not accepted", time);
	}
    }

    return 0;
    free(h);
    free(p);
    free(acceptance);
}
