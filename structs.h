#ifndef STRUCTS_H
#define STRUCTS_H

//typedef struct parameters_tag parameters;
struct parameters_tag;

typedef struct parameters_tag {
    unsigned int N; // number of atoms
    unsigned int P; // number of path-integral divisions
    unsigned int M; // number of steps per MD integration
    double v0;      // potential energy factor
    double beta;    // inverse thermal energy 1/(k_B*T)
} parameters /*name to reference struct*/;

#endif
