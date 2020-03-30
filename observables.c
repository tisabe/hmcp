#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "structs.h"
#include "utils.h"

double potential_energy(double *h, parameters params) {
  /*
  this function calculates and returns the potential energy for the system given by the inputs.

  input:
      double *h: displacements (N*P matrix)
      parameters params: struct with parameters
  output:
      double V: potential energy of the system
  */
    double V = 0;

    for (int p=0; p<params.P; p++) { //summation over all p
        V += (h[tup2ind(0,p,params.N,params.P)]*h[tup2ind(0,p,params.N,params.P)]); //
        for (int n=1; n<params.N; n++) {
            V += (h[tup2ind(n,p,params.N,params.P)]-h[tup2ind(n-1,p,params.N,params.P)]) * (h[tup2ind(n,p,params.N,params.P)]-h[tup2ind(n-1,p,params.N,params.P)]);
        }
    }
    V *= params.v0 * params.v0 / (2 * params.P);
    return V;
}

double square_fluctuation(double *h, parameters params) {                       // = 1/P * sum_{p} (h_{n,p})^2
/*
this function calculates and returns the square fluctuation for the n=N-1 atom given by the inputs.

input:
    double *h: displacements (N*P matrix)
    parameters params: struct with parameters
output:
    double square fluctuation: square fluctuation of the n=N_1 atom
*/
    double H = 0;
    for (int p = 0; p < params.P; p++) {                                        // Summation over all p
        H += h[tup2ind(params.N-1,p,params.P,params.N)] * h[tup2ind(params.N-1,p,params.P,params.N)];
    }
    H /= params.P; // Division  by P to finish average
    return H;
}

double fluctuation(double *h, parameters params) {                       // = 1/P * sum_{p} (h_{n,p})^2
/*
this returns the square fluctuation for the system given by the inputs.

input:
    double *h: displacements (N*P matrix)
    parameters params: struct with parameters
output:
    double fluctuation: displacement of the n=N_1 atom
*/
    double H = 0;
    for (int p = 0; p < params.P; p++) {                                        // Summation over all p
        H += h[tup2ind(params.N-1,p,params.P,params.N)];
    }
    H /= params.P;// Division  by P to finish average
    return H;
}
