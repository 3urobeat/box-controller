/*
 * File: main.cpp
 * Project: box-controller
 * Created Date: 24.08.2022 17:39:34
 * Author: 3urobeat
 * 
 * Last Modified: 06.09.2022 17:21:40
 * Modified By: 3urobeat
 * 
 * Copyright (c) 2022 3urobeat <https://github.com/HerrEurobeat>
 * 
 * Licensed under the MIT license: https://opensource.org/licenses/MIT
 * Permission is granted to use, copy, modify, and redistribute the work.
 * Full license information available in the project LICENSE file. 
 */


#include <Wire.h>
#include <NoiascaLiquidCrystal.h> // Article (german): https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm | Direct download: https://werner.rothschopf.net/2020/NoiascaLiquidCrystal.zip
#include <lcdHelper.h>
#include "helpers/helpers.h"

const int maxcol = 20;
const int maxrow = 4;
char version[] = "v0.1.0";

lcdHelper<LiquidCrystal_PCF8574> lcd(0x27, maxcol, 4);

float current, average, peak;
unsigned long lastReprint;


//Setup stuff on poweron
void setup() {

    //initiate display
    Wire.begin();
    lcd.begin();
    lcd.backlight();

    //Print startup screen
    lcd.centerPrint("Box Controller", 0, true);
    lcd.centerPrint(version, 1, true);
    delay(500);

    //Clear lcd when ready and enter loop()
    lcd.clear();
    
}


/**
 * Prints the current measurements every 100ms
 */
void printMeasurements() {

    // Print power measurements, give each value 5 chars on the display plus 1 char for the unit
    char buf[6] = "";

    lcd.setCursor(0, 3);
    lcd.alignedPrint("right", itoa((int) current, buf, 10), 5); //cast to int because of measurement inaccuracy
    lcd.print("W");

    lcd.setCursor(7, 3);
    lcd.alignedPrint("right", itoa((int) average, buf, 10), 5); 
    lcd.print("W");

    lcd.setCursor(14, 3);
    lcd.alignedPrint("right", itoa((int) peak, buf, 10), 5); 
    lcd.print("W");
    
}


/**
 * Measures every 10ms
 */
void loop() {

    //print power measurements
    current = measureCurrentPower();
    average = getAveragePower(current);
    peak    = getPeakPower(current);

    //print measurements to lcd every 100ms to avoid "display lag"
    if (lastReprint + 250 <= millis()) {
        printMeasurements();
        lastReprint = millis();
    }

    delay(10);
}