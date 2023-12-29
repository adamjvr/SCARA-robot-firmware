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

#include "actuator.h"

// Constructor: Initializes Actuator with LS7366R and AccelStepper configuration
Actuator::Actuator(uint8_t ls7366rCsPin, SPIClass& ls7366rSpiPort, uint8_t stepperStepPin, uint8_t stepperDirPin, uint8_t limitSwitchPin)
    : encoder(ls7366rCsPin, ls7366rSpiPort), stepper(AccelStepper::DRIVER, stepperStepPin, stepperDirPin), limitSwitchPin(limitSwitchPin) {}

// Initialization function
void Actuator::init() {
    // Initialize LS7366R and AccelStepper
    encoder.init();
    stepper.setMaxSpeed(2000.0);    // Set your desired max speed (steps per second)
    stepper.setAcceleration(1000.0); // Set your desired acceleration (steps per second^2)

    // Enable the stepper motor driver
    pinMode(stepperEnablePin, OUTPUT);
    digitalWrite(stepperEnablePin, LOW);

    // Set the limit switch pin as INPUT
    pinMode(limitSwitchPin, INPUT);

    // Move the stepper motor to the initial position
    stepper.setCurrentPosition(0);
    stepper.moveTo(0);
}

// Function to drive the stepper motor clockwise a specified number of rotations
void Actuator::driveClockwiseRotations(float rotations) {
    // Read the LS7366R counter value and convert it to rotations
    uint32_t counterValue = encoder.readCounter();
    float currentRotations = counterValue / 200.0; // Assuming 200 steps per revolution

    // Calculate the remaining rotations to the target
    float remainingRotations = rotations + currentRotations;

    // Convert remaining rotations to steps
    long remainingSteps = remainingRotations * 200.0; // Assuming 200 steps per revolution

    // Move the stepper motor to the target position (clockwise)
    stepper.moveTo(remainingSteps);

    // Update the AccelStepper object
    stepper.run();
}

// Function to drive the stepper motor counterclockwise a specified number of rotations
void Actuator::driveCounterclockwiseRotations(float rotations) {
    // Read the LS7366R counter value and convert it to rotations
    uint32_t counterValue = encoder.readCounter();
    float currentRotations = counterValue / 200.0; // Assuming 200 steps per revolution

    // Calculate the remaining rotations to the target
    float remainingRotations = currentRotations - rotations;

    // Convert remaining rotations to steps
    long remainingSteps = remainingRotations * 200.0; // Assuming 200 steps per revolution

    // Move the stepper motor to the target position (counterclockwise)
    stepper.moveTo(-remainingSteps);

    // Update the AccelStepper object
    stepper.run();
}

// Function to home the actuator by driving the motor either clockwise or counterclockwise
void Actuator::homeActuator(uint8_t direction) {
    // Enable the stepper motor driver
    digitalWrite(stepperEnablePin, LOW);

    // Move the stepper motor in the specified direction until the limit switch is triggered
    if (direction == 0) {
        // Drive counterclockwise
        stepper.moveTo(-1000000); // Move a large negative value
        while (digitalRead(limitSwitchPin) != HIGH) {
            stepper.run();
        }
    } else {
        // Drive clockwise
        stepper.moveTo(1000000); // Move a large positive value
        while (digitalRead(limitSwitchPin) != HIGH) {
            stepper.run();
        }
    }

    // Stop the stepper motor
    stepper.stop();

    // Move the stepper motor to the initial position
    stepper.setCurrentPosition(0);
    stepper.moveTo(0);

    // Update the AccelStepper object
    stepper.run();

    // Disable the stepper motor driver
    digitalWrite(stepperEnablePin, HIGH);
}
