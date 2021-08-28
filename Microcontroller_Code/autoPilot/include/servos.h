#ifndef SERVOS_H
#define SERVOS_H

void setup_Servos();

void writeServosAngle(float *inputAngle);

void writeServosPWM(volatile unsigned long *inputPWM);

void getRCSignalAngle(float *input, bool *autoMode, int *auxMode);

#endif