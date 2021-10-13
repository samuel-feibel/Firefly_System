#include "barometer.h"
wrapBarometer::wrapBarometer() //BarometerStruct &_baro_struct): baro_struct(_baro_struct)
{
  Adafruit_DPS310 dps;
  Adafruit_Sensor *dps_temp = dps.getTemperatureSensor();
  Adafruit_Sensor *dps_pressure = dps.getPressureSensor();
}


void wrapBarometer::setup()
{
  bool initialized = false;
  Serial.print("Setting up Barometer...");
  while (!initialized)
  {
    if (!dps.begin_I2C())
    {
      Serial.println("Failed, retrying");
      delay(500);
    }
    else
    {
      Serial.println("Success!");
      initialized = true;
    }
  }
  // Setup highest precision
  dps.configurePressure(DPS310_64HZ, DPS310_64SAMPLES);
}

void wrapBarometer::update()
{
  
  sensors_event_t pressure_event;

  // Reading pressure also reads temp so don't check pressure
  // before temp!
  if (dps.pressureAvailable())
  {
    dps_pressure->getEvent(&pressure_event);
    pressure = pressure_event.pressure;
  }
  else
  {
    pressure = -1;
  }

  // Serial.println(pressure);
}

float wrapBarometer::getPressure()
{
  return pressure;
}
