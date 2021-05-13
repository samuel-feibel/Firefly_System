#ifndef SERVOS_H
#define SERVOS_H

void setup_Servos();

void writeServosAngle(double *inputAngle);

void writeServosPWM(volatile unsigned long *inputPWM);

void getRCSignalAngle(double *input, bool *autoMode, int *auxMode);

#endif