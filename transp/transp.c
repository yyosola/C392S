//
//  main.c
//  transp
//
//  Created by zcy on 14/11/2018.
//  Copyright © 2018 zcy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

//create a new matrix using n as width
float * init(int n){
    float * a = malloc(n * n * sizeof(float));
    for (int i = 0; i < n * n; i++) {
        a[i] = rand();
    }
    return a;
}

//print the matrix
void printarray(float * a, int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", a[i*n + j]);
        }
        printf("\n");
    }
}

/*
//transpose the each block
void transblock(float * a, float * b, int width, int block){
    for (int i = 0; i < block; i++) {
        for (int j = 0; j < block; j++) {
            b[j * width + i] = a[i * width + j];
        }
    }
}
*/

//loop through the whole array to transpose each block
void transmatrix(float * a, float * b, int width, int block){
    for (int i = 0; i < width; i += block) {
        for (int j = 0; j < width; j += block) {
            for (int k = 0; k < block; k ++) {
                for (int l = 0; l < block; l ++) {
                    b[j * width + i + l * width + k] = a[i * width + j + k * width + l];
                }
            }
            //transblock(&a[i * block * width + j * block], &b[j * block * width + i * block], width, block);
        }
    }
}

int main(int argc, const char * argv[]) {
    //check the number of argument
    if (argc != 3) {
        fprintf(stderr, "Wrong number of arguments.\n");
        return 0;
    }
    
    int widthMatrix = atoi(argv[1]);
    int widthBlock = atoi(argv[2]);
    
    //create new matrix
    float * matrix = init(widthMatrix);
    
    //printarray(matrix, widthMatrix);
    
    //create the output matrix
    float * output = malloc(widthMatrix * widthMatrix * sizeof(float));
    
    
    struct timeval before;
    struct timeval after;
    gettimeofday(&before, NULL);
    
    //transpose
    transmatrix(matrix, output, widthMatrix, widthBlock);
    
    gettimeofday(&after, NULL);
    
    printf("Time consumed to transpose the matrix with width %d and block width %d: %ld microseconds.\n", widthMatrix, widthBlock, ((after.tv_sec - before.tv_sec) * 1000000L + after.tv_usec) - before.tv_usec);
    
    //printarray(output, widthMatrix);
    
    return 0;
}
