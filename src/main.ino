/*
 * Author(s) :
 *      - Akiel Aries
 * 
 * main file calling seperate headers that will display
 * the read in values on a 16x02 LCD screen as well as serial
 * output on TTY0/USB0.... 
 * * * * GOAL * * * *
 * transmit the same values over MQTT using port 
 * 1883, running into issues encorporating existing MQTT 
 * publish code into this modularized setting and calling 
 * the functions from the header files in this "driver" file 
 * * * * ISSUES * * * *
 * attempting to run the MQTT code that publishes the values
 * over PORT 1883, does not work in the desired way.
 *      - issues with arduinos loop() & setup() functions where
 *      there is no way to define my own main() like traditional
 *      programming
 *      - for AVR based MCUs, arduino setup() & loop() can be 
 *      found in a main.cpp file defining these functions 
 *      - for ESP based MCUs, things are a bit more complex....
 *          - setup() & loop() are defined within the SDK
 *          (Software Development Kit) for these specific architectures
 *      - issues with initializing objects more than once outside
 *      of the setup() function
 *          - setup() should only be called once; ideally anything
 *          initialized in setup will not be initialized again (NOT THE CASE)
 *          instead things must be declared in setup and again in loop in 
 *          order for loop to use whatever was declared
 */
#include <Arduino.h>
/*
* locally developed headers; PubSubClient is external lib
* for wireless communication using MQTT and pot 1883
*/
#include "PubSubClient.h"
#include "BME280.hpp"
#include "SHT30.hpp"
#include "displayLCD.hpp"
#include "constants.hpp"
#include "MQTT.hpp"
// #include "DS18B20.hpp"

// fourth working version of this project
#define VERSION 4

// initialize different peripherals here
void setup() {
    // set baud rate
    Serial.begin(9600);
    
    // initialize LCD in setup function
    LCD a(LCD_ADDR, 16, 02);
    a.initializeLCD();

    //MQTT c;    
    //c.connect_MQTT();
    
    /*  for LED visual error checking initialize
     *  - RED
     *  - YELLOW
     *  - BLUE
     *  - GREEN 
     *  HIGH = ON
     *  LOW = OFF
     
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    digitalWrite(10, HIGH);
    */
}

// loop thru given functions to display sensor vals
void loop() {  
    /* 
     *  since arduino only allows calling one function at a time
     *  we will be playing with the delay() functions and only
     *  calling them in the displayLCD.cpp file
     */  
     
    // print to LCD
    LCD a(LCD_ADDR, 16, 02);
    a.displayToLCD();

    // declare BME sensors I2C address and call the printToSerial function
    // BME b(BME_ADDR);
    // b.collect();

    // declare SHT sensor w/ I2C addr
    // SHT c(SHT_ADDR);
    // c.collect();

    // publish data to MQTT with call from MQTT.cpp
    MQTT d(BME_ADDR);    
    // d.connect_MQTT();
    d.publish_MQTT(); 
    //c.connect_MQTT();
    
    //delay(1000);
}
