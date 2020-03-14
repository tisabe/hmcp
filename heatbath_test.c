#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_rng.h>

#include "steps.h"
#include "structs.h"

/*
This code generates the conjugate momenta to check if they have a gaussian distribution.
*/

int main() {
    printf("Generating momenta\n");
    int max_M = 2000;
    parameters params;
    params.N = 10;
    params.v0 = 0.2;
    params.beta = 0.7;
    params.P = 50;
	params.size = 10*50;
    double *p0 = malloc(params.N*params.P*sizeof(double));
    double *p1 = malloc(params.N*params.P*sizeof(double));

    gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
    gsl_rng_set(r, 42);

    heat_bath(p0, r, params);
    heat_bath(p1, r, params);

    FILE *obs_file;
    obs_file = fopen("outputs/heatbath_test_out.txt","w");
    for (int i=0; i<params.size; i++) {
        fprintf(obs_file, "%e\t%e\n", p0[i], p1[i]);
    }
    fclose(obs_file);

    free(p0);
    free(p1);

    return 0;
}
