/*
 * File: stringUtils.tpp
 * Project: helpers
 * Created Date: 28.08.2022 23:42:19
 * Author: 3urobeat
 * 
 * Last Modified: 29.08.2022 00:16:55
 * Modified By: 3urobeat
 * 
 * Copyright (c) 2022 3urobeat <https://github.com/HerrEurobeat>
 * 
 * Licensed under the MIT license: https://opensource.org/licenses/MIT
 * Permission is granted to use, copy, modify, and redistribute the work.
 * Full license information available in the project LICENSE file. 
 */


/**
 * Better strlen function to correctly count chars that are two bytes long (like ä ö or ü)
 * Credit: https://forum.arduino.cc/t/frage-zu-chararray-strlen-und-umlaut/897224/12 and https://stackoverflow.com/a/4063229
 */
template <typename lcd>
size_t lcdHelper<lcd>::utf8_strlen(const char *str) {
    int len = 0;
    while (*str) len += (*str++ & 0xc0) != 0x80;
    return len;
}