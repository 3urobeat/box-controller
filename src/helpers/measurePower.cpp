/*
 * File: measurePower.cpp
 * Project: box-controller
 * Created Date: 25.08.2022 18:54:22
 * Author: 3urobeat
 * 
 * Last Modified: 25.08.2022 21:53:53
 * Modified By: 3urobeat
 * 
 * Copyright (c) 2022 3urobeat <https://github.com/HerrEurobeat>
 * 
 * Licensed under the MIT license: https://opensource.org/licenses/MIT
 * Permission is granted to use, copy, modify, and redistribute the work.
 * Full license information available in the project LICENSE file. 
 */


#include "helpers.h"


float averagePower = 0;
float peakPower    = 0;


/**
 * Measures the current power consumption using an L01Z100S05
 */
float measureCurrentPower() {

    float readout = analogRead(A0); //read measurement from pin A0

    float voltage = (readout * 5.015) / 1024;
    float current = (voltage - 2.5124) * 66.666; //-2.5124 offset (will now correctly display 0.00 idle)
    
    return current * 12; //current * 12 because Vcc 12V

}


/**
 * Adds a new measurement to the average power consumption and returns the current average
 * Call every 10ms to get avg over the last 10 seconds
 */
float getAveragePower(float measurement) {

    averagePower = ((averagePower * 1000) + measurement) / 1001; //calculate new average and update var

    return averagePower;

}


/**
 * Checks for a new peak and returns the current peak power measurement since poweron
 */
float getPeakPower(float measurement) {

    if (measurement > peakPower) peakPower = measurement; //check for new peak and update var

    return peakPower;

}