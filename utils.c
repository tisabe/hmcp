#include <stdlib.h>
#include <stdio.h>

unsigned int tup2ind(unsigned int n, unsigned int p, unsigned int N) {
    /*
    this function converts a 2 tupel of indices to a combined index, to call
    elements of a 2D matrix. n is the first index and p the second one.

    input:
        unsigned int n: first index of the matrix (row)
        unsigned int p: second index of the matrix (column)
        unsigned int N: number of rows of the matrix
    output:
        unsigned int ind: 1D raveled index
    */
    unsigned long ind = N*p + n;
    if (ind >= UINT_MAX) {
        printf("Error: index too large: %lu\n", ind);
        return -1;
    } else if (n>=N) {
        printf("Error: n larger than N: n=%u N=%u\n", n, N);
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
