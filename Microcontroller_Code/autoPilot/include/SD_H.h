#ifndef SD_H
#define SD_H

bool setupSD();
void writeData(double *state, double *servoInput, double *receiverInput, bool *autoMode, int *auxMode);
void openSD();
void closeSD();

#endif