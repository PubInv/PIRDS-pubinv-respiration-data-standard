# Public Invention Respiratory Data Standard (PIRDS) (v0.1)

# Event based protocol

PIRDS data is a series of events. It has no headers, though some events provide meta-information and may be grouped
together to form a header.

We possible, we follow the principle of making data human-readable if possible. In particular, because this
is meant in part for medical professionals, some unit types are chosen to conform that that field.

## Measurement Events

The most common PIRDS data are Measurement events.

Measurements are of fixed length, and consisting the character "M", a measurement type character designator,
a sensor designator consisting of a letter (location) and a nuumber 0-255. 

This is followed by an 32-bit unsigned integers representing milliseconds. In PIRDS data 

Finally, 32-bit signed integer 
is provided. The type of every measurement is multiplied by a decimal to allow an integer to express the 
acceptable range of value. Thus every measurement fits within 8 bytes.

The Types are:

1. T : Temperature in degrees Celsius times 100
2. P : cm H2O (a medical standard) times 100
3. F : slm (liters at 0C per minute) times 1000
4. O : FiO2 (fractional oxygen) times 100 (thus a percentage)
5. H : humidity (% humidity ???) times 100

The Sensor names roughly corresponed to identifiable locations in the breathing circuit.
We expect this to be extended.

1. A : Airway
1. B : amBient air
1. M : sensors in the Mixer/blender before pressurization
1. D : a pressure Differnce, of unspecified location.

For example, the first 3 sensors in the airway might be named A0, A1, A2. No distinction is made in
the standard for inhalation airway from exhalation standard.

A minial ventilator might provide D0, B0, and A0.

## Meta Events





# License

Released under a Creative Commons 0 (CC0) Universal License. All rights to the marks "PubInv" and "Public Invention" reserved.

