#ifndef UTILS_H
#define UTILS_H
#include <Arduino.h>
#include <BasicLinearAlgebra.h>

void copy(float *a, float *b, int b_size);

void printArray(float *arr,int m);

float norm3(BLA::Matrix<3> x);

void array2BLAMatrix(BLA::Matrix<6> &vec, float *arr);

void array2BLAMatrix(BLA::Matrix<9> &vec, float *arr);

void BLAMatrix2array(float *arr, BLA::Matrix<10> &vec);

void BLAMatrix2arrayDiag(float *arr, BLA::Matrix<10,10> &vec);



#endif