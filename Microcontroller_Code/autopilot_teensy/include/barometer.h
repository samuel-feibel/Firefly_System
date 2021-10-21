#ifndef BAROMETER_H
#define BAROMETER_H
#include <Arduino.h>
#include <pb_encode.h>
#include <autopilot.pb.h>
#include <Adafruit_DPS310.h>

class wrapBarometer
{
private:
  Adafruit_DPS310 dps;
  BarometerStruct &baro_struct;
  float dhdp;
  float alt0;
  float p0;

public:
  wrapBarometer(BarometerStruct &_baro_struct);
  void setup();
  void update();
};

#endif
