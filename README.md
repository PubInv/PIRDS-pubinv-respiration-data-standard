# Public Invention Respiration Data Standard
[Public Invention Respiration Data Standard (PIRDS) v0.1](https://github.com/PubInv/respiration-data-standard/blob/master/PIRDS-v.0.1.md) -- A standard for COVID-19 pandemic ventilator data exchange.

This is a sister to the [Public Invention Respiration Control Standard (PIRCS)](https://github.com/PubInv/pubinv-respiration-control-standard).

# Rationale

The open source, free software, and humanitarian engineering communities are attempting to address the COVID-19 pandemic.
Part of this effort is attempts to address and [urgent shortfall of ventilators](https://github.com/PubInv/covid19-vent-list). In order to be safely deployed,
rapidly manufactured ventilators require extensive testing. In order to be tested communaly with modular
tools, a data interchange format is required.

There exists standards for waveform data, such those of [Physionet](https://physionet.org/content/bidmc/1.0.0/).
We know of no format specific enough to respiratory data that meets our needs; but our time to research
has been limited.

# Three Expressions of the Standard

JSON is a convenient format for interchange of respiration data over the internet and between teams.
Our own test effort, [VentMon](https://github.com/PubInv/ventmon-ventilator-inline-test-monitor), requires a format for transfer between data servers and web pages for data analysis.
A byte-level protocol is convenient for electronic transfer between microcomponents and microcontrollers
in a working ventilator. In fact, we think of the problem not so much as that of ventilators but
modular ventilation systems. A byte-level protocol may support I2C and serial port interfaces.

We therefore intend to define an abstract standard, which has both a JavaScript and byte-level expression.

# The C Binding/Library of the PIRDS Standard

In order to make this standard more usable, we have produced a C-language library that offers
convenient functions to move to and from a byte-buffers, C structures, and string in the JSON format.
This library code is released under the MIT License (the standard itself is relaesed under CC0).

This code exists in the "pirds_library" directory. It has a small unit test file test_PIRDS/test_PIRD.c.
This file is a useful example on how to use the library, as well as a test for future develepmonet.

Originally, we mixed "transport protocol" into this library, but have removed it. The library moves to
and from byte buffer representations conformant to the standard; these buffers (or JSON) can be transported
or stored any way you want (I2C, SPI, UDP, TCP, file, etc.)

At present we use the library in two places which are important (to us.)
The [VentMon](https://github.com/PubInv/ventmon-ventilator-inline-test-monitor) uses the
PIRDS libary to output both JSON on the serial port and byte-level PIRDS data via UDP
to a "data lake" where it can be rendered with breath_plot.html. This code runs on an ESP32,
but probably runs on any Arduino-family MCU.
This PIRDS data is "unpacked" via ["pirds_logger"](https://github.com/PubInv/PIRDS-logger), which also uses "pirds_library".

For this reason, the main PIRDS code (which is very short) is named "PIRDS.cpp", even thought it
a C file, not a C++ file. This format allows "pirds_library" to be installed as an Arduino library,
so that you can hack the VentMonFirmware code if needed. In order to use this library in
the [PIRDS-logger](https://github.com/PubInv/PIRDS-logger), we explictly place the .h and .o
file in the PIRDS-logger as PIRDS-1-1.h and PIRDS-1-1.o.  However, if you are modifying these
files, you may have to compile these yourself.

We hope this would allow a new instrument to produces PIRDS data events. For example, if someone
made a CO2 sensor for capnograpy of the respiration exhalation limb, the could use these libraries
in their firmware to to produce PIRDS data that could be rendered with a (modified) version of
[breath_plot.html](https://github.com/PubInv/ventmon-ventilator-inline-test-monitor/blob/master/test_tools/breath_plot.html).


# License

The file is released under CC0, but names resembling "PubInv Respiration Data Standard" may not be used without the permission
of Public Invention. You are welcome to extend the standard; if you do, please submit your improves back to us.
However, to avoid confusion (standards must be standards) do not use the name "PubInv" or "Public Invention", which
are trademarks for Public Invention, a US 501(c)3 public charity, on any
derivative work.
