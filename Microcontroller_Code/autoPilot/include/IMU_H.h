#ifndef IMU_H
#define IMU_H

// Setup IMU
void setup_IMU();

// Update IMU Values
void updateIMU();

// Print values to Serial for debugging
void printIMU();

// Get Relevant Values
float getRawIMUgyrX();
float getRawIMUgyrY();
float getRawIMUgyrZ();
float getRawIMUmagX();
float getRawIMUmagY();
float getRawIMUmagZ();

float getIMUaccX();
float getIMUaccY();
float getIMUaccZ();
float getIMUgyrX();
float getIMUgyrY();
float getIMUgyrZ();
float getIMUmagX();
float getIMUmagY();
float getIMUmagZ();
float getIMUtemp();



#endif