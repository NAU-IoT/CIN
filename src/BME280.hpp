/*
 * library created to test library usage with arduino 
 * BME280 sensor
 */
#ifndef BME280_hpp
#define BME280_hpp

#include <Arduino.h>

class BME {
    public:
        BME(int BMEaddr);
        void printBMEToSerial();
};

#endif
