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

#include "SCARA_KINEMATICS.h"
#include <cmath>

// Implementation file for the ScaraKinematics class
// This file provides the detailed implementation of the member functions

ScaraKinematics::ScaraKinematics() : theta1(0), theta2(0), xP(0), yP(0), L1(0), L2(0), Phi(3.14159265359), phi(0), zP(0) {
    // Constructor initializes member variables to default values
    // Modify as needed based on the specific requirements of your robot
}

void ScaraKinematics::forwardKinematics(JointAngles &angles) {
    // Compute forward kinematics using the current joint angles
    float theta1F = theta1 * Phi / 180;
    float theta2F = theta2 * Phi / 180;
    xP = round(L1 * cos(theta1F) + L2 * cos(theta1F + theta2F));
    yP = round(L1 * sin(theta1F) + L2 * sin(theta1F + theta2F));

    // Update the JointAngles struct with the calculated joint angles
    angles.theta1 = theta1;
    angles.theta2 = theta2;
    angles.phi = phi;
}

void ScaraKinematics::inverseKinematics(float x, float y, JointAngles &angles) {
    // Compute inverse kinematics based on tool coordinates (x, y)
    
    // Calculate theta2 using the law of cosines
    theta2 = acos((std::pow(x, 2) + std::pow(y, 2) - std::pow(L1, 2) - std::pow(L2, 2)) / (2 * L1 * L2));

    // Adjust theta2 for the correct quadrant
    if (x < 0 && y < 0) {
        theta2 = -theta2;
    }

    // Calculate theta1 using the law of sines
    theta1 = atan2(y, x) - atan2(L2 * sin(theta2), (L1 + L2 * cos(theta2)));

    // Adjust theta1 for the correct quadrant
    if (x >= 0 && y >= 0) {
        theta1 = 90 - theta1;
    } else if (x < 0 && y > 0) {
        theta1 = 90 - theta1;
    } else if (x < 0 && y < 0) {
        theta1 = 270 - theta1;
        phi = 270 - theta1 - theta2;
        phi = -phi;
    } else if (x > 0 && y < 0) {
        theta1 = -90 - theta1;
    } else if (x < 0 && y == 0) {
        theta1 = 270 + theta1;
    }

    // Calculate phi angle so the gripper is parallel to the X-axis
    phi = 90 + theta1 + theta2;
    phi = -phi;

    // Adjust phi for the correct quadrant
    if (x < 0 && y < 0) {
        phi = 270 - theta1 - theta2;
    }
    if (std::abs(phi) > 165) {
        phi = 180 + phi;
    }

    // Round angles
    theta1 = round(theta1);
    theta2 = round(theta2);
    phi = round(phi);

    // Update the JointAngles struct with the calculated joint angles
    angles.theta1 = theta1;
    angles.theta2 = theta2;
    angles.phi = phi;
}


