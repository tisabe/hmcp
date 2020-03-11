#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "structs.h"
#include "utils.h"

double potential_energy(double *h, parameters params) {
    double V;
    V = 0;

    for (int p=0; p<params.P; p++) {
        V += params.v0 * params.v0 / 2 *(h[tup2ind(1,p,params.N,params.P)]*h[tup2ind(1,p,params.N,params.P)]);
        for (int n=0; n<params.N; n++) {
            V += (h[tup2ind(n,p,params.N,params.P)]-h[tup2ind(n-1,p,params.N,params.P)]) * (h[tup2ind(n,p,params.N,params.P)]-h[tup2ind(n-1,p,params.N,params.P)]);
        }
    }
    V = V/ params.P;
    return V;
}

int main(int argc, char const *argv[]) {
  /* code */
  printf("%s\n",'Apfel' );
  return 0;
}
