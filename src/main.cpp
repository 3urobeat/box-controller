/*
 * File: main.cpp
 * Project: box-controller
 * Created Date: 24.08.2022 17:39:34
 * Author: 3urobeat
 * 
 * Last Modified: 24.08.2022 17:45:19
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
#include "helpers/helpers.h"

const int maxcol = 20;
const int maxrow = 4;
char version[] = "v0.1.0";

LiquidCrystal_PCF8574 lcd(0x27, maxcol, 4);


//Setup stuff on poweron
void setup() {

    //initiate display
    Wire.begin();
    lcd.begin();
    lcd.backlight();

    //Print startup screen
    centerPrint("Box Controller", 0, true);
    centerPrint(version, 1, true);
    delay(500);

    //Clear lcd when ready and enter loop()
    lcd.clear();
}


void loop() {

    delay(500);
}