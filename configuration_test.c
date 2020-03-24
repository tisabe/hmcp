#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "steps.h"
#include "structs.h"

int main(){
  parameters params;
  params.N = 10;
  params.P = 5;
  params.size = params.N * params.P;
  params.beta = 0.7;
  params.v0 = 0.2;


  double *h = malloc(size*sizeof(double));
  double *f = malloc(size*sizeof(double));
  for (int i=0; i<params.size; i++){
    h[i]=2;
  }

  double action_of_2 = action(h,params);
  double force_of_2 = force(f,h,params);

  printf("\n action: %d \t force: %d \n", action_of_2, force_of_2);

  free(h);
  free(f);

  return 0;
}
