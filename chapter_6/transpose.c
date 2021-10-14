#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_BLOCK 32

void transpose(int dim, int src[][dim], int dst[][dim]){
    for(int i = 0; i < dim; i++)
        for(int j = 0; j < dim; j++)
            dst[i][j] = src[j][i];
}

// 每次对src和dst各读入一个block，block大小为 MAX_BLOCK * MAX_BLOCK
// 即BLOCKING技术不是向cache中单独读入一行或者读入一列(实际上也无法读入一列)，而是读入行*列构成的block
void faster_transpose(int dim, int src[][dim], int dst[][dim]){
    for(int i = 0; i < dim; i += MAX_BLOCK)
        for(int j = 0; j < dim; j += MAX_BLOCK)
            for(int k = i; k < i + MAX_BLOCK; k++)
                for(int l = j; l < j + MAX_BLOCK; l++)
                    if(k < dim && l < dim)
                        dst[k][l] = src[l][k];
}

int main(int argc, char** argv)
{
    int src[1000][1000], dst[1000][1000];
    for(int i = 0; i < 1000; i++)
        for(int j = 0; j< 1000; j++)
            src[i][j] = rand() % 10000;
            
    clock_t start, end;
    start = clock();
    transpose(1000, src, dst);
    end = clock();
    printf("%lf\n", (double)(end - start)/CLOCKS_PER_SEC);  

    start = clock();
    faster_transpose(1000, src, dst);
    end = clock();
    printf("%lf\n", (double)(end - start)/CLOCKS_PER_SEC);  

    return 0;
}