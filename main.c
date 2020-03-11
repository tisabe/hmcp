#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "utils.h"
#include "init_config.h"
#include "steps.h"


int main(int argc, char *arv[]) {

    if(argc!=6)
   {
      printf("Usage: <time_max> <N> <P> <M> <v0> <beta> \n\n");
      exit(-1);
   }

    int time_max = atoi(argv[0]);

    parameters params;
    params.N = atoi(argv[1]);
    params.P = atoi(argv[2]);
    params.M = atoi(argv[3]);
    params.v0 = atof(argv[4]);
    params.beta = atof(argv[5]);
    params.size = params.P * params.N;

    double *h = malloc(params.size*sizeof(double));
    double *p = malloc(params.size*sizeof(double));
    int *acceptance = malloc(time_max*sizeof(int));

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
