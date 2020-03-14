#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "utils.h"
#include "init_config.h"
#include "steps.h"
#include "observables.h"

double acceptanceRate(int time_max, parameters params) {

    double *h = malloc(params.size*sizeof(double));
    double *p = malloc(params.size*sizeof(double));

    init_config_rng(h, 42, params);
    gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);

    int acceptance_sum = 0;
    int accepted = 0;
    for (int time=1; time<=time_max; time++) {
        gsl_rng_set(r, time); //use time as seed
        heat_bath(p, r, params);
        accepted = step_mc(p, h, r, params);
        //if (accepted==0){ printf("%i: step %d was not accepted \n", params.M, time); } else { printf("%i: step %d was accepted \n", M, time); }
        acceptance_sum += accepted;
    }
    free(h);
    free(p);

    return (double) acceptance_sum / time_max;
}

//int find_optimal_M(int M_max, int time_max) {
int main(){
    int time_max = 1000;

    parameters params;
    params.N = 10;
    params.P = 50;
    params.v0 = 0.2;
    params.beta = 0.7;
    params.size = params.P * params.N;

    int M_lb = 0;           //M lower bound
    int M_ub = 8;           //M initial upper bound

    double ar_tv;           // acceptance rate target value
    printf("Set acceptance rate target value: ");
    scanf("%lf", &ar_tv);
    printf("The target value is: %lf\n", ar_tv);

    double acc_rate;

    params.M = M_ub;
    while (acceptanceRate(time_max, params) < ar_tv){
        M_ub *= 2;
        params.M = M_ub;
        printf("%lf\t%i\n", acceptanceRate(time_max, params), M_ub);
    }

    while(M_ub != (M_lb + 1)){
        params.M = (M_ub+M_lb) / 2;
        acc_rate = acceptanceRate(time_max, params);
        printf("The acceptance rate for M = %i is %f \n", params.M, acc_rate);
        if (acc_rate < ar_tv){
            M_lb = params.M;
        }else{
            M_ub = params.M;
        }
    }
    return 0;
}
