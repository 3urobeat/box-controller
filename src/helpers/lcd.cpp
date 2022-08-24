/*
 * File: lcd.cpp
 * Project: box-controller
 * Created Date: 24.08.2022 17:39:34
 * Author: 3urobeat
 * 
 * Last Modified: 24.08.2022 18:54:27
 * Modified By: 3urobeat
 * 
 * Copyright (c) 2022 3urobeat <https://github.com/HerrEurobeat>
 * 
 * Licensed under the MIT license: https://opensource.org/licenses/MIT
 * Permission is granted to use, copy, modify, and redistribute the work.
 * Full license information available in the project LICENSE file.
 */


#include "helpers.h"


void clearLine(int maxcol, int row)
{
    lcd.setCursor(0, row);

    //print maxcol amount of spaces to effectively clear the line
    char str[maxcol + 1];

    for (int i = 0; i < maxcol; i++) {
        str[i] = ' ';
    }

    str[maxcol] = '\0';

    lcdPrint(str);
}


void lcdPrint(const char *str)
{
    //Either print directly or cut string and then print the shortened string if it is wider than the display
    if (strlen(str) <= (unsigned int) maxcol) {
        lcd.print(str);
    } else {
        char temp[maxcol + 1]; // +1 for the null char
        strncpy(temp, str, maxcol); //Cut String if it is too long to prevent it overflowing to another row
        lcd.print(temp);
    }
}


void centerPrint(const char *str, int row, bool callclearLine) {
    if (callclearLine) clearLine(maxcol, row);

    //Calculate column
    int offset = maxcol - strlen(str);
    if (offset < 0) offset = 0; //set offset to 0 if it would be negative

    lcd.setCursor(offset / 2, row); //center string
    lcdPrint(str);
}