# Arduino-GSM-Car-Control
Arduino project for controlling a car using GSM and Bluetooth. This project involves interfacing Arduino with SIM800L GSM module and L298N motor driver for remote control via SMS and Bluetooth commands. The car's movements (forward, backward, left, right) can be controlled using a mobile phone via SMS or a Bluetooth-enabled device.

# Arduino GSM Bluetooth Car Control

This Arduino project enables remote control of a car using a SIM800L GSM module and Bluetooth. The project involves interfacing Arduino with the SIM800L GSM module and L298N motor driver to control the car's movements via SMS and Bluetooth commands.

## Features

- Control the car's movements (forward, backward, left, right) via SMS commands.
- Adjust the speed of the DC motors using Bluetooth communication.
- Voice control functionality using DTMF tones over GSM.

## Components

- Arduino board
- SIM800L GSM module
- L298N motor driver
- Bluetooth module
- DC motors
- Ultrasonic sensor for obstacle detection

## Setup

1. Connect the hardware components as per the circuit diagram.
2. Upload the Arduino code to your Arduino board.
3. Power up the Arduino and GSM module.
4. Control the car using SMS commands or Bluetooth communication.

## SMS Commands

- Send '1' to increase motor speed.
- Send '2' to move the car forward.
- Send '3' to slow down the motor.
- Send '4' to turn the car left.
- Send '5' to stop the car.

## Bluetooth Commands

Adjust the speed of the DC motors using the Bluetooth module.

## Voice Control

The project supports voice control using DTMF tones. Make a call to the SIM800L GSM module and use DTMF tones to control the car.

Feel free to contribute and enhance the project!
