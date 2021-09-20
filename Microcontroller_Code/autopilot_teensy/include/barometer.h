#ifndef BAROMETER_H
#define BAROMETER_H
#include <Adafruit_DPS310.h>

class wrapBarometer
{
private:
  Adafruit_DPS310 dps;
  Adafruit_Sensor *dps_temp = dps.getTemperatureSensor();
  Adafruit_Sensor *dps_pressure = dps.getPressureSensor();
  float pressure;

public:
  wrapBarometer();

  void setup();
  void update();
  float getPressure();
};

#endif
