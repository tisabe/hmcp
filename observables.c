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

double square_fluctuation(double *h, parameters params) {                       // = 1/P * sum_{n,p} (h_{n,p})^2

    double H = 0;
    for (int p = 0; p < params.P; p++) {                                        // Summation over all p
        for (int n = 0; n < params.N; n++) {                                    // Summation over all n
            H += h[tup2ind(n,p,params.P,params.N)] * h[tup2ind(n,p,params.P,params.N)];
        }
    }
    H /= params.P;
    return H;
}

/*int main(int argc, char const *argv[]) {
  // code
  printf("%s\n","Apfel" );
  return 0;
}*/
