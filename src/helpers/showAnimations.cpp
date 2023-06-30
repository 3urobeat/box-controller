/*
 * File: showAnimations.cpp
 * Project: helpers
 * Created Date: 08.09.2022 13:54:48
 * Author: 3urobeat
 * 
 * Last Modified: 30.06.2023 10:12:40
 * Modified By: 3urobeat
 * 
 * Copyright (c) 2022 3urobeat <https://github.com/3urobeat>
 * 
 * Licensed under the MIT license: https://opensource.org/licenses/MIT
 * Permission is granted to use, copy, modify, and redistribute the work.
 * Full license information available in the project LICENSE file.  
 */


#include "helpers.h"

uint8_t activeAnimation = 9; // tracks current animation. Start with something invalid so first animation only starts 30 secs after turn on
uint8_t repetition = 0;      // tracks repeated calls of the same animation
uint8_t reset = 0;           // tracks resets (moveOffset to 0) of an animation
uint8_t moveOffset = 0;      // tracks offset of moving string

bool blinkOn = false; // track blinking of temperature

// List of animations
const char titleAnimation1[9][9] = { "box ctrl", "bOx ctrl", "boX ctrl", "box ctrl", "box Ctrl", "box cTrl", "box ctRl", "box ctrL", "box ctrl" };
const char titleAnimation2[] = "________Box Ctrl";

const char dividerAnimation1[] = "                    --------------------                    ";

/**
 * Displays an animated title and divider row
 */
void showAnimations() {

    // Show different animation each 30 seconds
    if (millis() - lastAnimationSwitch >= 30000) {
        lastAnimationSwitch = millis();
        repetition = 0;
        reset = 0;
        moveOffset = 0; // reset moveOffset so the next animation will start fresh

        // Switch to next animation, reset if all have been shown
        activeAnimation++;
        if (activeAnimation > 2) activeAnimation = 0;

        // reset title
        lcd.home();
        lcd.print("Box Ctrl");

        // reset divider
        lcd.clearLine(1);
    } else {
        repetition++; // count repeated call of the same animation
    }

    // Play correct animation
    switch (activeAnimation) {
        // First title animation: Moving upper case char
        case 0:
            if (repetition % 2 == 1) return; // update only every second iteration, effectively every 500ms
            lcd.home();

            if (moveOffset >= 9) {
                moveOffset = 0;
                reset++;
            }

            if (reset % 2 != 1 && reset < 5) { // take breaks between runs and only run 3 times to not get stuck in switch
                lcd.print(titleAnimation1[moveOffset]);
            } else {
                if (moveOffset == 0) lcd.print("Box Ctrl"); // reset to default title between runs
            }

            moveOffset++;
            break;
            
        // First divider animation: Moving bar
        case 1:
            if (moveOffset >= 41) {
                moveOffset = 0;
                reset++;
            }

            if (reset < 2) { // only run 2 times to not get stuck in switch
                lcd.setCursor(0, 1);
                lcd.movingPrint(dividerAnimation1, &moveOffset, maxcol);
            }
            break;

        // Second title animation: Underscores popping up characters
        case 2:
            if (repetition % 2 == 1) return; // only update each 500ms
            if (moveOffset >= 9) {
                moveOffset = 0;
                reset++;
            }

            if (reset % 2 != 1 && reset < 5) { // take breaks between runs and only run 3 times to not get stuck in switch
                lcd.home();
                lcd.movingPrint(titleAnimation2, &moveOffset, 8);
            } else {
                moveOffset++; // count manually so that the reset check above works
            }
            break;

        // TODO: Second divider animation, Maybe use movingPrint center to sides animation?
    }


    // show temp with blinking animation if temp >=35
    if (temp >= 40) {
        if (repetition % 2 == 1) return; // only update every 500ms

        char buf[6] = "";
        lcd.setCursor(0, 2);

        if (blinkOn) {
            lcd.print("        ");
        } else {
            lcd.print("! ");
            lcd.print(dtostrf(temp, 4, 1, buf));
            lcd.print("°C  ");
        }

        blinkOn = !blinkOn;
    }
    
}