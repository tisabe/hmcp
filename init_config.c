#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>


#include "structs.h"
/*********************************************************************************
init_config_rng: this function creates an array of length "size" with random entries between 0 and 1.
		input: *configuration: configuration of length "size"
			r: initialized random number generator
			N: number of atoms
			P: length of the interval for the discretized auxiliary continuous coordinate

init_zero: this function creates an array with all entries equal to 0.
		input: *configuration: configuration of length "size"
			N: number of atoms
			P: length of the interval for the discretized auxiliary continuous coordinate
**********************************************************************************/

void init_config_rng(double *configuration, gsl_rng * r, parameters params){
	unsigned int size= params.N * params.P;
    	for (unsigned int i=0; i<size; i++) {
		configuration[i] = gsl_rng_uniform(r);
    	}
}

void init_zero(double *configuration, parameters params) {
	unsigned int size = params.N*params.P;
	for (unsigned int i=0; i<size; i++) {
		configuration[i] = 0.0;
	}
}
