# Raspberry Pi Pico, URF and a Buzzer

## Program

The board used here is programmed using the C/C++ SDK. It is programmed to emit
a beep at regular intervals if an object is under 30cms of distance, two beeps
if under 25cm and a long beep if under 20cms. The strength of the signal is
dependent on the strength of the power source. 

## Components

1. Raspberry Pi Pico
2. Active Piezo Buzzer.
3. Ultra-Sonic Range Finder (HC-SR04)
4. ~500Ω Resistor
5. NPN Transistor

## Power Supply

In this configuration, a total of 10.5 volts was provided to the
buzzer by connecting VBUS (5V) of the microcontroller in series with the bench
power supply of 5.5V. For this reason, a transistor was connected to act as a
switch for the supply to the buzzer.

[**Connection Diagram**](./urf-buzzer.png)

[**Demo Video**](https://youtu.be/e0GNt2fwnB4)
