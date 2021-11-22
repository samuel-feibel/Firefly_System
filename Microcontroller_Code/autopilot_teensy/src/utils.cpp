// Helpful Functions for the whole project
#include <Arduino.h>
#include <BasicLinearAlgebra.h>
#include <utils.h>

void copy(float *a, float *b, int b_size)
{
    if (b_size == 0)
        return;
    *a = *b;
    copy(++a, ++b, b_size - 1);
}

void copy(int32_t *a, byte *b, int b_size)
{
    if (b_size == 0)
        return;
    *a = int(*b);
    copy(++a, ++b, b_size - 1);
}

void copy(byte *a, int32_t *b, int b_size)
{
    if (b_size == 0)
        return;
    *a = int(*b);
    copy(++a, ++b, b_size - 1);
}

void printArray(float *arr, int m)
{
    for (int k = 0; k < m; k++)
    {
        Serial.println(arr[k]);
    }
}

float norm3(BLA::Matrix<3> x)
{
    return (sqrt(x(1) * x(1) + x(2) * x(2) + x(3) * x(3)));
}

void array2BLAMatrix(BLA::Matrix<6> &vec, float *arr)
{
    for (int i = 0; i < vec.Rows; i++)
    {
        vec(i) = *arr;
        ++arr;
    }
}

void array2BLAMatrix(BLA::Matrix<9> &vec, float *arr)
{
    for (int i = 0; i < vec.Rows; i++)
    {
        vec(i) = *arr;
        ++arr;
    }
}

void array2BLAMatrix(BLA::Matrix<10> &vec, float *arr)
{
    for (int i = 0; i < vec.Rows; i++)
    {
        vec(i) = *arr;
        ++arr;
    }
}

void array2BLAMatrix(BLA::Matrix<4> &vec, float *arr)
{
    for (int i = 0; i < vec.Rows; i++)
    {
        vec(i) = *arr;
        ++arr;
    }
}

void array2BLAMatrix(BLA::Matrix<3> &vec, float *arr)
{
    for (int i = 0; i < vec.Rows; i++)
    {
        vec(i) = *arr;
        ++arr;
    }
}

void BLAMatrix2array(float *arr, BLA::Matrix<10> &vec)
{
    for (int i = 0; i < vec.Rows; i++)
    {
        *arr = vec(i);
        ++arr;
    }
}

void BLAMatrix2arrayDiag(float *arr, BLA::Matrix<10, 10> &vec)
{
    for (int i = 0; i < vec.Rows; i++)
    {
        *arr = vec(i, i);
        ++arr;
    }
}

void BLAMatrix2array(float *arr, BLA::Matrix<4> &vec)
{
    for (int i = 0; i < vec.Rows; i++)
    {
        *arr = vec(i);
        ++arr;
    }
}

void BLAMatrix2arrayDiag(float *arr, BLA::Matrix<4, 4> &vec)
{
    for (int i = 0; i < vec.Rows; i++)
    {
        *arr = vec(i, i);
        ++arr;
    }
}

void BLAMatrix2array(float *arr, BLA::Matrix<13> &vec)
{
    for (int i = 0; i < vec.Rows; i++)
    {
        *arr = vec(i);
        ++arr;
    }
}

void BLAMatrix2arrayDiag(float *arr, BLA::Matrix<13, 13> &vec)
{
    for (int i = 0; i < vec.Rows; i++)
    {
        *arr = vec(i, i);
        ++arr;
    }
}

void BLAMatrix2array(float *arr, BLA::Matrix<3> &vec)
{
    for (int i = 0; i < vec.Rows; i++)
    {
        *arr = vec(i);
        ++arr;
    }
}

void BLAMatrix2array(float *arr, BLA::Matrix<6> &vec)
{
    for (int i = 0; i < vec.Rows; i++)
    {
        *arr = vec(i);
        ++arr;
    }
}
