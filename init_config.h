#ifndef INIT_CONFIG_H
#define INIT_CONFIG_H

#include "structs.h"

void init_config_rng(double *configuration, unsigned long int seed, parameters params);
void init_zero(double *h, parameters params);

#endif
