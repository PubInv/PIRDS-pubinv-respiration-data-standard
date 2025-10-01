# Public Invention Respiratory Data Standard (PIRDS) (v0.3)

## Event Based Protocol

PIRDS data is a series of events. It has no headers, though some events provide meta-information and may group
together to form a header.

When  possible, we follow the principle of making data that is human-readable. In support of this aim, this data standard uses many unit types with which medical professionals, our largest projected user base, would be familiar. 

## Measurement Events

The most common PIRDS data are Measurement Events.

![MeasurementByteFields](https://github.com/PubInv/respiration-data-standard/blob/master/images/measurement_fields.png)

Measurements are of fixed length and consist of multiple parts, including the character "M", a measurement type character designator, a sensor designator consisting of a letter (location), and a number like 0-255. The Measurement is terminated with a CRLF pair, (0x0D 0x0A) including characters not explicitly represented in these examples.

In the byte buffer above, the six fields are positional and don't require names. However, for our discussion and in
the JavaScript binding, these fields are:

1. event
2. type
3. loc (location)
4. num (sensor number in that location)
5. ms (relative millisecond)
6. val (value)

Finally, the PIRDS data provides a 32-bit signed integer, and multiplie the Type of every measurement by a decimal to allow an integer to express an
acceptable range of values. Thus, every measurement fits within 12 bytes.

Integers are stored in "Big-Endian" byte order within their 4 bytes.

The Types are:

1. T : Temperature in degrees Celsius times 100
2. P : Pressure: cm H2O (a medical standard) times 10
2. D : Differential pressure: cm H2O (a medical standard) times 10 (the same unit, but RELATIVE or GAUGE pressure, not ABSOLUTE)
3. F : Flow slm (liters at 0C per minute) times 1000
4. O : FO2 (fractional oxygen) times 100 (thus a percentage)
5. H : humidity (% humidity ???) times 100
6. V : Volume in milliliters
7. B : Breaths per minute times 10
8. G : Gas resitance (ohms) used to check for volatile compounds
8. A : Altitude in meters (used as a check of the system)
9. C : Carbon dioxide partial pressure in tenths of mmHg

The Sensor names roughly corresponded to identifiable locations in the breathing circuit.
We expect this to be extended into:

1. A : Airway
2. B : amBient air
3. M : sensors in the Mixer/blender before pressurization
4. D : a pressure Difference, of unspecified location.
5. I : Inspiratory manifold
6. E : Expiratory manifold

For example, the first 3 sensors in the airway might be named A0, A1, or A2. Typically `Airway` sensors
are located within the Y connector closest to the patient, but the `Inspiratory` and `Expiratory`
sensors will be mounted within the ventilator's enclosure. Pressure at all three locations would generally
be almost identical. However, both gas analysis and flow patterns will be completely different at the three
locations.

A minimal ventilator might provide D0, B0, and A0.


### Sample Measurement

The following measurement is a temperature measurement (B1: ‘T’) from the third (B3: 2) device in the ambient air (B2: ‘B’). The measurement occurred at 35ms (B4 - B7: 0035) and has a value of 25 degrees C (B9 - B11: 0250).

![SampleMeasurement](https://github.com/PubInv/respiration-data-standard/blob/master/images/sample_measurement.png)

Hex Equivalent: 4D 54 42 32 30 30 33 35 30 32 35 30


## Assertions

Assertions have the same structure as measurements. They begin with the character "A".
The most important assertions are:

1. "B" : Type "B" bpm
2. "V" : Type "V", tidal volume in milliliters
3. "X" : Maxiumum (peak) pressure
4. "E" : Minimum airway pressure (PEEP)

We have not defined the time period of these assertions. At present, it is undefined.
We may loosely construe it as "since the last such event reported". <!-- Lauria, should we add a second field
to represent the start of the time period of the assertion? -->

## Meta Events

Meta Events are not measurements but may provide information about measurements. The Meta Events begin with the character "E". The second character defines the Meta Event. Then the "ms" milliseconds unsigned 4 bytes follow.

1. M : Message : the next byte (b_size) defines the number of characters following. That
many characters (buff) define a string that is an arbitrary message.
2. N : Name event : the same format as a message.
3. D : Device identifier : the same format as a device.

### The Clock Event
1. C : Clock event : The Clock event is used to tie the relative milliseconds
to an absolute time. The first byte after C is a number n. However, the next
four bytes are an unsigned integer representing milliseconds in this data stream.
After that follows n bytes, which relate to a "time string" that specifies wall-clock time
[UTC](https://en.wikipedia.org/wiki/Coordinated_Universal_Time) in the [ISO 8601](https://en.wikipedia.org/wiki/ISO_8601) format.
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
also a need for a JSON-level expression of this standard. The obvious approach is to define
an event as a JSON object. We hope to make it somewhat human readable, while maintaining
direct connection to the Byte Level expression of the PIRDS standard.

Our expression will use JSON objects with slightly more informative names. The character
codes will remain the same, including their various timing in milliseconds. For now the values will use the same
scale as defined in the byte level specifications. This means that no floating point number will ever appear in a value field.

For example, the measurement of 25C from sensor #2 in ambient air would look like:

```JavaScript
{ "event" : "M",
  "type" : "T",
  "loc" : "B",
  "num" : 2,
  "ms" : 35,
  "val" : 250
  }
```

# Patient-Identifying Extension to the JSON Binding

On Sept. 25th, 2021, we extended the sibling PIRCS specification to allow the specification
of a patient identifying a 40-character string and a 32-bit unsigned integer "shorthand".
This would allow data from multiple patients to be collected from the same source and uniquely disambiguated. 
(We use IP
addresses as disambiguators of data streams in our logger, but we may not always have
separate, distinct IP addresses.)

In order to accomodate this, the PIRDS data standard adds new fields, respectively called "sht" (for "shorthand")
and "pid" (for "patient id"). Each of these fields
may or may not be present in a PIRDS message. It may look like this:

```JavaScript
{ "event" : "M",
  "type" : "T",
  "loc" : "B",
  "num" : 2,
  "ms" : 35,
  "val" : 250
  "sht" : 6754328
  "pid" : "834f44a2-4bf3-40ba-827b-ba2a8cc59531"
  }
```
Which means that patient number 6754328 experienced A pressure of 25 cm at 35 ms. This message would pass smoothly into the data stream.

However, this part of the standard is not currently implemented in the C library,
which implements the rest of the standard (found in this repo).


# License

Released under a Creative Commons 0 (CC0) Universal License. All rights to the marks "PubInv" and "Public Invention" reserved.
