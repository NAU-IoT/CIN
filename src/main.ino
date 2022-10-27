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
#include "displayLCD.hpp"
#include "constants.hpp"

//#include "DS18B20.h"

#define VERSION 4
// define LCD with I2C addr and dimension
LCD a(0x27, 16, 02);
BME b(0x77);

// initialize different peripherals here
void setup() {
    // set baud rate
    Serial.begin(9600);
  
    a.initializeLCD();

    /*  for LED visual error checking initialize
     *  - RED
     *  - YELLOW
     *  - BLUE
     *  - GREEN 
     *  HIGH = ON
     *  LOW = OFF
     */
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    
}

// loop thru given functions to display sensor vals
void loop() {  
    // printToLCD function for our sensors  
    //LCD a(0x27, 16, 02);
    a.main();
    Serial.println("De-Bug");
    // declare BME sensors I2C address and call theprintToSerial function
    //BME b(0x77);
    b.printBMEToSerial();
    
    // printToSerial function for DS18B20 sensor
   
    delay(1000);
  
}
