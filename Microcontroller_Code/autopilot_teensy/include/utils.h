#ifndef UTILS_H
#define UTILS_H
#include <Arduino.h>
#include <BasicLinearAlgebra.h>

void copy(float *a, float *b, int b_size);

void copy(int32_t *a, byte *b, int b_size);

void copy(byte *a, int32_t *b, int b_size);

void printArray(float *arr,int m);

float norm3(BLA::Matrix<3> x);

void array2BLAMatrix(BLA::Matrix<6> &vec, float *arr);

void array2BLAMatrix(BLA::Matrix<9> &vec, float *arr);

void array2BLAMatrix(BLA::Matrix<10> &vec, float *arr);

void array2BLAMatrix(BLA::Matrix<4> &vec, float *arr);

void array2BLAMatrix(BLA::Matrix<3> &vec, float *arr);

void BLAMatrix2array(float *arr, BLA::Matrix<10> &vec);

void BLAMatrix2arrayDiag(float *arr, BLA::Matrix<10,10> &vec);

void BLAMatrix2array(float *arr, BLA::Matrix<4> &vec);

void BLAMatrix2arrayDiag(float *arr, BLA::Matrix<4,4> &vec);

void BLAMatrix2array(float *arr, BLA::Matrix<13> &vec);

void BLAMatrix2arrayDiag(float *arr, BLA::Matrix<13,13> &vec);

void BLAMatrix2array(float *arr, BLA::Matrix<3> &vec);

void BLAMatrix2array(float *arr, BLA::Matrix<6> &vec);

#endif