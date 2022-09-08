/*
 * File: main.h
 * Project: box-controller
 * Created Date: 24.08.2022 17:39:34
 * Author: 3urobeat
 * 
 * Last Modified: 08.09.2022 20:17:49
 * Modified By: 3urobeat
 * 
 * Copyright (c) 2022 3urobeat <https://github.com/HerrEurobeat>
 * 
 * Licensed under the MIT license: https://opensource.org/licenses/MIT
 * Permission is granted to use, copy, modify, and redistribute the work.
 * Full license information available in the project LICENSE file.
 */


#include <NoiascaLiquidCrystal.h>
#include <NoiascaHW/lcd_PCF8574.h>
#include <DallasTemperature.h>
#include <lcdHelper.h>

extern const int maxcol;
extern lcdHelper<LiquidCrystal_PCF8574> lcd;
extern DallasTemperature sensors;
extern float temp, current, average, peak;
extern unsigned long lastAnimationSwitch;
extern DeviceAddress addr;

void printMeasurements();