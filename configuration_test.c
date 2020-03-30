#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "steps.h"
#include "structs.h"
#include "observables.h"

int main(){
  printf("Testing if analytical solution agrees with numerical result for all h = 2\n");

  parameters params;
  params.N = 10;
  params.P = 5;
  params.size = params.N * params.P;
  params.beta = 0.7;
  params.v0 = 0.2;

  printf("N = %d, P = %d, size = %d, beta = %f, v0 = %f\n", params.N, params.P, params.size, params.beta, params.v0);


  double *h = malloc(params.size*sizeof(double));
  for (int i=0; i<params.size; i++){
    h[i]=2;
  }

  double action_of_2 = action(h,params);
  double potential_of_2 = potential_energy(h,params);

  printf("\n action: %f \t potential: %f \n", action_of_2, potential_of_2);

  printf("Difference to analytical result: action: %e \t potential: %e\n", action_of_2 - 0.056, potential_of_2 - 0.08);

  free(h);

  return 0;
}
