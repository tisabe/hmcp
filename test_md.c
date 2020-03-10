#include <stdlib.h>
#include <stdio.h>

#include "steps.h"
#include "structs.h"
#include "utils.h"
#include "init_config.h"

/*
This code tests the molecular dynamics evolution of the HMC algorithm.
For this, different numbers of steps within the MD step will be tested and
if the difference between prior and posterior hamiltonian converges to zero
as required, for large number of leapfrog steps within the MD.
*/

int main() {
    printf("Testing convergence of energy in the MD simulation...\n");
    int max_M = 100;
    parameters params;
    params.N = 10;
    params.v0 = 0.2;
    params.beta = 0.7;
    params.P = 50;

    double *h = malloc(params.N*params.P*sizeof(double));
    double *h_out = malloc(params.N*params.P*sizeof(double));
    double *p = malloc(params.N*params.P*sizeof(double));
    double *p_out = malloc(params.N*params.P*sizeof(double));



    for (unsigned int m=10; m<=max_M; m+=10) {
        params.M = m; // update the number of leapfrog steps
        init_zero(h, params); // initialize the configuration to zero
        init_config_rng(p, 42, params); //rng needs a seed atm
        double ham = hamiltonian(p, h, params); // calculate the prior hamiltonian

        step_md(p, h, params); // perform the md simulation
        ham = hamiltonian(p, h, params) - ham;
        printf("tau = %e, delta_H = %e\n", 1/(float)m, ham);
    }
    printf("Test completed!\n");

    return 0;
}
