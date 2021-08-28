// Helpful Functions for the whole project
#include <Arduino.h>

void copy(float *a, float *b, int b_size)
{
    if (b_size == 0)
        return;
    *a = *b;
    copy(++a, ++b, b_size - 1);
}

void printArray(float *arr, int m)
{
    for (int k = 0; k < m; k++)
    {
        Serial.println(arr[k]);
    }
}