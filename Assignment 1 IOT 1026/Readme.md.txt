Assignment 1 – Embedded IoT Systems

Name: Fatima Shahzad
Reg No: 23-NTU-CS-1026
Course: Embedded IoT Systems
Instructor: Sir Nasir Mehmood
Date: 26-Oct-2025

Overview

This assignment includes two ESP32-based IoT projects created and tested using the Wokwi Simulator.
Both tasks focus on hardware interfacing, sensor inputs, and visual feedback via an OLED display.

Task 1 – Device Control using ESP32 (LEDs, Buttons, Buzzer & OLED)

Description:
In this project, the ESP32 manages three LEDs, two push buttons, and a buzzer. The OLED screen provides real-time status updates.
Each button press toggles the state of the connected LEDs and buzzer, and the OLED reflects these changes immediately.

Components Used:

ESP32 DevKitC V4

OLED 128x64 (I2C)

3 × LEDs

1 × Buzzer

2 × Push Buttons

3 × 420Ω Resistors

Jumper Wires

Pin Map:

Component	ESP32 Pin Label	GPIO Number
Green Push Button	D4	GPIO 4
Red Push Button	D5	GPIO 5
Buzzer	D18	GPIO 18
Blue LED	D2	GPIO 2
Red LED	D19	GPIO 19
Green LED	D21	GPIO 21
OLED VCC	3V3	—
OLED GND	GND	—
OLED SDA	D22	GPIO 22
OLED SCL	D23	GPIO 23

Wokwi Project Link:
🔗 View Simulation on Wokwi
https://wokwi.com/projects/445804295906521089

Screenshots:
![Task 1 Output]C:\Users\System Administrator\Desktop\Capture.PNG
![Task 1 Wokwi]C:\Users\System Administrator\Desktop\3.PNG

Task 2 – Button Press Duration Detection (Short / Long Press with OLED)

Description:
This project detects and differentiates between short and long button presses.
A short press toggles the LED, while a long press activates the buzzer. The OLED screen displays corresponding feedback messages.

Components Used:

ESP32 DevKitC V4

OLED 128x64 (I2C)

1 × Push Button

1 × LED

1 × Buzzer

1 × Resistor

Pin Map:

Component	ESP32 Pin Label	GPIO Number
Push Button	D4	GPIO 4
Buzzer	D5	GPIO 5
LED	D2	GPIO 2
OLED VCC	3V3	—
OLED GND	GND	—
OLED SDA	D21	GPIO 21
OLED SCL	D22	GPIO 22

Wokwi Project Link:
🔗 View Simulation on Wokwi
https://wokwi.com/projects/445805777808820225

Screenshots:
![Task 2 Output]C:\Users\System Administrator\Desktop\1.PNG
![Task 2 Wokwi]C:\Users\System Administrator\Desktop\2.PNG

loom video link 
![task 1 video ]https://www.loom.com/share/d15538c475034b2191837c0457ebb213
![task 2 video ] https://www.loom.com/share/148360e37c93466dafb91252c138bde7
