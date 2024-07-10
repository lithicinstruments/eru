/*
 * Author: Tyler Reckart (tyler.reckart@gmail.com)
 * Copyright 2024
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * See http://creativecommons.org/licenses/MIT/ for more information.
 */

#include "ModulationMatrix.h"
#include <EEPROM.h>

int modulationMatrix[4][4];
const int cvInputPins[4] = {A0, A1, A2, A3}; // Example analog pins
const int outputPins[4] = {9, 10, 11, 12}; // Example output pins

void setupModulationMatrix() {
  for (int i = 0; i < 4; i++) {
    pinMode(outputPins[i], OUTPUT);
  }
}

void updateModulationMatrix() {
  // Update the modulation matrix based on CV inputs and encoder values
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      modulationMatrix[i][j] = analogRead(cvInputPins[i]) / 4; // Example scaling
    }
  }
}

void applyModulationMatrix() {
  // Apply the modulation matrix to the outputs
  for (int i = 0; i < 4; i++) {
    int modValue = 0;
    for (int j = 0; j < 4; j++) {
      modValue += modulationMatrix[i][j];
    }
    analogWrite(outputPins[i], modValue);
  }
}

void loadPreset(int presetIndex) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      modulationMatrix[i][j] = EEPROM.read(presetIndex * 16 + i * 4 + j);
    }
  }
}

void savePreset(int presetIndex) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      EEPROM.write(presetIndex * 16 + i * 4 + j, modulationMatrix[i][j]);
    }
  }
}
