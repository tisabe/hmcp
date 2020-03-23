#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

int main(){
    int N = 10;
    int P=20;
    int *test_index = malloc(P * N * sizeof(int));

    for (int n=0; n<N; n++){
        for (int p=0; p<P; p++){
            test_index[tup2ind(n,p,N,P)] = tup2ind(n,p,N,P);
        }
    }
    for (int k=0; k<N*P;k++){
        if (k%N==0){
            printf("\n%i\t",test_index[k]);
        }
        else{
            printf("%i\t",test_index[k]);
        }
    }
    return 0;
}
