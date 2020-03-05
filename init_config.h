#ifndef INIT_CONFIG_H
#define INIT_CONFIG_H

void init_config_rand(char *configuration, parameters params);
void init_config_rng(char *configuration, unsigned long int seed, parameters params);
void init_zero(double *h, parameters params);

#endif
