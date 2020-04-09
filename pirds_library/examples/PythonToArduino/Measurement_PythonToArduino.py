#! /usr/bin/env python
#################################################################################
#     File Name           :     Measurement_PythonToArduino.py
#     Created By          :     lauriaclarke
#     Creation Date       :     [2020-04-08 09:05]
#     Last Modified       :     [2020-04-09 09:14]
#     Description         :
#################################################################################
import serial
import time
import struct
import sys

# check for input arguments
if len(sys.argv) < 3:
	print("please re-run with the required arguments: python3 [program name] [serial port] [baud rate]\n ")
	sys.exit()

# print input arguments
print("establishing connection on port: ", sys.argv[1])
print("baud rate: ", sys.argv[2], "\n")

arduino = serial.Serial(sys.argv[1], int(sys.argv[2]), timeout=.1)

class Measurement:
  def __init__(self, measurementType, deviceType, deviceLocation, measurementTime, measurementValue):
      self.m                = "M"
      self.measurementType  = measurementType
      self.deviceType       = deviceType
      self.deviceLocation   = deviceLocation
      self.measurementTime  = measurementTime
      self.measurementValue = measurementValue

p1 = Measurement("T", "B", 25, 123456789, 1234567)

print(p1.m, p1.measurementType, p1.deviceType, p1.deviceLocation, p1.measurementTime, p1.measurementValue)

time.sleep(1)
arduino.write(str.encode(p1.m))
arduino.write(str.encode(p1.measurementType))
arduino.write(str.encode(p1.deviceType))
arduino.write(struct.pack('>B', p1.deviceLocation))
arduino.write(struct.pack('>I', p1.measurementTime))
arduino.write(struct.pack('>I', p1.measurementValue))

while True:
	data = arduino.readline()[:-2]
	if data:
		print(data)




