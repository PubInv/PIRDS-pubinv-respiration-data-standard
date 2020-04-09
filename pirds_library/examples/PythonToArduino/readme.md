# Measurement Event Test No. 2 - Python to Arduino

This is an extremely basic example of sending a measurement event from a Python script to Arduino and back again over the serial port.

There is no event handling, or processing on either end. This is simply to test basic functionality of the connection and the data structure. 

## Prerequisites

This example assumes that you are running Python 3 and have installed PySerial.  
For more information on PySerial: https://pyserial.readthedocs.io/en/latest/pyserial.html

You will also need to add this library contianing PIRDS.h to your Arduino IDE.  
For more information on adding a library: https://www.arduino.cc/en/guide/libraries


## Run the Example

First upload the Arduino sketch to your Arduino. Then launch the Python script. You should see the Measurement data printed and then echoed back in your terminal. 

#### Measurement_PythonToArduino.ino

This Arduino sketch places the data received from Python into a Measurement struct and then sends it back to the Python script.

#### Measurement_PythonToArduino.py

This Python program sends a measurement event over the serial port to an Arduino and then prints the data sent back from the Arduino. 

To run:
> python3 Measurement_PythonToArduino.py [serial port] [baud rate]



***Disclaimer: This code is the most basic implementation of a more complex standard and WILL change.*** 
