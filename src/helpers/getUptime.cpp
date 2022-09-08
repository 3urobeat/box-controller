/*
 * File: getUptime.cpp
 * Project: helpers
 * Created Date: 07.09.2022 14:42:31
 * Author: 3urobeat
 * 
 * Last Modified: 08.09.2022 13:38:48
 * Modified By: 3urobeat
 * 
 * Copyright (c) 2022 3urobeat <https://github.com/HerrEurobeat>
 * 
 * Licensed under the MIT license: https://opensource.org/licenses/MIT
 * Permission is granted to use, copy, modify, and redistribute the work.
 * Full license information available in the project LICENSE file. 
 */


#include "helpers.h"


/**
 * Writes current uptime into dest. 
 * Format when <1 hour uptime: min:sec
 * Format when >1 hour uptime: hour:min:sec
 */
char* getUptime(char *dest) {

    // Get uptime in secs, create buffer and clear dest
    unsigned long uptime = millis() / 1000; // current uptime in seconds
    char numBuf[3] = "";
    dest[0] = '\0'; // make sure dest is empty (can't use memset here as we can't use sizeof(), so we only set first byte to 0 which is enough for strcat to work correctly)

    // Add hours and divider if uptime >1 hour
    if (uptime > 3600) {
        uint8_t hours = uptime / 3600;
        lcd.toFixedLengthNumber(numBuf, hours, 2);
        strcat(dest, numBuf);

        strcat(dest, ":");
    }

    // Add minutes
    uint8_t minutes = (uptime % 3600) / 60;
    lcd.toFixedLengthNumber(numBuf, minutes, 2);
    strcat(dest, numBuf);                         //using strncat is impractical as sizeof doesn't return right size

    // Add divider
    strcat(dest, ":");

    // Add seconds
    uint8_t seconds = uptime % 60;
    lcd.toFixedLengthNumber(numBuf, seconds, 2);
    strcat(dest, numBuf);

    return dest;
    
}