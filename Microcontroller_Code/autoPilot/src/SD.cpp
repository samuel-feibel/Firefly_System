#include <Arduino.h>
#include <SD.h>
#include <Wire.h>                           //Needed for I2C to GPS
#include <GPS_H.h>
#include <IMU_H.h>

File myFile;

static void writeFormattedFloat(float val, uint8_t leading, uint8_t decimals) {
  float aval = abs(val);
  if (val < 0) {
    myFile.print("-");
  } else {
    myFile.print(" ");
  }
  for ( uint8_t indi = 0; indi < leading; indi++ ) {
    uint32_t tenpow = 0;
    if ( indi < (leading - 1) ) {
      tenpow = 1;
    }
    for (uint8_t c = 0; c < (leading - 1 - indi); c++) {
      tenpow *= 10;
    }
    if ( aval < tenpow) {
      myFile.print("0");
    } else {
      break;
    }
  }
  if (val < 0) {
    myFile.print(-val, decimals);
  } else {
    myFile.print(val, decimals);
  }
}


bool setupSD() {
  //Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(53, OUTPUT);

  if (!SD.begin(10)) {
    Serial.println("No SD card detected");
    return 0;
  }
  Serial.println("Setting up SD card...Success");

  // First Log Entry
  myFile = SD.open("dataLog.txt", FILE_WRITE);
  myFile.println("================================ Starting Log =================================");
  myFile.print("Current Time: ");
  myFile.print(getGPSYear());
  myFile.print("-");
  myFile.print(getGPSMonth());
  myFile.print("-");
  myFile.print(getGPSDay());
  myFile.print(" ");
  myFile.print(getGPSHour());
  myFile.print(":");
  myFile.print(getGPSMinute());
  myFile.print(":");
  myFile.print(getGPSSecond());
  myFile.print(".");
  //Pretty print leading zeros
  int mseconds = getGPSMillisecond();
  if (mseconds < 100)
    myFile.print("0");
  if (mseconds < 10)
    myFile.print("0");
  myFile.print(mseconds);
  myFile.println("");

  // Data Type Header
  myFile.print("Time (ms), ");
  myFile.print("Scaled. Acc x (mg), ");  myFile.print("Scaled. Acc y (mg), "); myFile.print("Scaled. Acc z (mg), ");
  myFile.print("Gyr (DPS) x, ");  myFile.print("Gyr (DPS) y, "); myFile.print("Gyr (DPS) z, ");
  myFile.print("Mag (uT) x, ");  myFile.print("Mag (uT) y, "); myFile.print("Mag (uT) z, ");
  myFile.print("Tmp (C), ");
  myFile.print("Lat, "); myFile.print("Lon, "); myFile.print("Alt (mm), "); myFile.print("Speed (mm/s), "); 
  myFile.print("Heading (degrees * 10^-5), "); myFile.print("pDOP, "); myFile.print("SIV, ");
  myFile.print("Pressure (hPa), ");
  myFile.print("Reciever Throttle Val (0-180), "); myFile.print("Reciever Aileron Servo (deg), "); myFile.print("Reciever Elevator Servo (deg), "); myFile.print("Reciever Rudder Servo (deg), ");
  myFile.print("Auto Mode (deg), "); myFile.print("Aux Mode");
  myFile.print("N, "); myFile.print("E, "); myFile.print("D, "); myFile.print("u, "); myFile.print("v, "); myFile.print("w, "); myFile.print("q1, "); myFile.print("q2, "); myFile.print("q3, "); myFile.print("q4, ");
  myFile.print("Servo Throttle Val (0-180), "); myFile.print("Servo Aileron Servo (deg), "); myFile.print("Servo Elevator Servo (deg), "); myFile.print("Servo Rudder Servo (deg), ");

  // close file
  myFile.println("");
  myFile.close();

  return 1;
}

void writeData(double *state, double *servoInput, double *receiverInput, bool *autoMode, int *auxMode) {

  //myFile = SD.open("dataLog.txt", FILE_WRITE);
  if (myFile) {
    // write data

    // --- IMU --- //
    myFile.print(millis());
    myFile.print(", ");
    writeFormattedFloat( getIMUaccX(), 5, 2 );
    myFile.print(", ");
    writeFormattedFloat( getIMUaccY(), 5, 2 );
    myFile.print(", ");
    writeFormattedFloat( getIMUaccZ(), 5, 2 );
    myFile.print(", ");
    writeFormattedFloat( getIMUgyrX(), 5, 2 );
    myFile.print(", ");
    writeFormattedFloat( getIMUgyrY(), 5, 2 );
    myFile.print(", ");
    writeFormattedFloat( getIMUgyrZ(), 5, 2 );
    myFile.print(", ");
    writeFormattedFloat( getIMUmagX(), 5, 2 );
    myFile.print(", ");
    writeFormattedFloat( getIMUmagY(), 5, 2 );
    myFile.print(", ");
    writeFormattedFloat( getIMUmagZ(), 5, 2 );
    myFile.print(", ");
    writeFormattedFloat( getIMUtemp(), 5, 2 );
    myFile.print(", ");

    // -- GPS --- //
    long latitude = getGPSLatitude();
    myFile.print(latitude);
    myFile.print(", ");
    long longitude = getGPSLongitude();
    myFile.print(longitude);
    myFile.print(", ");
    long altitude = getGPSAltitude();
    myFile.print(altitude);
    myFile.print(", ");
    long speed = getGPSGroundSpeed();
    myFile.print(speed);
    myFile.print(", ");
    long heading = getGPSHeading();
    myFile.print(heading);
    myFile.print(", ");
    int pDOP = getGPSPDOP();
    myFile.print(pDOP / 100.0, 2);
    myFile.print(", ");
    byte SIV = getGPSSIV();
    myFile.print(SIV);
    myFile.print(", ");

    // -- Barometer --//
    myFile.print("stuff");
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
    myFile.print(*autoMode);
    myFile.print(", ");
    myFile.print(*auxMode);
    myFile.print(", ");


     // -- States --- //
    myFile.print(state[0]);
    myFile.print(", ");
    myFile.print(state[1]);
    myFile.print(", ");
    myFile.print(state[2]);
    myFile.print(", ");
    myFile.print(state[3]);
    myFile.print(", ");
    myFile.print(state[4]);
    myFile.print(", ");
    myFile.print(state[5]);
    myFile.print(", ");
    myFile.print(state[6]);
    myFile.print(", ");
    myFile.print(state[7]);
    myFile.print(", ");
    myFile.print(state[8]);
    myFile.print(", ");
    myFile.print(state[9]);
    myFile.print(", ");

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

  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

}

void openSD() {
  myFile = SD.open("dataLog.txt", FILE_WRITE);
}

void closeSD() {
  myFile.close();
}


