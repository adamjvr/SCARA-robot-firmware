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
    static const uint8_t CLEAR_COUNTER = 0x20;

    LS7366R(uint8_t csPin, SPIClass& spiPort); // Updated constructor
    void init();
    void sendCommand(uint8_t command);
    uint32_t readCounter();
    void clearCounter();

private:
    uint8_t csPin;
    SPIClass& spiPort; // Reference to the SPI port
};

#endif /* LS7366R_ARDUINO_H */
