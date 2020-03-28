#ifndef INIT_CONFIG_H
#define INIT_CONFIG_H
#include <gsl/gsl_rng.h>
#include "structs.h"

void init_config_rng(double *configuration, gsl_rng * r, parameters params);
void init_zero(double *configuration, parameters params);

#endif
