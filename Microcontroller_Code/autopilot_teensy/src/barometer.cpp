#include "barometer.h"
wrapBarometer::wrapBarometer(BarometerStruct &_baro_struct) : baro_struct(_baro_struct)
{
}

void wrapBarometer::setup()
{
  bool initialized = false;
  // Serial.print("Setting up Barometer...");
  while (!initialized)
  {
    if (!dps.begin_I2C())
    {
      // Serial.println("Failed, retrying");
      delay(500);
    }
    else
    {
      // Serial.println("Success!");
      initialized = true;
    }
  }
  // Setup highest precision
  dps.configurePressure(DPS310_64HZ, DPS310_64SAMPLES);
  dps.configureTemperature(DPS310_64HZ, DPS310_64SAMPLES);
}

void wrapBarometer::update()
{

  sensors_event_t temp_event, pressure_event;

  if (dps.temperatureAvailable() || dps.pressureAvailable())
  {
    dps.getEvents(&temp_event, &pressure_event);
    baro_struct.temperature = temp_event.temperature;
    baro_struct.pressure = pressure_event.pressure;
  }
}