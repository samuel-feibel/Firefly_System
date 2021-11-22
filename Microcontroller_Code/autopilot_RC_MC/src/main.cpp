/*  rcTiming.ino -- JW, 30 November 2015 -- 
 * Uses pin-change interrupts on A0-A4 to time RC pulses
 *
 * Ref: http://arduino.stackexchange.com/questions/18183/read-rc-receiver-channels-using-interrupt-instead-of-pulsein
 *
 */

#include <Arduino.h>
#include <Streaming.h>
#include <Servo.h>
#define HWSERIAL Serial1

static byte rcOld;                  // Prev. states of inputs
volatile unsigned long rcRises[6];  // times of prev. rising edges
volatile unsigned long rcTimes[6];  // recent pulse lengths
volatile unsigned int rcChange = 0; // Change-counter

#define interruptPin0 A0
#define interruptPin1 A1
#define interruptPin2 A2
#define interruptPin3 A3
#define interruptPin4 A4
#define interruptPin5 A5

#define throttlePin 10
#define aileronPin 9
#define elevatorPin 6
#define rudderPin 5
#define auxPin 3

unsigned long prevLoopTime;

static bool wasServoSignal = 0;
byte servoSignal[6];

Servo throttleServo;
Servo aileronServo;
Servo elevatorServo;
Servo rudderServo;

static int mapRC(unsigned long rcTime)
{
  int mapped = 180 * ((rcTime - 1100.0) / (1900 - 1100));
  if (mapped > 180)
  {
    return 180;
  }

  if (mapped < 0)
  {
    return 0;
  }

  return mapped;
}

void rcTiming()
{
  byte rcNew = 0b00000000;

  if (digitalRead(interruptPin0))
  {
    bitSet(rcNew, 0);
  }
  if (digitalRead(interruptPin1))
  {
    bitSet(rcNew, 1);
  }
  if (digitalRead(interruptPin2))
  {
    bitSet(rcNew, 2);
  }
  if (digitalRead(interruptPin3))
  {
    bitSet(rcNew, 3);
  }
  if (digitalRead(interruptPin4))
  {
    bitSet(rcNew, 4);
  }
  if (digitalRead(interruptPin5))
  {
    bitSet(rcNew, 5);
  }

  byte changes = rcNew ^ rcOld; // Notice changed bits
  byte channel = 0;
  unsigned long now = micros(); // micros() is ok in int routine
  while (changes)
  {
    if ((changes & 1))
    { // Did current channel change?
      if ((rcNew & (1 << channel)))
      {                         // Check rising edge
        rcRises[channel] = now; // Is rising edge
      }
      else
      { // Is falling edge
        rcTimes[channel] = now - rcRises[channel];
      }
    }
    changes >>= 1; // shift out the done bit
    ++channel;
    ++rcChange;
  }
  rcOld = rcNew; // Save new state
}

// Be sure to call setup_rcTiming() from setup()
void setup_rcTiming()
{
  rcOld = 0;
  pinMode(interruptPin0, INPUT_PULLUP);
  pinMode(interruptPin1, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  pinMode(interruptPin3, INPUT_PULLUP);
  pinMode(interruptPin4, INPUT_PULLUP);
  pinMode(interruptPin5, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin0), rcTiming, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin1), rcTiming, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), rcTiming, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin3), rcTiming, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin4), rcTiming, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin5), rcTiming, CHANGE);
}

void setup()
{
  Serial.begin(115200);
  HWSERIAL.begin(9600);
  setup_rcTiming();

  throttleServo.attach(throttlePin);
  aileronServo.attach(aileronPin);
  elevatorServo.attach(elevatorPin);
  rudderServo.attach(rudderPin);

  prevLoopTime = millis();
}

void loop()
{

  if ((millis() - prevLoopTime) > 40)
  {
    prevLoopTime = millis();
    byte rcSignals[7];
    unsigned int rcN;
    if (rcChange)
    {

      // Data is subject to races if interrupted, so off interrupts
      cli(); // Disable interrupts
      rcN = rcChange;
      rcChange = 0; // Zero the change counter
      rcSignals[0] = mapRC(rcTimes[0]);
      rcSignals[1] = mapRC(rcTimes[1]);
      rcSignals[2] = mapRC(rcTimes[2]);
      rcSignals[3] = mapRC(rcTimes[3]);
      rcSignals[4] = mapRC(rcTimes[4]);
      rcSignals[5] = mapRC(rcTimes[5]);
      // Serial << "t=" << millis() << " " << rcSignals[0] << " " << rcSignals[1]
      //        << " " << rcSignals[2] << " " << rcSignals[3] << " " << rcSignals[4] << " " << rcSignals[5] << " " << rcN;
      sei(); // reenable interrupts
    }

    // Transfer Data
    rcSignals[6] = 200;
    HWSERIAL.write(rcSignals, 7);

    // Read Data
    while (HWSERIAL.available() > 6)
    {
      HWSERIAL.readBytesUntil(200, servoSignal, 8);
    }

    // Serial << "t=" << millis() << " " << servoSignal[0] << " " << servoSignal[1]
    //        << " " << servoSignal[2] << " " << servoSignal[3] << " " << servoSignal[4] << " " << servoSignal[5] << " " << endl;

    // Write to Servos
    if (rcSignals[4] < 90)
    {
      throttleServo.write(rcSignals[0]);
      aileronServo.write(rcSignals[0]);
      elevatorServo.write(rcSignals[0]);
      rudderServo.write(rcSignals[0]);
    }
    else
    {
      throttleServo.write(servoSignal[0]);
      aileronServo.write(servoSignal[1]);
      elevatorServo.write(servoSignal[2]);
      rudderServo.write(servoSignal[3]);
    }
  }
}
