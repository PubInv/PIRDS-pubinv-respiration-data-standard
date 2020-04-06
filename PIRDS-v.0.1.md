# Public Invention Respiratory Data Standard (PIRDS) (v0.1)

## Event based protocol

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
acceptable range of value. Thus every measurement fits within 9 bytes.

The Types are:

1. T : Temperature in degrees Celsius times 100
2. P : cm H2O (a medical standard) times 100
3. F : slm (liters at 0C per minute) times 1000
4. O : FiO2 (fractional oxygen) times 100 (thus a percentage)
5. H : humidity (% humidity ???) times 100
6. V : Volume in millilieters
7. B : Breaths per minute times 10

The Sensor names roughly corresponed to identifiable locations in the breathing circuit.
We expect this to be extended.

1. A : Airway
1. B : amBient air
1. M : sensors in the Mixer/blender before pressurization
1. D : a pressure Differnce, of unspecified location.

For example, the first 3 sensors in the airway might be named A0, A1, A2. No distinction is made in
the standard for inhalation airway from exhalation standard.

A minial ventilator might provide D0, B0, and A0.

## Assertions

Assertions have the same structure as measurements. The begin with the character "A".
The most important asseritons are:

1. "B" : Type "B" bpm
2. "V" : Type "V", tidal volume in milliters
3. "X" : Maxiumum (peak) pressure
4. "E" : Minimum airway pressure (PEEP)

We have not defined the time period of the these assertions. At present, it is undefined.
It may loosely be construed as "since the last such event reported". (Lauria, should we add a second field
to represent the start of the time period of the asswertion?)

## Meta Events

Meta Events are not measurements but may provide information about measurements. 
The mEta Events begin with character "E". The second character defines the meta
event

1. M : Message : the next byte defines the number of characters following. That
many characters define a string that is an arbitrary message.
1. N : Name event : the same format as a message.
1. D : Device identifier : the same format as a device.
1. C : Clock event : The Clock event is used to tie the relative milliseconds
to an absolute time. The first byte after C is a number n. However, the next
four bytes are an unsigned integer representing milliseconds in this data stream.
After that follows n bytes which of a "time string" that specifies wall-clock time 
in an unspecified format.

# License

Released under a Creative Commons 0 (CC0) Universal License. All rights to the marks "PubInv" and "Public Invention" reserved.

