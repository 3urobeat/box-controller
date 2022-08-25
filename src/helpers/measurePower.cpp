/*
 * File: measurePower.cpp
 * Project: box-controller
 * Created Date: 25.08.2022 18:54:22
 * Author: 3urobeat
 * 
 * Last Modified: 25.08.2022 19:00:45
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
 * Measures the current power consumption using an L01Z100S05
 */
float measurePower() {

    float readout = analogRead(A0);

    float voltage = (readout * 5.015) / 1024;
    float current = (voltage - 2.5124) * 66.666;
    
    return current * 12; //current * 12 because Vcc 12V

}