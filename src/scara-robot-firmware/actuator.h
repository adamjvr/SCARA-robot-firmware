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

#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "ls7366r_arduino.h"
#include <AccelStepper.h>

class Actuator {
public:
    // Constructor: Initializes Actuator with LS7366R and AccelStepper configuration
    Actuator(uint8_t ls7366rCsPin, SPIClass& ls7366rSpiPort, uint8_t stepperStepPin, uint8_t stepperDirPin, uint8_t limitSwitchPin);

    // Initialization function
    void init();

    // Function to drive the stepper motor clockwise a specified number of rotations
    void driveClockwiseRotations(float rotations);

    // Function to drive the stepper motor counterclockwise a specified number of rotations
    void driveCounterclockwiseRotations(float rotations);

    // Function to home the actuator by driving the motor either clockwise or counterclockwise
    void homeActuator(uint8_t direction);

private:
    // LS7366R and AccelStepper objects
    LS7366R encoder;
    AccelStepper stepper;

    // Limit switch input pin
    uint8_t limitSwitchPin;

    // Stepper motor driver enable pin
    uint8_t stepperEnablePin;
};

#endif /* ACTUATOR_H */
