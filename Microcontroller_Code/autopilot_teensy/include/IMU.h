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
  const float BIAS_GYR [3] = {0.07251906394958496, 1.6412214636802673, 0.3396944999694824}; // deg/s

  const float BIAS_MAG [3] = {-12.225000381469727, -19.350001335144043, 8.775001525878906};  // uT


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
