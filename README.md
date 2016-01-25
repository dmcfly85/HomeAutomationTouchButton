# HomeAutomationTouchButton

"Internet buttons" for a home automation project running on https://home-assistant.io

Two capicty sensors when touched hit the home-assistant.io api to trigger an event

####Hardware
Arduino YUN

####Circuit
- Cap Sensor 1: Pins 2 and 4*
- Cap Sensor 1: Pins 6 and 13*
- LED Green: Pin 11 >> 220 ohm resistor >> GND
- LED White: Pin 10 >> 220 ohm resistor >> GND
- LED Red: Pin 9 >> 220 ohm resistor >> GND

(*for capacity sensor wiring diagram see http://playground.arduino.cc/Main/CapacitiveSensor?from=Main.CapSense)
