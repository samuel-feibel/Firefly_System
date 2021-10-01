#include <SDs.h>

wrapSD::wrapSD(wrapGPS &_myWrapGPS, wrapIMU &_myWrapIMU, wrapBarometer &_mywrapBarometer) : myWrapGPS(_myWrapGPS), myWrapIMU(_myWrapIMU), myWrapBarometer(_mywrapBarometer) {}

void wrapSD::writeFormattedFloat(float val, uint8_t leading, uint8_t decimals)
{
  float aval = abs(val);
  if (val < 0)
  {
    myFile.print("-"); 
  }
  else
  {
    myFile.print(" ");
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
      myFile.print("0");
    }
    else
    {
      break;
    }
  }
  if (val < 0)
  {
    myFile.print(-val, decimals);
  }
  else
  {
    myFile.print(val, decimals);
  }
}

bool wrapSD::setup()
{
  //Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.

  if (!SD.begin(BUILTIN_SDCARD))
  {
    Serial.println("No SD card detected");
    return 0;
  }
  Serial.println("Setting up SD card...Success");

  // First Log Entry
  myFile = SD.open("dataLog.txt", FILE_WRITE);
  myFile.println("================================ Starting Log =================================");
  myFile.print("Current Time: ");
  myFile.print(myWrapGPS.getYear());
  myFile.print("-");
  myFile.print(myWrapGPS.getMonth());
  myFile.print("-");
  myFile.print(myWrapGPS.getDay());
  myFile.print(" ");
  myFile.print(myWrapGPS.getHour());
  myFile.print(":");
  myFile.print(myWrapGPS.getMinute());
  myFile.print(":");
  myFile.print(myWrapGPS.getSecond());
  myFile.print(".");
  //Pretty print leading zeros
  int mseconds = myWrapGPS.getMillisecond();
  if (mseconds < 100)
    myFile.print("0");
  if (mseconds < 10)
    myFile.print("0");
  myFile.print(mseconds);
  myFile.println("");

  // Data Type Header
  myFile.print("Time (ms), ");
  myFile.print("Scaled. Acc x (mg), ");
  myFile.print("Scaled. Acc y (mg), ");
  myFile.print("Scaled. Acc z (mg), ");
  myFile.print("Gyr (DPS) x, ");
  myFile.print("Gyr (DPS) y, ");
  myFile.print("Gyr (DPS) z, ");
  myFile.print("Mag (uT) x, ");
  myFile.print("Mag (uT) y, ");
  myFile.print("Mag (uT) z, ");
  myFile.print("Tmp (C), ");
  myFile.print("Lat, ");
  myFile.print("Lon, ");
  myFile.print("Alt (mm), ");
  myFile.print("Speed (mm/s), ");
  myFile.print("Heading (degrees * 10^-5), ");
  myFile.print("pDOP, ");
  myFile.print("SIV, ");
  myFile.print("Pressure (hPa), ");
  myFile.print("Reciever Throttle Val (0-180), ");
  myFile.print("Reciever Aileron Servo (deg), ");
  myFile.print("Reciever Elevator Servo (deg), ");
  myFile.print("Reciever Rudder Servo (deg), ");
  myFile.print("Auto Mode (deg), ");
  myFile.print("Aux Mode,");
  myFile.print("N, ");
  myFile.print("E, ");
  myFile.print("D, ");
  myFile.print("u, ");
  myFile.print("v, ");
  myFile.print("w, ");
  myFile.print("q1, ");
  myFile.print("q2, ");
  myFile.print("q3, ");
  myFile.print("q4, ");
  myFile.print("Servo Throttle Val (0-180), ");
  myFile.print("Servo Aileron Servo (deg), ");
  myFile.print("Servo Elevator Servo (deg), ");
  myFile.print("Servo Rudder Servo (deg)");

  // close file
  myFile.println("");
  myFile.close();

  return 1;
}

void wrapSD::writeData(BLA::Matrix<10, 1> &xhat, float *servoInput, float *receiverInput, bool &autoMode, int &auxMode)
{

    if (myFile)
  {
    // write data

    // --- IMU --- //
    myFile.print(millis());
    myFile.print(", ");
    writeFormattedFloat(myWrapIMU.getaccX(), 5, 2);
    myFile.print(", ");
    writeFormattedFloat(myWrapIMU.getaccY(), 5, 2);
    myFile.print(", ");
    writeFormattedFloat(myWrapIMU.getaccZ(), 5, 2);
    myFile.print(", ");
    writeFormattedFloat(myWrapIMU.getgyrX(), 5, 2);
    myFile.print(", ");
    writeFormattedFloat(myWrapIMU.getgyrY(), 5, 2);
    myFile.print(", ");
    writeFormattedFloat(myWrapIMU.getgyrZ(), 5, 2);
    myFile.print(", ");
    writeFormattedFloat(myWrapIMU.getmagX(), 5, 2);
    myFile.print(", ");
    writeFormattedFloat(myWrapIMU.getmagY(), 5, 2);
    myFile.print(", ");
    writeFormattedFloat(myWrapIMU.getmagZ(), 5, 2);
    myFile.print(", ");
    writeFormattedFloat(myWrapIMU.gettemp(), 5, 2);
    myFile.print(", ");

    // -- GPS --- //
    long latitude = myWrapGPS.getLatitude();
    myFile.print(latitude);
    myFile.print(", ");
    long longitude = myWrapGPS.getLongitude();
    myFile.print(longitude);
    myFile.print(", ");
    long altitude = myWrapGPS.getAltitude();
    myFile.print(altitude);
    myFile.print(", ");
    long speed = myWrapGPS.getGroundSpeed();
    myFile.print(speed);
    myFile.print(", ");
    long heading = myWrapGPS.getHeading();
    myFile.print(heading);
    myFile.print(", ");
    int pDOP = myWrapGPS.getPDOP();
    myFile.print(pDOP / 100.0, 2);
    myFile.print(", ");
    byte SIV = myWrapGPS.getSIV();
    myFile.print(SIV);
    myFile.print(", ");

    // -- Barometer --//
    myFile.print(myWrapBarometer.getPressure());
    myFile.print(", ");

    // -- Receiver Inputs --- //
    myFile.print(receiverInput[0]);
    myFile.print(", ");
    myFile.print(receiverInput[1]);
    myFile.print(", ");
    myFile.print(receiverInput[2]);
    myFile.print(", ");
    myFile.print(receiverInput[3]);
    myFile.print(", ");
    myFile.print(autoMode);
    myFile.print(", ");
    myFile.print(auxMode);
    myFile.print(", ");

    // -- States --- //
    for (int i = 0;  i < 10; i++)
    {
      myFile.print(xhat(i));
      myFile.print(", ");
    }

    // -- Servo Inputs --- //
    myFile.print(servoInput[0]);
    myFile.print(", ");
    myFile.print(servoInput[1]);
    myFile.print(", ");
    myFile.print(servoInput[2]);
    myFile.print(", ");
    myFile.print(servoInput[3]);

    // close the file:
    myFile.println("");
    //myFile.close();
  }
  else
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void wrapSD::open()
{
  myFile = SD.open("dataLog.txt", FILE_WRITE);
}

void wrapSD::close()
{
  myFile.close();
}
