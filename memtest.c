#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int len = 27;
    double *v0 = malloc(len*sizeof(double));
    double *v1 = malloc(len*sizeof(double));
    for (int i=0; i<len; i++) {
        v0[i] = (float) i;
    }
    printf("before copying:\n");
    for (int i=0; i<len; i++) {
        printf("v0[%d]=%e\n", i, v0[i]);
        printf("v1[%d]=%e\n", i, v1[i]);
    }
    memcpy(v1, v0, len*sizeof(double)); // *sizeof belongs here
    printf("after copying:\n");
    for (int i=0; i<len; i++) {
        printf("v0[%d]=%e\n", i, v0[i]);
        printf("v1[%d]=%e\n", i, v1[i]);
    }
    free(v0);
    free(v1);
}
