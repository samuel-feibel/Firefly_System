#include <Arduino.h>
#include "IMU.h" // Click here to get the library: http://librarymanager/All#SparkFun_ICM_20948_IMU

#define SERIAL_PORT Serial

#define SPI_PORT SPI // Your desired SPI port.       Used only when "USE_SPI" is defined
#define CS_PIN 2     // Which pin you connect CS to. Used only when "USE_SPI" is defined

#define WIRE_PORT Wire // Your desired Wire port.      Used when "USE_SPI" is not defined
#define AD0_VAL 1      // The value of the last bit of the I2C address.
// On the SparkFun 9DoF IMU breakout the default is 1, and when
// the ADR jumper is closed the value becomes 0

wrapIMU::wrapIMU()
{
  ICM_20948_I2C myICM; // create  ICM_20948_I2C object
}

// Below here are some helper functions to print the data nicely!
void wrapIMU::printPaddedInt16b(int16_t val)
{
  if (val > 0)
  {
    SERIAL_PORT.print(" ");
    if (val < 10000)
    {
      SERIAL_PORT.print("0");
    }
    if (val < 1000)
    {
      SERIAL_PORT.print("0");
    }
    if (val < 100)
    {
      SERIAL_PORT.print("0");
    }
    if (val < 10)
    {
      SERIAL_PORT.print("0");
    }
  }
  else
  {
    SERIAL_PORT.print("-");
    if (abs(val) < 10000)
    {
      SERIAL_PORT.print("0");
    }
    if (abs(val) < 1000)
    {
      SERIAL_PORT.print("0");
    }
    if (abs(val) < 100)
    {
      SERIAL_PORT.print("0");
    }
    if (abs(val) < 10)
    {
      SERIAL_PORT.print("0");
    }
  }
  SERIAL_PORT.print(abs(val));
}

void wrapIMU::printRawAGMT(ICM_20948_AGMT_t agmt)
{
  SERIAL_PORT.print("RAW. Acc [ ");
  printPaddedInt16b(agmt.acc.axes.x);
  SERIAL_PORT.print(", ");
  printPaddedInt16b(agmt.acc.axes.y);
  SERIAL_PORT.print(", ");
  printPaddedInt16b(agmt.acc.axes.z);
  SERIAL_PORT.print(" ], Gyr [ ");
  printPaddedInt16b(agmt.gyr.axes.x);
  SERIAL_PORT.print(", ");
  printPaddedInt16b(agmt.gyr.axes.y);
  SERIAL_PORT.print(", ");
  printPaddedInt16b(agmt.gyr.axes.z);
  SERIAL_PORT.print(" ], Mag [ ");
  printPaddedInt16b(agmt.mag.axes.x);
  SERIAL_PORT.print(", ");
  printPaddedInt16b(agmt.mag.axes.y);
  SERIAL_PORT.print(", ");
  printPaddedInt16b(agmt.mag.axes.z);
  SERIAL_PORT.print(" ], Tmp [ ");
  printPaddedInt16b(agmt.tmp.val);
  SERIAL_PORT.print(" ]");
  SERIAL_PORT.println();
}

void wrapIMU::printFormattedFloat(float val, uint8_t leading, uint8_t decimals)
{
  float aval = abs(val);
  if (val < 0)
  {
    Serial.print("-");
  }
  else
  {
    Serial.print(" ");
  }
  for (uint8_t indi = 0; indi < leading; indi++)
  {
    uint32_t tenpow = 0;
    if (indi < (leading - 1))
    {
      tenpow = 1;
    }
    for (uint8_t c = 0; c < (leading - 1 - indi); c++)
    {
      tenpow *= 10;
    }
    if (aval < tenpow)
    {
      Serial.print("0");
    }
    else
    {
      break;
    }
  }
  if (val < 0)
  {
    Serial.print(-val, decimals);
  }
  else
  {
    Serial.print(val, decimals);
  }
}

void wrapIMU::printScaledAGMT(ICM_20948_AGMT_t agmt)
{
  SERIAL_PORT.print("Scaled. Acc (mg) [ ");
  printFormattedFloat(myICM.accX(), 5, 2);
  SERIAL_PORT.print(", ");
  printFormattedFloat(myICM.accY(), 5, 2);
  SERIAL_PORT.print(", ");
  printFormattedFloat(myICM.accZ(), 5, 2);
  SERIAL_PORT.print(" ], Gyr (DPS) [ ");
  printFormattedFloat(myICM.gyrX(), 5, 2);
  SERIAL_PORT.print(", ");
  printFormattedFloat(myICM.gyrY(), 5, 2);
  SERIAL_PORT.print(", ");
  printFormattedFloat(myICM.gyrZ(), 5, 2);
  SERIAL_PORT.print(" ], Mag (uT) [ ");
  printFormattedFloat(myICM.magX(), 5, 2);
  SERIAL_PORT.print(", ");
  printFormattedFloat(myICM.magY(), 5, 2);
  SERIAL_PORT.print(", ");
  printFormattedFloat(myICM.magZ(), 5, 2);
  SERIAL_PORT.print(" ], Tmp (C) [ ");
  printFormattedFloat(myICM.temp(), 5, 2);
  SERIAL_PORT.print(" ]");
  SERIAL_PORT.println();
}

