#include <Arduino.h>

void printArray(double *arr,int m)
{
    for (int k = 0; k < m ; k++)
    {
        Serial.println(arr[k]);
    }
}