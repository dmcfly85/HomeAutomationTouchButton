# HomeAutomationTouchButton

"Internet buttons" for a home automation project running on https://home-assistant.io

Two capacitive sensors when touched hit the home-assistant.io api to trigger an event

####Hardware
- Arduino YUN
- For the capacitive sensors I used a set of chinese baoding balls and two glass votives. 

####Circuit
- Cap Sensor 1: Pins 2 and 4*
- Cap Sensor 2: Pins 6 and 13*
- LED Green: Pin 11 >> 220 ohm resistor >> GND
- LED White: Pin 10 >> 220 ohm resistor >> GND
- LED Red: Pin 9 >> 220 ohm resistor >> GND

(*for capacity sensor wiring diagram see http://playground.arduino.cc/Main/CapacitiveSensor?from=Main.CapSense)
