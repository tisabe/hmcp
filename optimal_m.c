#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "utils.h"
#include "init_config.h"
#include "steps.h"
#include "observables.h"

/*
The find_optimal_M function calculates and returns the ideal M for the system given by the supplied target value of the acceptance rate.

    input:
        int time_max:           max time of the time evolution as stated in the main program
        parameters params:      struct with parameters
    output:
        int:                    ideal value for M with the given target value
*/

static double acceptanceRate(int time_max, parameters params) {                 // Function to return the acceptance rate of the configuration, for documentation see main.c

    double *h = malloc(params.size*sizeof(double));
    double *p = malloc(params.size*sizeof(double));

    init_config_rng(h, 42, params);
    gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);

    int acceptance_sum = 0;
    int accepted = 0;
    for (int time=1; time<=time_max; time++) {
        gsl_rng_set(r, time);
        heat_bath(p, r, params);
        accepted = step_mc(p, h, r, params);
        acceptance_sum += accepted;
    }
    free(h);
    free(p);

    return (double) acceptance_sum / time_max;
}

int find_optimal_M(parameters params) {
    printf("Starting algorithm to find ideal M...\n");

    int time_max = 1000;

    double ar_tv;                                                               // Set acceptance rate target value
    printf("Please enter the acceptance rate target value: ");
    scanf( "%lf", &ar_tv);

    printf("Finding M upper bound...");
    fflush(stdout);
    int M_ub = 8;                                                               // M initial upper bound
    params.M = M_ub;
    while (acceptanceRate(time_max, params) < ar_tv){                           // Increase upper bound by factor of 2 until the acceptance rate is larger than the target value
        params.M *= 2;
        printf("%i...", params.M);
        fflush(stdout);
    }
    M_ub = params.M;
    int M_lb = M_ub / 2;                                                        // M lower bound set as half of the upper bound
    printf(" M upper bound = %i\n", params.M);
    printf("Starting bisection algorithm to find ideal M...");
    fflush(stdout);

    double acc_rate;
    while(M_ub != (M_lb + 1)){                                                  // Do bisection algorithm until the upper bound and lower bound are only 1 apart
        params.M = (M_ub+M_lb) / 2;
        acc_rate = acceptanceRate(time_max, params);                            // Calculate acceptance rate with function above
        printf("%i...", params.M);
        fflush(stdout);
        if (acc_rate < ar_tv){
            M_lb = params.M;                                                    // If acceptance rate smaller than target value, adjust lower bound...
        }else{
            M_ub = params.M;                                                    // ...otherwise adjust upper bound
        }
    }

    params.M = M_lb;
    double acc_rate_l = acceptanceRate(time_max, params);
    params.M = M_ub;
    double acc_rate_u = acceptanceRate(time_max, params);

    if (abs(acc_rate_l - ar_tv) < abs(acc_rate_u - ar_tv)){                     // If acc_rate of M_lb closer to target value, set this as M...
        params.M = M_lb;
        acc_rate = acc_rate_l;
    }else{                                                                      // ...otherwise use M_ub as M
        acc_rate = acc_rate_u;
    }

    printf(" terminated at M = %i, acceptance = %lf\n\n", params.M, acc_rate);

    return params.M;
}
