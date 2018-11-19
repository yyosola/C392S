//
//  main.c
//  transpif
//
//  Created by zcy on 18/11/2018.
//  Copyright © 2018 zcy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

//create a new matrix using width and height as height and width
float * init(int height, int width){
    float * a = malloc(height * width * sizeof(float));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            a[i * width + j] = rand();
        }
    }
    return a;
}

//print the matrix
void printarray(float * a, int height, int width){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%f ", a[i*width + j]);
        }
        printf("\n");
    }
}

//transpose function
void transmatrix(float * a, float * b, int height, int width, int block){
    for (int i = 0; i < height; i += block) {
        for (int j = 0; j < width; j += block) {
            for (int k = 0; k < block; k++) {
                for (int l = 0; l < block; l++) {
                    //check if there is illegal memory access to the matrix(access to the j+l th element of the row which is out of bound)
                    if (j + l > width) {
                        printf("illigal access to the memory\n");
                    }
                    b[j * height + i + l * height + k] = a[i * width + j + k * width + l];
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Wrong number of arguments.\n");
        return 0;
    }
    
    int heightMatrix = atoi(argv[1]);
    int widthMatrix = atoi(argv[2]);
    int widthBlock = atoi(argv[3]);
    
    if (widthBlock > heightMatrix || widthBlock > widthMatrix) {
        fprintf(stderr, "The width can't be bigger than both height and width of the matrix\n");
        return 0;
    }
    
    //create a new matrix with given height and width
    float * matrix = init(heightMatrix, widthMatrix);
    
    //create a new transpose matrix with height as width and width as height
    float * output = malloc(heightMatrix * widthMatrix * sizeof(float));
    
    //printarray(matrix, heightMatrix, widthMatrix);
    
    struct timeval before;
    struct timeval after;
    gettimeofday(&before, NULL);
    
    //transpose
    transmatrix(matrix, output, heightMatrix, widthMatrix, widthBlock);
    
    gettimeofday(&after, NULL);
    
    printf("Time consumed to transpose the matrix with width %d and block width %d: %ld microseconds.\n", widthMatrix, widthBlock, ((after.tv_sec - before.tv_sec) * 1000000L + after.tv_usec) - before.tv_usec);
    
    //printarray(output, widthMatrix, heightMatrix);
    
    return 0;
}
