/*
 * File: printMeasurements.cpp
 * Project: src
 * Created Date: 07.09.2022 14:32:47
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


#include "main.h"
#include "helpers/helpers.h"

unsigned long lastPeakFlip = millis();
bool showPeak = true;

/**
 * Prints the current measurements every 100ms
 */
void printMeasurements() {

    // Run showAnimations helper
    showAnimations();

    char buf[9] = "";

    // Display uptime
    lcd.setCursor(maxcol - 8, 0);
    lcd.alignedPrint("right", getUptime(buf), 8);

    // Print temp measurement if temp <35, otherwise showAnimations will handle it with some alarming blinky blinky
    if (temp < 40) {
        lcd.setCursor(0, 2);
        if (temp >= 35) lcd.print("! "); // show warning if temp is high

        lcd.print(dtostrf(temp, 4, 1, buf));
        lcd.print("°C  ");
    }

    // get new measurement which will be ready when this function is called the next time
    sensors.requestTemperaturesByAddress(addr); // only get temp for this specific sensor as it is faster than calling requestTemperatures()
    temp = sensors.getTempC(addr);              // use getTempC() instead of getTempCByIndex() as it is too slow

    // Print power measurements, give each value 5 chars on the display plus 1 char for the unit
    lcd.setCursor(0, 3);
    lcd.alignedPrint("right", itoa((int) current, buf, 10), 5); //cast to int because of measurement inaccuracy
    lcd.print("W");

    lcd.setCursor(6, 3);
    lcd.alignedPrint("right", itoa((int) average, buf, 10), 5); 
    lcd.print("W");

    
    if (millis() - lastPeakFlip > 5000) {
        showPeak = !showPeak; // flip between peak and power consumption since turn on every 5 sec
        lastPeakFlip = millis();
    }
    
    lcd.setCursor(13, 3);

    if (showPeak) {
        lcd.alignedPrint("right", itoa((int) peak, buf, 10), 5); 
        lcd.print("W ");
    } else {
        lcd.alignedPrint("right", dtostrf(powerConsumed, 4, 3, buf), 5);
        lcd.print("Wh");
    }
    
}