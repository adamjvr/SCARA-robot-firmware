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


#include "LS7366R_arduino.h"

// Constructor: Initializes LS7366R with CS pin and SPI port
LS7366R::LS7366R(uint8_t csPin, SPIClass& spiPort) : csPin(csPin), spiPort(spiPort) {}

// Initialization function
void LS7366R::init() {
    pinMode(csPin, OUTPUT);
    digitalWrite(csPin, HIGH); // Initialize CS high (deselected)
    spiPort.begin();            // Initialize the selected SPI port
}

// Function to send a command to LS7366R
void LS7366R::sendCommand(uint8_t command) {
    digitalWrite(csPin, LOW);   // Select LS7366R by lowering CS
    spiPort.transfer(command);    // Send the specified command over SPI
    digitalWrite(csPin, HIGH);  // Deselect LS7366R by raising CS
}

// Function to read the counter value from LS7366R
uint32_t LS7366R::readCounter() {
    uint32_t count = 0;

    digitalWrite(csPin, LOW);         // Select LS7366R by lowering CS
    spiPort.transfer(READ_COUNTER);    // Send the Read Counter command

    // Read the counter value (32 bits) over SPI
    count |= (uint32_t)spiPort.transfer(0) << 24;
    count |= (uint32_t)spiPort.transfer(0) << 16;
    count |= (uint32_t)spiPort.transfer(0) << 8;
    count |= (uint32_t)spiPort.transfer(0);

    digitalWrite(csPin, HIGH);        // Deselect LS7366R by raising CS

    return count;
}

// Function to clear the counter in LS7366R
void LS7366R::clearCounter() {
    sendCommand(CLEAR_COUNTER); // Send the Clear Counter command
}

// Function to read the status register of LS7366R
uint8_t LS7366R::readStatus() {
    uint8_t status = 0;

    digitalWrite(csPin, LOW);         // Select LS7366R by lowering CS
    spiPort.transfer(READ_STATUS);     // Send the Read Status command

    // Read the status register value over SPI
    status = spiPort.transfer(0);

    digitalWrite(csPin, HIGH);        // Deselect LS7366R by raising CS

    return status;
}

// Function to read the mode register of LS7366R
uint8_t LS7366R::readMode() {
    uint8_t mode = 0;

    digitalWrite(csPin, LOW);         // Select LS7366R by lowering CS
    spiPort.transfer(READ_MODE);       // Send the Read Mode command

    // Read the mode register value over SPI
    mode = spiPort.transfer(0);

    digitalWrite(csPin, HIGH);        // Deselect LS7366R by raising CS

    return mode;
}

// Function to write to the mode register of LS7366R
void LS7366R::writeMode(uint8_t mode) {
    sendCommand(WRITE_MODE);   // Send the Write Mode command
    spiPort.transfer(mode);    // Send the mode value over SPI
}

// Function to load a value into the counter of LS7366R
void LS7366R::loadCounter(uint32_t value) {
    sendCommand(LOAD_COUNTER);  // Send the Load Counter command

    // Send the 32-bit value over SPI
    spiPort.transfer((value >> 24) & 0xFF);
    spiPort.transfer((value >> 16) & 0xFF);
    spiPort.transfer((value >> 8) & 0xFF);
    spiPort.transfer(value & 0xFF);
}

// Function to load a value into the OTR (One Turn Register) of LS7366R
void LS7366R::loadOTR(uint32_t value) {
    sendCommand(LOAD_OTR);     // Send the Load OTR command

    // Send the 32-bit value over SPI
    spiPort.transfer((value >> 24) & 0xFF);
    spiPort.transfer((value >> 16) & 0xFF);
    spiPort.transfer((value >> 8) & 0xFF);
    spiPort.transfer(value & 0xFF);
}

// Function to read the value from the OTR (One Turn Register) of LS7366R
uint32_t LS7366R::readOTR() {
    uint32_t otrValue = 0;

    digitalWrite(csPin, LOW);         // Select LS7366R by lowering CS
    spiPort.transfer(READ_OTR);        // Send the Read OTR command

    // Read the OTR value over SPI
    otrValue |= (uint32_t)spiPort.transfer(0) << 24;
    otrValue |= (uint32_t)spiPort.transfer(0) << 16;
    otrValue |= (uint32_t)spiPort.transfer(0) << 8;
    otrValue |= (uint32_t)spiPort.transfer(0);

    digitalWrite(csPin, HIGH);        // Deselect LS7366R by raising CS

    return otrValue;
}
