#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "steps.h"
#include "structs.h"
#include "observables.h"

int main(){
  parameters params;
  params.N = 10;
  params.P = 5;
  params.size = params.N * params.P;
  params.beta = 0.7;
  params.v0 = 0.2;


  double *h = malloc(params.size*sizeof(double));
  for (int i=0; i<params.size; i++){
    h[i]=2;
  }

  double action_of_2 = action(h,params);
  double potential_of_2 = potential_energy(h,params);

  printf("\n action: %d \t potential: %d \n", action_of_2, potential_of_2);

  free(h);

  return 0;
}
