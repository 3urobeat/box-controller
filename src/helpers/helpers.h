/*
 * File: lcd.h
 * Project: box-controller
 * Created Date: 24.08.2022 17:39:34
 * Author: 3urobeat
 * 
 * Last Modified: 25.08.2022 21:43:44
 * Modified By: 3urobeat
 * 
 * Copyright (c) 2022 3urobeat <https://github.com/HerrEurobeat>
 * 
 * Licensed under the MIT license: https://opensource.org/licenses/MIT
 * Permission is granted to use, copy, modify, and redistribute the work.
 * Full license information available in the project LICENSE file. 
 */


#include "main.h"

void clearLine(int maxcol, int row);
void lcdPrint(const char *str);
void centerPrint(const char *str, int row, bool callclearLine);

float measureCurrentPower();
float getAveragePower(float measurement);
float getPeakPower(float measurement);