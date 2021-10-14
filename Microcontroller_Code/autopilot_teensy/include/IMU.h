#ifndef IMU_H
#define IMU_H
#include <Arduino.h>
#include "ICM_20948.h" // Click here to get the library: http://librarymanager/All#SparkFun_ICM_20948_IMU
#include <pb_encode.h>
#include <pb.h>
#include <autopilot.pb.h>

class wrapIMU
{
private:
  // --- Biases --- //
  const float BIAS_GYR_X = 0.1300; // deg/s
  const float BIAS_GYR_Y = -2.8500; // deg/s
  const float BIAS_GYR_Z = -0.7500; // deg/s

  const float BIAS_MAG_X = 17.6100;  // uT
  const float BIAS_MAG_Y = -22.6950; // uT
  const float BIAS_MAG_Z = 17.0450;  // uT

  // Protobuf
  IMUStruct& IMU_struct;

  ICM_20948_I2C myICM;

  void printPaddedInt16b(int16_t val);
  void printRawAGMT(ICM_20948_AGMT_t agmt);
  void printFormattedFloat(float val, uint8_t leading, uint8_t decimals);
  void printScaledAGMT(ICM_20948_AGMT_t agmt);

public:
  wrapIMU(IMUStruct &_IMU_struct);

  // Setup IMU
  void setup();

  // Update IMU Values
  void update();

  // Print values to Serial for debugging
  void print();

};

#endif
