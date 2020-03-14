#ifndef UTILS_H
#define UTILS_H

#include "structs.h"

unsigned int tup2ind(unsigned int n, int p, unsigned int N, unsigned int P);
void vec_add(double *res, double *v, double *w, long int L);
void vec_scalar_mul(double *res, double *v, double s, long int L);
void vec_scalar_vec_add(double *res, double s, double *v, double *w, long int L);
void print_file(double *v_pot, double *delta_h, int *acceptance, int num_steps, parameters params);

#endif
