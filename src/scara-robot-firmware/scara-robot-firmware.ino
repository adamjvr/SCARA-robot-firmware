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

// Define LS7366R and SPI configuration
#define LS7366R_CS_PIN_Z 10
#define LS7366R_CS_PIN_J1 11
#define LS7366R_CS_PIN_J2 12
#define LS7366R_CS_PIN_J3 13
// SPI Port For Encoder Counter Chips 
#define LS7366R_SPI_PORT SPI

// Define Stepper motor connections
#define STEPPER_STEP_PIN_Z 2
#define STEPPER_DIR_PIN_Z 3
#define STEPPER_ENABLE_PIN_Z 4
#define LIMIT_SWITCH_PIN_Z 5

#define STEPPER_STEP_PIN_J1 6
#define STEPPER_DIR_PIN_J1 7
#define STEPPER_ENABLE_PIN_J1 8
#define LIMIT_SWITCH_PIN_J1 9

#define STEPPER_STEP_PIN_J2 A0
#define STEPPER_DIR_PIN_J2 A1
#define STEPPER_ENABLE_PIN_J2 A2
#define LIMIT_SWITCH_PIN_J2 A3

#define STEPPER_STEP_PIN_J3 A4
#define STEPPER_DIR_PIN_J3 A5
#define STEPPER_ENABLE_PIN_J3 2
#define LIMIT_SWITCH_PIN_J3 3
// Number of joints in the SCARA Robot
#define NUM_JOINTS 4

// Create an array of Actuator objects
Actuator SCARA_robot[NUM_JOINTS] = {
  Actuator(LS7366R_CS_PIN_Z, LS7366R_SPI_PORT, STEPPER_STEP_PIN_Z, STEPPER_DIR_PIN_Z, LIMIT_SWITCH_PIN_Z),
  Actuator(LS7366R_CS_PIN_J1, LS7366R_SPI_PORT, STEPPER_STEP_PIN_J1, STEPPER_DIR_PIN_J1, LIMIT_SWITCH_PIN_J1),
  Actuator(LS7366R_CS_PIN_J2, LS7366R_SPI_PORT, STEPPER_STEP_PIN_J2, STEPPER_DIR_PIN_J2, LIMIT_SWITCH_PIN_J2),
  Actuator(LS7366R_CS_PIN_J3, LS7366R_SPI_PORT, STEPPER_STEP_PIN_J3, STEPPER_DIR_PIN_J3, LIMIT_SWITCH_PIN_J3)
};


// Define Servo(s) for end effector/toolhead
Servo gripper;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Initialize each Actuator in the SCARA Robot
  for (int i = 0; i < NUM_JOINTS; i++) {
    SCARA_robot[i].init();
  }// end for

  // Home each joint/axis of SCARA Robot
  SCARA_robot[0].homeActuator(1);
  SCARA_robot[1].homeActuator(1);
  SCARA_robot[2].homeActuator(1);
  SCARA_robot[3].homeActuator(1);

}

void loop() {
  // put your main code here, to run repeatedly:

}
