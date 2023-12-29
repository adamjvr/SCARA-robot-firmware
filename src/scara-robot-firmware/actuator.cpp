#include "actuator.h"

// Constructor: Initializes Actuator with LS7366R and AccelStepper configuration
Actuator::Actuator(uint8_t ls7366rCsPin, SPIClass& ls7366rSpiPort, uint8_t stepperStepPin, uint8_t stepperDirPin)
    : encoder(ls7366rCsPin, ls7366rSpiPort), stepper(AccelStepper::DRIVER, stepperStepPin, stepperDirPin) {}

// Initialization function
void Actuator::init() {
    // Initialize LS7366R and AccelStepper
    encoder.init();
    stepper.setMaxSpeed(2000.0);    // Set your desired max speed (steps per second)
    stepper.setAcceleration(1000.0); // Set your desired acceleration (steps per second^2)

    // Enable the stepper motor driver
    pinMode(stepperEnablePin, OUTPUT);
    digitalWrite(stepperEnablePin, LOW);

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
