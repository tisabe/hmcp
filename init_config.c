#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>


#include "structs.h"
/*********************************************************************************
init_config_rng: this function initializes random entries between 0 and 1 in the array "configuration".
		input: *configuration: configuration of length "size"
			r: initialized random number generator
			N: number of atoms
			P: length of the interval for the discretized auxiliary continuous coordinate

init_zero: this function initializes all entries to 0 in the array "configuration".
		input: *configuration: configuration of length "size"
			N: number of atoms
			P: length of the interval for the discretized auxiliary continuous coordinate
**********************************************************************************/

void init_config_rng(double *configuration, gsl_rng * r, parameters params){
    	for (unsigned int i=0; i<params.size; i++) {
		configuration[i] = gsl_rng_uniform(r);
    	}
}

void init_zero(double *configuration, parameters params) {
	for (unsigned int i=0; i<params.size; i++) {
		configuration[i] = 0.0;
	}
}
