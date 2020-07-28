
#include <PIRDSEvent.h>

// create a one of each class and see if they work
PIRDSEvent event0;
PIRDSEvent event1('p', 123);
Measurement m0;
Assertion a0;
Meta e0;
Meta e1(20);

void setup()
{
  Serial.begin(115200);
  Serial.flush();

  // Set them all to use the Serial port
  // ...could be I2C
  event0.setChannel(&Serial);
  event1.setChannel(&Serial);
  m0.setChannel(&Serial);
  a0.setChannel(&Serial);
  e0.setChannel(&Serial);
  e1.setChannel(&Serial);
}

void loop()
{ 
  // print info from each event type
  event0.sendEvent();
  event1.sendEvent();
  m0.sendEvent();
  a0.sendEvent();
  e0.sendEvent();
  e1.sendEvent();
  Serial.print('\n');
  delay(8000);
}
