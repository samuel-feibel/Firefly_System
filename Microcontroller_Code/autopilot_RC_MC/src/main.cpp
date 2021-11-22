/*  rcTiming.ino -- JW, 30 November 2015 -- 
 * Uses pin-change interrupts on A0-A4 to time RC pulses
 *
 * Ref: http://arduino.stackexchange.com/questions/18183/read-rc-receiver-channels-using-interrupt-instead-of-pulsein
 *
 */

#include <Arduino.h>
#define HWSERIAL Serial1


#include <Streaming.h>
static byte rcOld;                  // Prev. states of inputs
volatile unsigned long rcRises[6];  // times of prev. rising edges
volatile unsigned long rcTimes[6];  // recent pulse lengths
volatile unsigned int rcChange = 0; // Change-counter

int interruptPin0 = A0;
int interruptPin1 = A1;
int interruptPin2 = A2;
int interruptPin3 = A3;
int interruptPin4 = A4;
int interruptPin5 = A5;

unsigned long prevLoopTime;

void rcTiming()
{
  byte rcNew = 0b10000000;

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

  prevLoopTime = millis();
}

int mapRC(unsigned long rcTime)
{
  return 180 * ((rcTime - 1100.0)/(1900 - 1100));
}

void loop()
{

  if ((millis() - prevLoopTime) > 20)
  {
    prevLoopTime = millis();
    
    // unsigned int rcN;
    // if (rcChange)
    // {

    //   // Data is subject to races if interrupted, so off interrupts
    //   cli(); // Disable interrupts
    //   rcN = rcChange;
    //   rcChange = 0; // Zero the change counter
    //   rcSignals[0] = mapRC(rcTimes[0]);
    //   rcSignals[1] = mapRC(rcTimes[1]);
    //   rcSignals[2] = mapRC(rcTimes[2]);
    //   rcSignals[3] = mapRC(rcTimes[3]);
    //   rcSignals[4] = mapRC(rcTimes[4]);
    //   rcSignals[5] = mapRC(rcTimes[5]);
    //   sei(); // reenable interrupts

    //   // Serial << "t=" << millis() << " " << rcT[0] << " " << rcT[1] << " "
    //   //        << rcT[2] << " " << rcT[3] << " " << rcT[4] << " " << rcT[5] << " " << rcN << endl;
    // }
    
    
    // Transfer Data
    // int value=1234; //this would be much more exciting if it was a sensor value
    // itoa(value, str, 10); //Turn value into a character array

    // byte rcSignals[6] = {mapRC(1200),2,3,4,5,6};
      byte rcSignals[7]; 
      // char str[2];
      // itoa(mapRC(1300),str,10);
      rcSignals[0] = mapRC(1200);
      rcSignals[1] = mapRC(1300);
      rcSignals[2] = mapRC(1400);
      rcSignals[3] = mapRC(1500);
      rcSignals[4] = mapRC(1600);
      rcSignals[5] = mapRC(1700);
      rcSignals[6] = 200;
      // Serial.println(rcSignals[0]);
    HWSERIAL.write(rcSignals, 7);
  }
}

