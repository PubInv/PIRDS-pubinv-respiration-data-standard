/* =====================================================================================
 *
 *       Filename:  Measurement_ArduinoToPython.ino
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/07/2020 10:35:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Lauria Clarke (lauriaclarke), lauria.clarke@gmail.com
 *   Organization:  Public Invention
 *
 * =====================================================================================
 */

#include <PIRDS.h>

Measurement m0;

void setup()
{
  Serial.begin(115200);
  Serial.flush();
}

void loop()
{
  // assign values to the measurement fields
  // this represents a temperature measurement from the third ambient sensor
  // the temperature reported is 25C
  m0.measurementType  = 'T';
  m0.deviceType       = 'B';
  m0.deviceLocation   = 2;
  m0.measurementTime  = millis();
  m0.measurementValue = 250;
  
  // print each field of the event to Python
  Serial.println(m0.measurementType, HEX);
  Serial.println(m0.deviceType, HEX);
  Serial.println(m0.deviceLocation, HEX);
  Serial.println(m0.measurementTime, HEX);
  Serial.println(m0.measurementValue, HEX);
  Serial.println(' ');

  // wait 10 seconds
  delay(10000);
}
