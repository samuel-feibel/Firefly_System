#ifndef RCTIMING_H
#define RCTIMING_H

// Setup RC Timing ISR
bool setup_rcTiming();

// Get most recent RC Signal
void getRCSignalPWM(unsigned long *rcT);

#endif