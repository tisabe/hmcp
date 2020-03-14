#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main(){
    int N;
    printf("Choose a number: ");
    scanf("%i", &N);
    if (isPowerOfTwo(N) == 1){
        printf("%i is a power of 2!\n", N);
    }else{
        printf("%i is not a power of 2!\n", N);
    }
    return 0;
}
