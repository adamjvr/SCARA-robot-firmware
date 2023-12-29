/*
MIT License

Copyright (c) 2023 Adam Vadala-Roth

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <AccelStepper.h>
#include <Servo.h>
#include <math.h>
#include "LS7366R_arduino.h"
#include "actuator.h"
#include "SCARA_KINEMATICS.h"

// Chip Select Pins for LS7366R SPI encoder counter chip 
#define LS7366R_Z_CS_PIN 10 
#define LS7366R_J1_CS_PIN 11
#define LS7366R_J2_CS_PIN 12
#define LS7366R_J3_CS_PIN 13
// SPI Port For Encoder Counter Chips 
#define LS7366R_SPI_PORT SPI 

/*
LS7366R encoder_Z(LS7366R_Z_CS_PIN, LS7366R_SPI_PORT);
LS7366R encoder_J1(LS7366R_J1_CS_PIN, LS7366R_SPI_PORT);
LS7366R encoder_J2(LS7366R_J2_CS_PIN, LS7366R_SPI_PORT);
LS7366R encoder_J3(LS7366R_J3_CS_PIN, LS7366R_SPI_PORT);

// Define the stepper motors and the pins the will use (Type:driver, STEP, DIR)
AccelStepper stepper_Z(1, 2, 5);
AccelStepper stepper_J1(1, 3, 6); 
AccelStepper stepper_J2(1, 4, 7);
AccelStepper stepper_J3(1, 12, 13);
*/



// Define Servo(s) for end effector/toolhead
Servo gripper;

void setup() {
  // put your setup code here, to run once:
  stepper_Z.setMaxSpeed(4000);
  stepper_Z.setAcceleration(2000);
  stepper_J1.setMaxSpeed(4000);
  stepper_J1.setAcceleration(2000);
  stepper_J2.setMaxSpeed(4000);
  stepper_J2.setAcceleration(2000);
  stepper_J3.setMaxSpeed(4000);
  stepper_J3.setAcceleration(2000);

}

void loop() {
  // put your main code here, to run repeatedly:

}