// Here are the main functions
void wrapIMU::setup()
{

#ifdef USE_SPI
  SPI_PORT.begin();
#else
  WIRE_PORT.begin();
  WIRE_PORT.setClock(400000);
#endif

  bool initialized = false;
  Serial.print("Setting up IMU...");
  while (!initialized)
  {

#ifdef USE_SPI
    myICM.begin(CS_PIN, SPI_PORT);
#else
    myICM.begin(WIRE_PORT, AD0_VAL);
#endif

    // Set full scale ranges for both acc and gyr
    ICM_20948_fss_t myFSS; // This uses a "Full Scale Settings" structure that can contain values for all configurable sensors

    myFSS.a = gpm4; // (ICM_20948_ACCEL_CONFIG_FS_SEL_e)
    // gpm2
    // gpm4
    // gpm8
    // gpm16

    myFSS.g = dps250; // (ICM_20948_GYRO_CONFIG_1_FS_SEL_e)
    // dps250
    // dps500
    // dps1000
    // dps2000

    myICM.setFullScale((ICM_20948_Internal_Acc | ICM_20948_Internal_Gyr), myFSS);

    //SERIAL_PORT.print( F("Initialization of the sensor returned: ") );
    //SERIAL_PORT.println( myICM.statusString() );
    if (myICM.status != ICM_20948_Stat_Ok)
    {
      Serial.println("Failed, retrying");
      delay(500);
    }
    else
    {
      initialized = true;
      Serial.println("Success!");
    }
  }
}

void wrapIMU::update()
{

  if (myICM.dataReady())
  {
    myICM.getAGMT(); // The values are only updated when you call 'getAGMT'
  }
  else
  {
    Serial.println("Waiting for data");
  }
}

void wrapIMU::print()
{
  printFormattedFloat(myICM.accX(), 5, 2);
  Serial.print(", ");
  printFormattedFloat(myICM.accY(), 5, 2);
  Serial.print(", ");
  printFormattedFloat(myICM.accZ(), 5, 2);
  Serial.print(", ");
  printFormattedFloat(myICM.gyrX(), 5, 2);
  Serial.print(", ");
  printFormattedFloat(myICM.gyrY(), 5, 2);
  Serial.print(", ");
  printFormattedFloat(myICM.gyrZ(), 5, 2);
  Serial.print(", ");
  printFormattedFloat(myICM.magX(), 5, 2);
  Serial.print(", ");
  printFormattedFloat(myICM.magY(), 5, 2);
  Serial.print(", ");
  printFormattedFloat(myICM.magZ(), 5, 2);
  Serial.print(", ");
  printFormattedFloat(myICM.temp(), 5, 2);

  Serial.println();
}

// Report Raw Values
float wrapIMU::getRawgyrX()
{
  return myICM.gyrX();
}
float wrapIMU::getRawgyrY()
{
  return myICM.gyrY();
}
float wrapIMU::getRawgyrZ()
{
  return myICM.gyrZ();
}
float wrapIMU::getRawmagX()
{
  return myICM.magX();
}
float wrapIMU::getRawmagY()
{
  return myICM.magY();
}
float wrapIMU::getRawmagZ()

{
  return myICM.magZ();
}

// Report non-biased Values
float wrapIMU::getaccX()
{
  return myICM.accX();
}
float wrapIMU::getaccY()
{
  return myICM.accY();
}
float wrapIMU::getaccZ()
{
  return myICM.accZ();
}
float wrapIMU::getgyrX() // (deg/s)
{
  return myICM.gyrX() - BIAS_GYR_X;
}
float wrapIMU::getgyrY() // (deg/s)
{
  return myICM.gyrY() - BIAS_GYR_Y;
}
float wrapIMU::getgyrZ() // (deg/s)
{
  return myICM.gyrZ() - BIAS_GYR_Z;
}
float wrapIMU::getmagX() // uT
{
  return myICM.magX() - BIAS_MAG_X;
}
float wrapIMU::getmagY() // uT
{
  return myICM.magY() - BIAS_MAG_Y;
}
float wrapIMU::getmagZ() // uT
{
  return myICM.magZ() - BIAS_MAG_Z;
}
float wrapIMU::gettemp() // C
{
  return myICM.temp();
}
