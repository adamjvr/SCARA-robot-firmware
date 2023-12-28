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

#ifndef SCARA_KINEMATICS_H
#define SCARA_KINEMATICS_H

// Header file for the ScaraKinematics class
// This class represents a simple SCARA robot and provides functions for forward and inverse kinematics

class ScaraKinematics {
public:
    // Constructor to initialize member variables
    ScaraKinematics();

    // Function to compute forward kinematics and update xP and yP
    void forwardKinematics();

    // Function to compute inverse kinematics based on tool coordinates (x, y)
    void inverseKinematics(float x, float y);

private:
    // Member variables representing robot state
    float theta1, theta2, xP, yP, L1, L2, Phi, phi, zP;  // Renamed 'PI' to 'Phi', add other necessary member variables
};

#endif // SCARA_KINEMATICS_H

