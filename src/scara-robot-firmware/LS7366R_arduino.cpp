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

// Updated constructor to accept SPI port as a parameter
LS7366R::LS7366R(uint8_t csPin, SPIClass& spiPort) : csPin(csPin), spiPort(spiPort) {}

void LS7366R::init() {
    pinMode(csPin, OUTPUT);
    digitalWrite(csPin, HIGH);
    spiPort.begin(); // Initialize the selected SPI port
}

void LS7366R::sendCommand(uint8_t command) {
    digitalWrite(csPin, LOW);
    spiPort.transfer(command);
    digitalWrite(csPin, HIGH);
}

uint32_t LS7366R::readCounter() {
    uint32_t count = 0;

    digitalWrite(csPin, LOW);
    spiPort.transfer(READ_COUNTER); // Use class-level constant
    count |= (uint32_t)spiPort.transfer(0) << 24;
    count |= (uint32_t)spiPort.transfer(0) << 16;
    count |= (uint32_t)spiPort.transfer(0) << 8;
    count |= (uint32_t)spiPort.transfer(0);
    digitalWrite(csPin, HIGH);

    return count;
}

void LS7366R::clearCounter() {
    sendCommand(CLEAR_COUNTER); // Use class-level constant
}
