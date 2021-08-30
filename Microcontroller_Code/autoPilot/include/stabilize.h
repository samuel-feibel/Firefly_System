#ifndef STABILIZE_H
#define STABILIZE_H
#include <BasicLinearAlgebra.h>

void stabilize(float *receiverInput, float *servoInput, BLA::Matrix<10> &xhat);

#endif