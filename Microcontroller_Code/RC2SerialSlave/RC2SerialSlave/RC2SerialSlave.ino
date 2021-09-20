/*  rcTiming.ino -- JW, 30 November 2015 -- 
 * Uses pin-change interrupts on A0-A4 to time RC pulses
 *
 * Ref: http://arduino.stackexchange.com/questions/18183/read-rc-receiver-channels-using-interrupt-instead-of-pulsein
 *
 */
#include <Streaming.h>
static   byte rcOld;        // Prev. states of inputs
volatile unsigned long rcRises[6]; // times of prev. rising edges
volatile unsigned long rcTimes[6]; // recent pulse lengths
volatile unsigned int  rcChange=0; // Change-counter

int interruptPin0 = A0;
int interruptPin1 = A1;
int interruptPin2 = A2;
int interruptPin3 = A3;
int interruptPin4 = A4;
int interruptPin5 = A5;


// Be sure to call setup_rcTiming() from setup()
void setup_rcTiming() {
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

void rcTiming(){
  byte rcNew = 0b10000000;

  if (digitalRead(interruptPin0)) 
  {
    bitSet(rcNew,0);
  }
  if (digitalRead(interruptPin1)) 
  {
    bitSet(rcNew,1);
  }
  if (digitalRead(interruptPin2)) 
  {
    bitSet(rcNew,2);
  }
  if (digitalRead(interruptPin3)) 
  {
    bitSet(rcNew,3);
  }
  if (digitalRead(interruptPin4)) 
  {
    bitSet(rcNew,4);
  }
  if (digitalRead(interruptPin5)) 
  {
    bitSet(rcNew,5);
  }
  
  byte changes = rcNew^rcOld;   // Notice changed bits
  byte channel = 0;
  unsigned long now = micros(); // micros() is ok in int routine
  while (changes) {
    if ((changes & 1)) {  // Did current channel change?
      if ((rcNew & (1<<channel))) { // Check rising edge
        rcRises[channel] = now;     // Is rising edge
      } else {              // Is falling edge
        rcTimes[channel] = now-rcRises[channel];
      }
    }
    changes >>= 1;      // shift out the done bit
    ++channel;
    ++rcChange;
  }
  rcOld = rcNew;        // Save new state
}


void setup() {
  Serial.begin(115200);
  setup_rcTiming();

}

void loop() {
  unsigned long rcT[6]; // copy of recent pulse lengths
  unsigned int rcN;
  if (rcChange) {

    // Data is subject to races if interrupted, so off interrupts
    cli();          // Disable interrupts
    rcN = rcChange;
    rcChange = 0;       // Zero the change counter
    rcT[0] = rcTimes[0];
    rcT[1] = rcTimes[1];
    rcT[2] = rcTimes[2];
    rcT[3] = rcTimes[3];
    rcT[4] = rcTimes[4];
    rcT[5] = rcTimes[5];
    sei();          // reenable interrupts

    Serial << "t=" << millis() << " " << rcT[0] << " " << rcT[1] << " "
            << rcT[2] << " " << rcT[3] << " " << rcT[4] << " " << rcT[5] << " " << rcN << endl;
  }
  sei();            // reenable interrupts
}
