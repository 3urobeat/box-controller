/*
 * File: main.cpp
 * Project: box-controller
 * Created Date: 24.08.2022 17:39:34
 * Author: 3urobeat
 * 
 * Last Modified: 07.09.2022 14:18:53
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
#include <OneWire.h>
#include <DallasTemperature.h>
#include "helpers/helpers.h"

const int maxcol = 20;
const int maxrow = 4;
char version[] = "v0.1.0";

lcdHelper<LiquidCrystal_PCF8574> lcd(0x27, maxcol, 4);

OneWire oneWire(2); // temp sensor is connected to pin D2
DallasTemperature sensors(&oneWire);


float temp, current, average, peak;
unsigned long lastReprint;

DeviceAddress addr; // store address of temp sensor here


//Setup stuff on poweron
void setup() {

    //initiate display
    Wire.begin();
    lcd.begin();
    lcd.backlight();

    //Print startup screen
    lcd.centerPrint("Box Controller", 0, true);
    lcd.centerPrint(version, 1, true);

    // get address of temp sensor
    sensors.begin();
    sensors.getAddress(addr, 0); // save address of temp sensor 0 into addr to make accessing it faster
    sensors.setResolution(addr, 9); // reduce resolution to speed up conversion (9 bits, 0.5°C is enough for our use case)
    sensors.setWaitForConversion(false); // disable lib waiting for conversion (93ms) as we need to take measurements in between

    // get first temp reading so it will be ready when printMeasurements() is called for the first time
    sensors.requestTemperaturesByAddress(addr);
    temp = sensors.getTempC(addr);

    // Clear lcd when ready and enter loop()
    delay(5000); // at least wait 1000 ms for getTempC() to be done
    lcd.clear();
    
}


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


/**
 * Measures every 10ms
 */
void loop() {

    // get power measurements
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