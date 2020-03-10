#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
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
	double diff;

        for (int n=0; n<N; n++) {
            diff = h[tup2ind(n, p+1, N, P)] - h[tup2ind(n, p, N, P)];
            s1 += diff*diff;
        }
        s1 *= P/(beta*2);

        for (int n=1; n<N; n++) {
            diff = h[tup2ind(n, p, N, P)] - h[tup2ind(n-1, p, N, P)];
            s2 += diff*diff;
        }
	s2 += h[tup2ind(0,p,N,P)]*h[tup2ind(0,p,N,P)];
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
    unsigned int N = params.N;
    unsigned int P = params.P;
    double v0 = params.v0;
    double beta = params.beta;
    unsigned int size = N * P;

    for (int n=0; n<N; n++) {
        for (int p=0; p<P; p++) {
            double a1 = 0.0; // summand A(n,p)
            double b1 = 0.0; // summand B(n,p)
            int n_max = N-1;

            a1 = P/beta * (h[tup2ind(n, p+1, N, P)] + h[tup2ind(n, p-1, N, P)] - 2 * h[tup2ind(n, p, N, P)]);
			if (n==0) {
				b1 = beta * v0 * v0/P * (h[tup2ind(1, p, N, P)] - 2 * h[tup2ind(0, p, N, P)]);
            } else if (n==N-1) {
                b1 = beta * v0 * v0/P * (h[tup2ind(N-2, p, N, P)] - h[tup2ind(N-1, p, N, P)]);
            } else {
                b1 = beta * v0 * v0/P * (h[tup2ind(n+1, p, N, P)] + h[tup2ind(n-1, p, N, P)] - 2 * h[tup2ind(n, p, N, P)]);
            }
            f[tup2ind(n, p, N, P)]= a1 + b1;
        }
    }
}

double hamiltonian(double *p, double *h, parameters params) {
    /*
    this function calculates the hamiltonian of the system

    input:
        double *p: conjugate momenta (N*P matrix)
        double *h: displacements (N*P matrix)
        parameters params: struct with parameters
    output:
        double H_out: the hamiltonian of the system according to eq. (10)
    */
    unsigned int size = params.N*params.P;
    double H_out = 0.0;
    for (unsigned int i=0; i<size; i++) {
        H_out += p[i]*p[i];
    }
    H_out = H_out/2 + action(h, params);
    return H_out;
}

void heat_bath(double *p, gsl_rng * r, parameters params) {
    /* this function updates the momenta with gaussian distributed random momenta

    input:
        double *p: conjugate momenta (N*P matrix)
        parameters params: struct with parameters
    output:
        void
    */
    unsigned int size = params.N*params.P;
    for (unsigned int i=0; i<size; i++) {
        p[i] = gsl_ran_gaussian(r, 1.0);
    }
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
    unsigned int size = params.size;
    unsigned int M = params.M;

    double tau = 1.0/M; // MD time

    double *f = malloc(size*sizeof(double));

    for (int m=0; m<M; m++) {
        // step 1
        force(f, h, params);
        vec_scalar_vec_add(p, tau/2, f, p, size);

        //step 2
        vec_scalar_vec_add(h, tau, p, h, size);

        //step 3
        force(f, h, params);
        vec_scalar_vec_add(p, tau/2, f, p, size);
    }

    free(f);
}

int step_mc(double *p, double *h, gsl_rng * r, parameters params) {
    /*
    this function performs the metropolis step

    input:
        double *p: conjugate momenta (N*P matrix)
        double *h: displacements (N*P matrix)
        parameters params: struct with parameters
    output:
        int acceptance: if the step was accepted 1, if not 0
    */

	//to do: needs to give back "acceptance" to calculate the overall acceptance

	double r_max = gsl_rng_max(r);
	double H_0 = hamiltonian(p, h, params);
	unsigned int N = params.N;
    unsigned int P = params.P;
	unsigned int size = N * P;

	double *p0 = malloc(size * sizeof(double));
	double *h0 = malloc(size * sizeof(double));
    // copy the state to reset the config, if it's not accepted after the step
    memcpy(p0, p, size*sizeof(double));
    memcpy(h0, h, size*sizeof(double));

	step_md(p, h, params);

	double Delta_H= hamiltonian(p, h, params) - H_0;

	if (Delta_H >= 0) {
        // the new energy is higher so the probability of accepting the higher energy needs to be calculated
		double prob = exp(-1*Delta_H);

		if (gsl_rng_get (r)/r_max > prob) {
            // the random number is higher than the calculated probability, reject the step
            // copy the old configuration into the "output"
            memcpy(p, p0, size*sizeof(double));
			memcpy(h, h0, size*sizeof(double));
			return 0;
		}
        else {
            // the random number is smaller, accept the step
            return 1;
        }
	}
    else {
        // the new energy is smaller, accept the step
        return 1;
    }
}
