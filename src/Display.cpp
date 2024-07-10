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

#include "Display.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1305 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

extern int currentMenu;
extern int currentSubMenu;
extern int modulationMatrix[4][4];
extern bool isTrigger[4];

void setupDisplay() {
  if(!display.begin(SSD1305_I2C_ADDRESS, OLED_RESET)) {
    Serial.println(F("SSD1305 allocation failed"));
    for(;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1305_WHITE);
  display.setCursor(0, 0);

  switch (currentMenu) {
    case 0:
      display.println(F("Modulation Matrix"));
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          display.print(modulationMatrix[i][j]);
          display.print(" ");
        }
        display.println();
      }
      break;
    case 1:
      display.println(F("Input Settings"));
      for (int i = 0; i < 4; i++) {
        display.print(F("Input "));
        display.print(i + 1);
        display.print(": ");
        display.println(isTrigger[i] ? F("Trigger") : F("Envelope Follower"));
      }
      break;
    case 2:
      display.println(F("Presets"));
      display.print(F("Current Preset: "));
      display.println(currentSubMenu);
      break;
  }

  display.display();
}
