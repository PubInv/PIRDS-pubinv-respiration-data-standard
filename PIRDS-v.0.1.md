# Public Invention Respiratory Data Standard (PIRDS) (v0.1)

## Event based protocol

PIRDS data is a series of events. It has no headers, though some events provide meta-information and may be grouped
together to form a header.

We possible, we follow the principle of making data human-readable if possible. In particular, because this
is meant in part for medical professionals, some unit types are chosen to conform that field.

## Measurement Events

The most common PIRDS data are Measurement events.

![MeasurementByteFields](https://github.com/PubInv/respiration-data-standard/blob/master/images/measurement_fields.png)

Measurements are of fixed length, and consisting the character "M", a measurement type character designator,
a sensor designator consisting of a letter (location) and a number 0-255. 

The the byte buffer above, the six fields are positional and don't require names. However, for discussion and in the 
the JavaScript binding, these fields are:

1. event,
1. type,
1. loc (location),
1. num (senosr number in that location),
1. ms (relative millisecond),
1. val (value)

Finally, 32-bit signed integer
is provided. The type of every measurement is multiplied by a decimal to allow an integer to express the
acceptable range of value. Thus every measurement fits within 12 bytes.

Integers are stored in "Big-Endian" byte order within their 4 bytes.

The Types are:

1. T : Temperature in degrees Celsius times 100
2. P : Pressure: cm H2O (a medical standard) times 10
2. D : Differential pressure: cm H2O (a medical standard) times 10 (the same unit, but RELATIVE, not ABSOLUTE)
3. F : Flow slm (liters at 0C per minute) times 1000
4. O : FO2 (fractional oxygen) times 100 (thus a percentage)
5. H : humidity (% humidity ???) times 100
6. V : Volume in millilieters
7. B : Breaths per minute times 10
8. G : Gas resitance (ohms) used to check for volatile compounds
8. A : Altitude in meters (used as a check of the system)
9. C : Carbon dioxide concentration in tenths of mmHg 

The Sensor names roughly corresponded to identifiable locations in the breathing circuit.
We expect this to be extended.

1. A : Airway
1. B : amBient air
1. M : sensors in the Mixer/blender before pressurization
1. D : a pressure Difference, of unspecified location.
1. I : Inspiratory manifold
1. E : Expiratory manifold

For example, the first 3 sensors in the airway might be named A0, A1, A2. Typically `Airway` sensors
will be located within at the Y connector closest to the patient, but the `Inspiratory` and `Expriratory`
sensors will be mounted within the ventilator's enclosure. Pressure at all three locations would generally
be almost identical, however both gas analysis and flow patterns will be completely different at the three
locations. 

A minimal ventilator might provide D0, B0, and A0.


### Sample Measurement

The following measurement is a temperature measurement (B1: ‘T’) from the third (B3: 2) device in the ambient air (B2: ‘B’). The measurement occurred at 35ms (B4 - B7: 0035) and has a value of 25 degrees C (B9 - B11: 0250).

![SampleMeasurement](https://github.com/PubInv/respiration-data-standard/blob/master/images/sample_measurement.png)

Hex Equivalent: 4D54 4202 0023 00FA


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
event. Then the "ms" milliseconds unsigned 4 bytes fallows.

1. M : Message : the next byte (b_size) defines the number of characters following. That
many characters (buff) define a string that is an arbitrary message.
1. N : Name event : the same format as a message.
1. D : Device identifier : the same format as a device.

### The Clock Event
1. C : Clock event : The Clock event is used to tie the relative milliseconds
to an absolute time. The first byte after C is a number n. However, the next
four bytes are an unsigned integer representing milliseconds in this data stream.
After that follows n bytes which of a "time string" that specifies wall-clock time
[UTC](https://en.wikipedia.org/wiki/Coordinated_Universal_Time) time in the [ISO 8601](https://en.wikipedia.org/wiki/ISO_8601) format.
An example of this format is:
```JavaScript
{ "event": "E", "type": "C", "ms": 10443, "buff": "Sun Jul 26 22:19:10 2020" },
```

Note: In the C Language, we use the following code snippet to generate this human-readable time stream in UTC/Zulu Time/GMT. By always
using UTC, we remove some geographic timezone complexity.

```C
   char iso_time_string[256];
   time_t now;
   struct tm *ptm = gmtime(&now);
   sprintf(iso_time_string,"%s", asctime(ptm));
```

# JSON Expression

Although driven by a need for a byte-level protocol to communicate electronically, there is
also need for a JSON-level expression of the standard. The obvious approach is to define
and event as a JSON object. We hope to make it somewhat human readable, but maintain a
direct connection to the Byte Level expression of the PIRDS standard.

Our expression will use JSON objects with slightly more information names. The charcter
codes will be used as is. The time in milliseconds. For now the values will use the same
scale as defined in the byte level specifcations. This means that no floating point number will
at present ever appear in a value field.

So for example, measurement of 25C from sensor #2 in the ambient air would look  like:

```JavaScript
{ "event" : "M",
  "type" : "T",
  "loc" : "B",
  "num" : 2,
  "ms" : 35,
  "val" : 250
  }
```

# License

Released under a Creative Commons 0 (CC0) Universal License. All rights to the marks "PubInv" and "Public Invention" reserved.
