# PIRDS Class Testing 

This test creates different types of PIRDS events and psrints some of their values to the serial monitor. It is effectively a sandbox for class development. 

## Prerequisites

This example assumes that you are running Python 3 and have installed PySerial.  
For more information on PySerial: https://pyserial.readthedocs.io/en/latest/pyserial.html

You will also need to add this library contianing PIRDSEvent.h and PIRDSEvent.cpp to your Arduino IDE.  
For more information on adding a library: https://www.arduino.cc/en/guide/libraries


## Run the Example

Upload the sketch to your Arduino and launch the serial monitor.

#### PIRDS_ClassTesting.ino

This Arduino sketch creates instances of each type of class and exercises basic methods to check that they're functional. 
