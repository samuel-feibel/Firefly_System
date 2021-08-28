#ifndef IMU_H
#define IMU_H
#include "ICM_20948.h" // Click here to get the library: http://librarymanager/All#SparkFun_ICM_20948_IMU

class wrapIMU
{
private:
  // --- Biases --- //
  const float BIAS_GYR_X = -0.1325; // deg/s
  const float BIAS_GYR_Y = -1.5720; // deg/s
  const float BIAS_GYR_Z = -0.3581; // deg/s

  const float BIAS_MAG_X = 15.8147;  // uT
  const float BIAS_MAG_Y = -23.0732; // uT
  const float BIAS_MAG_Z = 16.3668;  // uT

  ICM_20948_I2C myICM;

  void printPaddedInt16b(int16_t val);
  void printRawAGMT(ICM_20948_AGMT_t agmt);
  void printFormattedFloat(float val, uint8_t leading, uint8_t decimals);
  void printScaledAGMT(ICM_20948_AGMT_t agmt);

public:
  wrapIMU();

  // Setup IMU
  void setup();

  // Update IMU Values
  void update();

  // Print values to Serial for debugging
  void print();

  // Get Relevant Values
  float getRawgyrX();
  float getRawgyrY();
  float getRawgyrZ();
  float getRawmagX();
  float getRawmagY();
  float getRawmagZ();

  float getaccX();
  float getaccY();
  float getaccZ();
  float getgyrX();
  float getgyrY();
  float getgyrZ();
  float getmagX();
  float getmagY();
  float getmagZ();
  float gettemp();
};

#endif
