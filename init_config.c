#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>


#include "structs.h"
/*********************************************************************************
this function creates an array of length "size" with random entries between 0 and 1.
**********************************************************************************/
void init_config_rand(char *configuration, parameters params){
	long int L= params.L;

    for (int i=0; i<L; i++) {
        configuration[i] = 2*(rand() % 2) - 1;
    }
}

void init_config_rng(char *configuration, unsigned long int seed, parameters params){
	long int n= params.N;
	long int p= params.P;
	long int size= n * p;
	gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
	gsl_rng_set(r, seed); // set the seed for the rng
	//double r_max = gsl_rng_max(r);

    	for (int i=0; i<L; i++) {
		configuration[i] = r/r_max;
    	}
    	gsl_rng_free(r);
}

void init_zero(double *h, parameters params) {
	unsigned int max_ind = params.N*params.P;
	for (unsigned int i=0, i<max_ind; i++) {
		h[i] = 0.0;
	}
}
