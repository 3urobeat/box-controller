/*
 * File: printMeasurements.cpp
 * Project: src
 * Created Date: 07.09.2022 14:32:47
 * Author: 3urobeat
 * 
 * Last Modified: 07.09.2022 14:33:26
 * Modified By: 3urobeat
 * 
 * Copyright (c) 2022 3urobeat <https://github.com/HerrEurobeat>
 * 
 * Licensed under the MIT license: https://opensource.org/licenses/MIT
 * Permission is granted to use, copy, modify, and redistribute the work.
 * Full license information available in the project LICENSE file. 
 */


#include "main.h"


/**
 * Prints the current measurements every 100ms
 */
void printMeasurements() {

    char buf[6] = "";

    // Print temp measurement
    lcd.setCursor(0, 2);
    lcd.alignedPrint("right", dtostrf(temp, 4, 3, buf), 4); // use getTempC() instead of getTempCByIndex() as it is too slow
    lcd.print("°C");

    // get new measurement which will be ready when this function is called the next time
    sensors.requestTemperaturesByAddress(addr); // only get temp for this specific sensor as it is faster than calling requestTemperatures()
    temp = sensors.getTempC(addr);              // get temp by addr instead of 

    // Print power measurements, give each value 5 chars on the display plus 1 char for the unit
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