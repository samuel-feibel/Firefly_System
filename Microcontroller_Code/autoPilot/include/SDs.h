#ifndef SD_H
#define SD_H

bool setupSD();
void writeData(float *state, float *servoInput, float *receiverInput, bool *autoMode, int *auxMode);
void openSD();
void closeSD();

#endif