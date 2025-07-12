# Auto Nav Bot Project

## Description

The Auto Nav Bot is a self-navigating robot designed to collect data about its environment using various sensors. It is capable of detecting obstacles, measuring gas levels, temperature, and humidity, and can be controlled remotely via Bluetooth.

Project Document: https://docs.google.com/document/d/1uLjSJZGQdncbeZ4jwbA8o4y43IQFU3PijnEI4YkVqd4/edit?usp=sharing 

## Schematic Diagram

<img width="801" height="558" alt="Schematic" src="https://github.com/user-attachments/assets/2b8f8c7b-d128-4acc-aab5-8acaa74c7104" />

## Features

- Obstacle avoidance using an ultrasonic sensor and servo motor
- Gas detection (LPG, CO, Smoke) with an MQ-2 gas sensor
- Temperature and humidity monitoring with a DHT11 sensor
- Remote control via Bluetooth module (HC-05)
- Real-time data display on an LCD screen
- Powered by an Arduino UNO board and L298N motor driver

## Components

- Arduino UNO
- MQ-2 Gas sensor
- DHT11 Temperature & Humidity sensor
- HC-SR04 Ultrasonic Distance sensor
- Servo motor
- L298N motor driver
- 16x2 LCD display with I2C adapter
- HC-05 Bluetooth module
- 9V and 12V batteries
- Robot/Car kit with two motors and a castor wheel

## Setup and Usage

1. Assemble the robot chassis according to the provided instructions.
2. Connect the sensors, motors, and other components to the Arduino UNO board as per the circuit diagram.
3. Upload the Arduino code to the board.
4. Power on the robot using the batteries.
5. Use the Bluetooth module to connect to the robot and control its movements or monitor sensor data.

## Skills Needed

### Programming Skills
- Proficiency in C++ programming language for coding on the Arduino IDE
- Understanding of programming concepts like loops, conditionals, functions, and data structures
- Ability to integrate and interface different sensors and modules with the Arduino

### Electronics and Circuit Design
- Knowledge of basic electronics components like resistors, capacitors, and transistors
- Understanding of circuit design principles and schematics
- Familiarity with breadboard prototyping and soldering techniques

### Mechanical Assembly
- Ability to follow assembly instructions and manuals
- Basic mechanical skills for assembling the robot chassis and mounting components
- Understanding of motor and servo mechanisms

### Bluetooth Communication
- Knowledge of Bluetooth protocols and communication standards
- Experience in configuring and pairing Bluetooth modules
- Ability to develop mobile apps or interfaces for remote control

### Sensor Integration
- Understanding of various sensor types (gas, temperature, humidity, distance)
- Familiarity with sensor datasheets and calibration procedures
- Ability to interpret sensor data and implement data processing algorithms

### Project Management
- Planning and organizing project tasks and timelines
- Documenting the development process and learnings
- Troubleshooting and problem-solving skills

## Acknowledgments

- [Arduino](https://www.arduino.cc/) for the development platform
- [MIT App Inventor](https://appinventor.mit.edu/) for the Bluetooth control app
- [Tinkercad](https://www.tinkercad.com/) for circuit simulations and 3D modeling
