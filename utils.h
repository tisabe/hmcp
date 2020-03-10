#ifndef UTILS_H
#define UTILS_H

unsigned int tup2ind(unsigned int n, int p, unsigned int N, unsigned int P);
void vec_add(double *res, double *v, double *w, long int L);
void vec_scalar_mul(double *res, double *v, double s, long int L);
void vec_scalar_vec_add(double *res, double s, double *v, double *w, long int L);

#endif
