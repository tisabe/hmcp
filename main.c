#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_rng.h>

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
    double *sq_fluct = malloc(time_max*sizeof(double));
    double *fluct = malloc(time_max*sizeof(double));
    double *md_hamiltonian = malloc(time_max*sizeof(double));
    int *acceptance = malloc(time_max*sizeof(int));

    double *delta_h = malloc(time_max*sizeof(double));
    for (int i=0; i<time_max; i++){
        delta_h[i] = 0.1;
    }

    int acceptance_sum = 0;

    gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
    gsl_rng_set(r, 42);

    init_config_rng(h, r, params);
    //init_zero(h, params);

    printf("Time\tAcc.\tAcc. rate\tV_beta\th^2\t Hamiltonian\n");

    for (int time=0; time<time_max; time++) {

       // generate a random p with heat bath
       heat_bath(p, r, params);

       // execute the md step and the mc step and return if the step is accepted or not
       acceptance[time] = step_mc(p, h, r, params);

       // calculate observables
       potential[time] = potential_energy(h, params);
       sq_fluct[time] = square_fluctuation(h, params);
       fluct[time] = fluctuation(h, params);
       md_hamiltonian[time] = hamiltonian(h, p, params);

       acceptance_sum += acceptance[time];

       if (time % 100 == 0){ printf("%i\t%i\t%lf\t%lf\t%lf\t%lf\t%lf\n", time, acceptance[time], (double) acceptance_sum/(time+1), potential[time], sq_fluct[time], md_hamiltonian[time], fluct[time]); }
    }

    print_file(potential, sq_fluct, fluct, md_hamiltonian, acceptance, time_max, params);

    free(h);
    free(p);
    free(potential);
    free(sq_fluct);
    free(fluct);
    free(md_hamiltonian);
    free(acceptance);
    gsl_rng_free (r);
    free(delta_h);

    return 0;
}
