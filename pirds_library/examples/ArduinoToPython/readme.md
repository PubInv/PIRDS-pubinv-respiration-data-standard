# Measurement Event Test No. 1 - Arduino to Python

This is an extremely basic example of sending a measurement event from an Arduino to a Python script over the serial port.

There is no event handling, or processing on either end. This is simply to test basic functionality of the connection and the data structure. 

## Prerequisites

This example assumes that you are running Python 3 and have installed PySerial.  
For more information on PySerial: https://pyserial.readthedocs.io/en/latest/pyserial.html

You will also need to add this library contianing PIRDS.h to your Arduino IDE.  
For more information on adding a library: https://www.arduino.cc/en/guide/libraries


## Run the Example

First upload the Arduino sketch to your arduino. Then launch the pythin script. You should see the Measurement data echoed back in your terminal. 

#### Measurement_ArduinoToPython.ino

This Arduino sketch places fake measurement data into a the PIRDS mearusment format and sends it over a serial connection to a Python script. It's very simple. 


#### Measurement_ArduinoToPython.py

This Python program prints serial output coming from the Arduino.

To run:
> python3 Measurement_ArduinoToPython.py [serial port] [baud rate]



***Disclaimer: This code is the most basic implementation of a more complex standard and WILL change.*** 
