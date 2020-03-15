#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "structs.h"

unsigned int tup2ind(unsigned int n, int p, unsigned int N, unsigned int P) {
    /*
    this function converts a 2 tupel of indices to a combined index, to call
    elements of a 2D matrix with periodic boundaries.
    n is the first index and p the second one.

    input:
        unsigned int n: first index of the matrix (row)
        int p: second index of the matrix (column)
        unsigned int N: number of rows of the matrix
        unsigned int P: number of columns of the matrix
    output:
        unsigned int ind: 1D raveled index
    */
    n %= N; // apply the periodic boundary conditions in N
    p = (p + P) % P; // apply the periodic boundary conditions in P

    unsigned long ind = N*p + n;
    if (ind >= UINT_MAX) {
        printf("Error: index too large: %lu\n", ind);
        return -1;
    } else {
        return (unsigned int) ind;
    }
}

void vec_add(double *res, double *v, double *w, long int L) {
    for (long int i=0; i<L; i++) {
        res[i] = v[i] + w[i];
    }
}

void vec_scalar_mul(double *res, double *v, double s, long int L) {
    for (long int i=0; i<L; i++) {
        res[i] = v[i]*s;
    }
}

void vec_scalar_vec_add(double *res, double s, double *v, double *w, long int L) {
    for (long int i=0; i<L; i++) {
        res[i] = s*v[i] + w[i];
    }
}

void print_file(double *v_pot, double *delta_h, int *acceptance, int num_steps, parameters params) {
    /* This function prints an output file with the parameters and observables of an MC chain

    input:
        double *v_pot: array with history of potential energies of the MC chain (size: num_steps)
        double *delta_h: array with history of displacemnts of the MC chain (size: num_steps)
        int *acceptance: array with history of acceptance of the MC chain (size: num_steps)
        int num_steps: number of steps of the chain
        parameters params: struct with parameters
    output:
        void

    */
    FILE *obs_file;
    char str[80];
    //char str2[80];
    sprintf(str, "outputs/out_M_%u_P_%u.txt", params.M, params.P);
    obs_file = fopen(str,"w");
    fprintf(obs_file, "N\tP\tM\tv0\tbeta\tnum_steps\n");
    fprintf(obs_file, "%u\t%u\t%u\t%e\t%e\t%u\n", params.N, params.P, params.M, params.v0, params.beta, num_steps);
    fprintf(obs_file, "i\tV_beta\th^2\tAcc.\n");
    for(unsigned int i = 0; i < num_steps; i++) {
        fprintf(obs_file, "%u\t%e\t%e\t%d\n", i, v_pot[i], delta_h[i], acceptance[i]);
    }

    fclose(obs_file);
}
