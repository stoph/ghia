# Ghia controller
This is the code for automation of my 1961 VW Karmann Ghia convertible using an Arduino ESP32. It adds presence detection when the car is off, and BLE audio control when the car is on.

Future versions will add tachometer and temperature readings of the engine, GPS and telemetry data, and addtional interior and exterior lighting controls.

![Ghia](https://github.christophkhouri.com/ghia/ghia.jpeg?)

## Hardware
Currently I am running an [Adafruit HUZZAH32 – ESP32 Feather Board](https://www.adafruit.com/product/3405) as the main controller. It is mounted inside a gutted Sapphire 1 radio. (**project link coming**). The original volume knob has been replaced by a rotaery encoder and the 5 AM radio preset push buttons have switches installed to use them as digital buttons. There is also a WS2812 LED installed behind the frequency dial to illuminate differetn colors based on different states. (e.g. different colors based on button presses, if the radio is muted, when a device is connected, or presence detection modes). There are also relays installed to control 12v LED strips for the interior, hood, and trunk area.

![Sapphire I Radio](https://github.christophkhouri.com/ghia/sapphite_I_gutted.jpeg?)

Currently I am using a [Xiaomi Mi Band 5](https://amzn.to/3rdBexL) as the BLE trigger. It allows discovery at all times. (Initially I tried the Wyze band, but it disables discovery while connected to a phone)

## Presence
While the car is off, it scans for known bluetooth devices every minute. If a device is found, it simply turns on some interior lights (for now). Once the car is turned on, by sensing a 12v input from the ignition, it disables BLE scanning to dedicate resources to the Audio Control.

## BLE Audio control
While the car is on, the buttons on the radio trigger calls to the connected BLE device to control the audio.
The ESP32 connect as a HID device using the [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) library.

