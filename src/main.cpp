/*
 * File: main.cpp
 * Project: box-controller
 * Created Date: 24.08.2022 17:39:34
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


#include <Wire.h>
#include <NoiascaLiquidCrystal.h> // Article (german): https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm | Direct download: https://werner.rothschopf.net/2020/NoiascaLiquidCrystal.zip
#include <lcdHelper.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "helpers/helpers.h"

const int maxcol = 20;
const int maxrow = 4;
char version[] = "v1.1.0";

lcdHelper<LiquidCrystal_PCF8574> lcd(0x26, maxcol, 4);

OneWire oneWire(2); // temp sensor is connected to pin D2
DallasTemperature sensors(&oneWire);

float temp, current, average, peak, powerConsumed = 0;
unsigned long lastReprint, lastAnimationSwitch;

DeviceAddress addr; // store address of temp sensor here


//Setup stuff on poweron
void setup() {

    // initiate display
    Wire.begin();
    lcd.begin();
    lcd.backlight();

    // Print startup screen
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
    delay(2500); // at least wait 1000 ms for getTempC() to be done
    lcd.clear();

    // Display title
    lcd.home();
    lcd.print("Box Ctrl");

    lastAnimationSwitch = millis();
    
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