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

//create a new matrix using n as width
float * init(int n){
    float * a = malloc(n * n * sizeof(float));
    for (int i = 0; i < n * n; i++) {
        a[i] = rand();
    }
    return a;
}

void printarray(float * a, int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", a[i*n + j]);
        }
        printf("\n");
    }
}

void transblock(float * a, float * b, int width, int block){
    for (int i = 0; i < block; i++) {
        for (int j = 0; j < block; j++) {
            b[j * width + i] = a[i * width + j];
        }
    }
}

void transmatrix(float * a, float * b, int width, int block){
    int blocknum = width / block;
    for (int i = 0; i < blocknum; i++) {
        for (int j = 0; j < blocknum; j++) {
            transblock(&a[i * block * width + j * block], &b[j * block * width + i * block], width, block);
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
    
    printarray(matrix, widthMatrix);
    
    float * output = malloc(widthMatrix * widthMatrix * sizeof(float));
    
    transmatrix(matrix, output, widthMatrix, widthBlock);
    
    printarray(output, widthMatrix);
    
    return 0;
}
