#ifndef UTILS_H
#define UTILS_H
#include <BasicLinearAlgebra.h>

void copy(float *a, float *b, int b_size);

void printArray(float *arr,int m);

float norm3(BLA::Matrix<3> x);

#endif