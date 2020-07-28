#! /usr/bin/env python
#################################################################################
#     File Name           :     Measurement_ArduinoToPython.py
#     Created By          :     lauriaclarke
#     Creation Date       :     [2020-04-07 16:58]
#     Last Modified       :     [2020-04-09 09:15]
#     Description         :
#################################################################################

import serial
import sys

# check for input arguments
if len(sys.argv) < 3:
	print("please re-run with the required arguments: python3 [program name] [serial port] [baud rate]\n ")
	sys.exit()

# print input arguments
print("establishing connection on port: ", sys.argv[1])
print("baud rate: ", sys.argv[2], "\n")

# establish serial connection
arduino = serial.Serial(sys.argv[1], int(sys.argv[2]), timeout=.1)

# echo data from Arduino
while True:
	data = arduino.readline()[:-2]
	if data:
		print(data)
