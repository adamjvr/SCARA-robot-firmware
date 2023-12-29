#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "ls7366r_arduino.h"
#include <AccelStepper.h>

class Actuator {
public:
    // Constructor: Initializes Actuator with LS7366R and AccelStepper configuration
    Actuator(uint8_t ls7366rCsPin, SPIClass& ls7366rSpiPort, uint8_t stepperStepPin, uint8_t stepperDirPin);

    // Initialization function
    void init();

    // Function to drive the stepper motor clockwise a specified number of rotations
    void driveClockwiseRotations(float rotations);

    // Function to drive the stepper motor counterclockwise a specified number of rotations
    void driveCounterclockwiseRotations(float rotations);

private:
    // LS7366R and AccelStepper objects
    LS7366R encoder;
    AccelStepper stepper;

    // Stepper motor driver enable pin
    uint8_t stepperEnablePin;
};

#endif /* ACTUATOR_H */
