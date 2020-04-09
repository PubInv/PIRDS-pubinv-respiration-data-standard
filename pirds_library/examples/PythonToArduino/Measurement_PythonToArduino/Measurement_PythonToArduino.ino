/* =====================================================================================
 *
 *       Filename:  Measurement_PythonToArduino.ino
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/08/2020 10:35:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Lauria Clarke (lauriaclarke), lauria.clarke@gmail.com
 *   Organization:  Public Invention
 *
 * =====================================================================================
 */


#include <PIRDS.h>


// shoud eventually be in a class
Measurement readMeasurement();
void printMeasurement();


Measurement m0;
void setup()
{
  Serial.begin(115200);
}

void loop()
{
  if (Serial.available() > 0)
  {
    char data = Serial.read();
    switch (data)
    {
      // measurement event
      case 'M':
        m0 = readMeasurement();
        printMeasurement(m0);
        break;

      // meta event
      case 'E':
        // readMeta();
        Serial.println("META");
        break;

      // assertion event
      case 'A':
        // readAssertion();
        Serial.println("ASSERTION");
        break;
    }
  }


}

void printMeasurement(Measurement m)
{
  Serial.println("MEASUREMENT");
  Serial.println(m.measurementType);
  Serial.println(m.deviceType);
  Serial.println(m.deviceLocation);
  Serial.println(m.measurementTime);
  Serial.println(m.measurementValue);
}


Measurement readMeasurement()
{
  Measurement m;

  char measurementType[1];
  Serial.readBytes(measurementType, 1);
  m.measurementType = measurementType[0];

  char deviceType[1];
  Serial.readBytes(deviceType, 1);
  m.deviceType = deviceType[0];

  byte deviceLocation[1];
  Serial.readBytes(deviceLocation, 1);
  m.deviceLocation = deviceLocation[0];

  byte measurementTime[4];
  Serial.readBytes(measurementTime, 4);
  // place bytes into struct
  long tempTime;
  for (int i = 0; i < 4; i++)
  {
    tempTime = tempTime | ((long)measurementTime[3 - i] << 8UL * i) & (0xFFUL << 8UL * i);
  }
  m.measurementTime = tempTime;

  byte measurementValue[4];
  Serial.readBytes(measurementValue, 4);
  // place bytes into struct
  long tempValue;
  for (int i = 0; i < 4; i++)
  {
    tempValue = tempValue | ((long)measurementValue[3 - i] << 8UL * i) & (0xFFUL << 8UL * i);
  }
  m.measurementValue = tempValue;

  return m;
}
