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
  Adafruit_Sensor *dps_temp = dps.getTemperatureSensor();
  Adafruit_Sensor *dps_pressure = dps.getPressureSensor();
  float pressure;
  // BarometerStruct& baro_struct;
  

public:
  // wrapBarometer(BarometerStruct &_baro_struct);
wrapBarometer();
  void setup();
  void update();
  float getPressure();
};

#endif
