/* RC Aircraft Autopilot
 * Written by Samuel Feibel
 *
 * TODO:
 * - Check all units and constants for errors
 * - figure out source of explosion at higher frequencies
*/

// Includes
#include <main.h>

plane myPlane;


void setup()
{
  myPlane.setup();
}

void loop()
{
  myPlane.loop();
}