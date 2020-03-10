#ifndef STEPS_H
#define STEPS_H

#include "structs.h"
#include <gsl/gsl_rng.h>

double action(double *h, parameters params);
void force(double *f, double *h, parameters params);
double hamiltonian(double *p, double *h, parameters params);
void heat_bath(double *p, gsl_rng * r, parameters params);
void step_md(double *p, double *h, parameters params);
int step_mc(double *p, double *h, gsl_rng * r, parameters params);

#endif
