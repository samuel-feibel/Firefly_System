#include <Arduino.h>
#include <servos.h>

// https://arduino.stackexchange.com/questions/18183/read-rc-receiver-channels-using-interrupt-instead-of-pulsein

static byte rcOld;                  // Prev. states of inputs
volatile unsigned long rcRises[6];  // times of prev. rising edges
volatile unsigned long rcTimes[6];  // recent pulse lengths
volatile unsigned int rcChange = 0; // Change-counter
volatile unsigned long lastTime = 0;

// Be sure to call setup_rcTiming() from setup()
void setup_rcTiming()
{
  rcOld = 0;
  pinMode(A8, INPUT); // pin 14, A0, PC0, for pin-change interrupt
  pinMode(A9, INPUT); // pin 15, A1, PC1, for pin-change interrupt
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);
  pinMode(A13, INPUT);
  PCMSK2 |= 0x3F; // 0x0F // Four-bit mask for four channels
  PCIFR |= 0x04;  // clear pin-change interrupts if any
  PCICR |= 0x04;  // enable pin-change interrupts
}
// Define the service routine for PCI vector 1
ISR(PCINT2_vect)
{
  byte rcNew = PINK & 63;       //15;   // Get low 4 bits, A0-A3
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

  // Write to Servos if in Manual Mode
  if (rcOld == 0)
  {
    if (rcTimes[4] < 1700)
    {
      writeServosPWM(&rcTimes[0]);
      // Serial.println(millis()-lastTime);

    }
  }
}

void getRCSignalPWM(unsigned long *rcT)
{
  //unsigned long rcT[4]; // copy of recent pulse lengths
  unsigned int rcN;
  if (rcChange)
  {

    // Data is subject to races if interrupted, so off interrupts
    cli(); // Disable interrupts
    rcN = rcChange;
    rcChange = 0; // Zero the change counter

    rcT[0] = rcTimes[0]; // Throttle
    rcT[1] = rcTimes[1]; // Elevator
    rcT[2] = rcTimes[2]; // Aileron
    rcT[3] = rcTimes[3]; // Rudder
    rcT[4] = rcTimes[4]; // Auto
    rcT[5] = rcTimes[5]; // Aux
    sei();               // reenable interrupts
  }
  sei(); // reenable interrupts
  //return rcT;
}

