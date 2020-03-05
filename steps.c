#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <limits.h>

#include "structs.h"
#include "utils.h"

double action(double *h, parameters params) {
    /*
    this function calculates and returns the euclidian action for the system given by the inputs.

    input:
        double *h: displacements (N*P matrix)
        parameters params: struct with parameters
    output:
        double s: euclidian action of the system
    */
    unsigned int N = params.N;
    unsigned int P = params.P;
    double v0 = params.v0;
    double beta = params.beta;

    double s = 0.0; // total sum

    for (int p=0; p<P; p++) {
        double s1 = 0.0; // first partial sum
        double s2 = 0.0; // second partial sum

        for (int n=0; n<N; n++) {
            double diff = h[tup2ind(n, p+1, N, P)] - h[tup2ind(n, p, N, P)];
            s1 += diff*diff;
        }
        s1 *= P/(beta*2);

        for (int n=1; n<N; n++) {
            double diff = h[tup2ind(n, p, N, P)] - h[tup2ind(n-1, p, N, P)];
            s2 += diff*diff;
        }
        s2 *= beta*v0*v0/(2*P);

        s += s1 + s2;
    }
    return s;
}

void force(double *f, double *h, parameters params) {
    /*
    this function returns the MD force for the system given by the inputs.

    input:
        double *h: displacements (N*P matrix)
        parameters params: struct with parameters
    output:
        double *f: forces (N*P matrix)
    */
}

double hamiltonian(double *p, double *h, parameters params) {
    /*
    this function calculates the hamiltonian of the system

    input:
        double *p: conjugate momenta (N*P matrix)
        double *h: displacements (N*P matrix)
        parameters params: struct with parameters
    output:
    */
}

void heat_bath(double *p, parameters params) {
    /* this function updates the momenta with gaussian distributed random momenta

    input:
        double *p: conjugate momenta (N*P matrix)
        parameters params: struct with parameters
    output:
        void
    */
}

void step_md(double *p, double *h, parameters params) {
    /* this function performs the molecular dynamics (MD) step with a leapfrog integration

    input:
        double *p: conjugate momenta (N*P matrix)
        double *h: displacements (N*P matrix)
        parameters params: struct with parameters
    output:
        void
    */
    unsigned int N = params.N;
    unsigned int P = params.P;
    unsigned int M = params.M;

    double tau = 1/M; // MD time

    double *f = malloc(N*P*sizeof(double));

    for (int m=0; m<M; m++) {
        // step 1
        force(f, h, params);
        vec_scalar_vec_add(p, tau/s, f, p, N*P);

        //step 2
        vec_scalar_vec_add(h, tau, p, h, N*P);

        //step 3
        force(f, h, params);
        vec_scalar_vec_add(p, tau/s, f, p, N*P);
    }

}

void step_mc(double *p, double *h, gsl_rng * r, parameters params) {
    /*
    this function performs the metropolis step

    input:
        double *p: conjugate momenta (N*P matrix)
        double *h: displacements (N*P matrix)
        parameters params: struct with parameters
    output:
        void
    */

	//to do: needs to give back "acceptance" to calculate the overall acceptance

	double r_max = gsl_rng_max(r);
	int acceptance = 0;
	double H_0 = hamiltonian(p, h, params);
	unsigned int N = params.N;
   	unsigned int P = params.P;
	unsigned int size = N * P;
		
	double *p0 = malloc(size * sizeof(double))
	double *h0 = malloc(size * sizeof(double))

	step_md(p, h, params);

	Delta_H= hamiltonian(p, h, params) - H_0;

	if (Delta_H >= 0) { 
		double prob = exp(-1*Delta_H);

		if (gsl_rng_get (r)/r_max > prob) {
			memcpy(p, p0, size);
			memcpy(h, h0, size);
			acceptance = 1;
		}
	}
}
