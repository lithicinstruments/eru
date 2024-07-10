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

#include "Encoders.h"
#include <Encoder.h>

#define ENC1_PIN_A 2
#define ENC1_PIN_B 3
#define ENC2_PIN_A 4
#define ENC2_PIN_B 5
#define ENC3_PIN_A 6
#define ENC3_PIN_B 7
#define ENC4_PIN_A 8
#define ENC4_PIN_B 9
#define ENC4_BUTTON_PIN 10

Encoder enc1(ENC1_PIN_A, ENC1_PIN_B);
Encoder enc2(ENC2_PIN_A, ENC2_PIN_B);
Encoder enc3(ENC3_PIN_A, ENC3_PIN_B);
Encoder enc4(ENC4_PIN_A, ENC4_PIN_B);

extern int currentMenu;
extern int currentSubMenu;
extern bool isTrigger[4];

long lastEnc1Value = 0;
long lastEnc2Value = 0;
long lastEnc3Value = 0;
long lastEnc4Value = 0;

void setupEncoders() {
  pinMode(ENC4_BUTTON_PIN, INPUT_PULLUP);
}

void handleEncoders() {
  long enc1Value = enc1.read();
  long enc2Value = enc2.read();
  long enc3Value = enc3.read();
  long enc4Value = enc4.read();

  // Encoder 1 to navigate main menu
  if (enc1Value != lastEnc1Value) {
    currentMenu = (currentMenu + (enc1Value > lastEnc1Value ? 1 : -1)) % 3;
    if (currentMenu < 0) currentMenu += 3;
    lastEnc1Value = enc1Value;
  }

  // Encoder 2 to adjust submenu items
  if (enc2Value != lastEnc2Value) {
    if (currentMenu == 1) { // Input settings menu
      int inputIndex = (enc2Value / 4) % 4;
      if (inputIndex < 0) inputIndex += 4;
      isTrigger[inputIndex] = !isTrigger[inputIndex];
    } else if (currentMenu == 2) { // Presets menu
      currentSubMenu = (currentSubMenu + (enc2Value > lastEnc2Value ? 1 : -1)) % 10; // Assume 10 presets
      if (currentSubMenu < 0) currentSubMenu += 10;
    }
    lastEnc2Value = enc2Value;
  }

  // Encoder 3 and 4 to adjust parameters if needed
  // (You can add more logic here based on your needs)

  // Encoder 4 button press to load/save presets
  if (digitalRead(ENC4_BUTTON_PIN) == LOW) {
    if (currentMenu == 2) {
      savePreset(currentSubMenu);
    }
  }
}
