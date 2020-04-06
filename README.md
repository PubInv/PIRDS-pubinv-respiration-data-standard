# respiration-data-standard
[PubInv Respiration Data Standard (PIRDS) v0.1](https://github.com/PubInv/respiration-data-standard/blob/master/PIRDS-v.0.1.md) -- A standard for COVID-19 pandemic ventilator data exchange.

# Rationale

The open source, free software, and humanitarian engineering communities are attempting to address the COVID-19 pandemic.
Part of this effort is attempts to address and [urgent shortfall of ventilators](https://github.com/PubInv/covid19-vent-list). In order to be safely deployed,
rapidly manufactured ventilators require extensive testing. In order to be tested communaly with modular 
tools, a data interchange format is required.

There exists standards for waveform data, such those of [Physionet](https://physionet.org/content/bidmc/1.0.0/).
We know of know format specific enough to respiratory data that meets our needs; but our time to research
has been limited.

# Three Expressions of the Standard

JSON is a convenient format for interchange of respiration data over the internet and between teams.
Our own test effort, [VentMon](https://github.com/PubInv/ventmon-ventilator-inline-test-monitor), requires a format for transfer between data servers and web pages for data analysis.
A byte-level protocol is convenient for electronic transfer between microcomponents and microcontrollers 
in a working ventilator. In fact, we think of the problem not so much as that of ventilators but 
modular ventilation systems. A byte-level protocol may support I2C and serial port interfaces.

We therefore intend to define an abstract standard, which has both a JavaScript and byte-level expression.

# Testing in the repo

In order to provide very basic testing of the PIRDS, we will create create Python program and C program on the 
Arduino platform. The Python program will generate mock data and convert it to the byte-level version and send
it to the Arduino via PySerial. The Arduino program will interpret the standard and echo it back to 
the Python program in the JavaScript format. The Python program will then check abstractly that it has received
what it sent in a round trip.

# License

The file is released under CC0, but names resembling "PubInv Respiration Data Standard" may not be used without the permission
of Public Invention. You are welcome to extend the standard; if you do, please submit your improves back to us.
However, to avoid confusion (standards must be standards) do not use the name "PubInv" or "Public Invention", which
are trademarks for Public Invention, a US 501(c)3 public charity, on any
derivative work.
