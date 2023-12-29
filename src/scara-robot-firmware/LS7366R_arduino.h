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

#ifndef LS7366R_ARDUINO_H
#define LS7366R_ARDUINO_H

#include <Arduino.h>
#include <SPI.h>

class LS7366R {
public:
    // LS7366R Commands
    static const uint8_t READ_COUNTER = 0x60;
    static const uint8_t READ_STATUS = 0x40;
    static const uint8_t READ_MODE = 0x88;
    static const uint8_t WRITE_MODE = 0xC0;
    static const uint8_t LOAD_COUNTER = 0x50;
    static const uint8_t LOAD_OTR = 0x90;
    static const uint8_t CLEAR_COUNTER = 0x20;
    static const uint8_t CLEAR_OTR = 0x28;
    static const uint8_t READ_OTR = 0xB8;
    static const uint8_t NO_OP = 0xFF;

    // Constructor: Initializes LS7366R with CS pin and SPI port
    LS7366R(uint8_t csPin, SPIClass& spiPort);

    // Initialization function
    void init();

    // Function to send a command to LS7366R
    void sendCommand(uint8_t command);

    // Function to read the counter value from LS7366R
    uint32_t readCounter();

    // Function to clear the counter in LS7366R
    void clearCounter();

    // Function to read the status register of LS7366R
    uint8_t readStatus();

    // Function to read the mode register of LS7366R
    uint8_t readMode();

    // Function to write to the mode register of LS7366R
    void writeMode(uint8_t mode);

    // Function to load a value into the counter of LS7366R
    void loadCounter(uint32_t value);

    // Function to load a value into the OTR (One Turn Register) of LS7366R
    void loadOTR(uint32_t value);

    // Function to read the value from the OTR (One Turn Register) of LS7366R
    uint32_t readOTR();

private:
    uint8_t csPin;       // Chip Select (CS) pin
    SPIClass& spiPort;   // Reference to the SPI port
};

#endif /* LS7366R_ARDUINO_H */
