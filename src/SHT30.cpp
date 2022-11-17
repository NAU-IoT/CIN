/*
 * Reading values from the Wemos SHT30 Temperature and 
 * Humidity sensor
 */

#include "Wire.h"
#include "SHT31.h"
#include "SHT30.hpp"
#include "constants.hpp"

uint32_t start;
uint32_t stop;

SHT31 sht;

// initialize instance of BME for serial output display
SHT::SHT(int SHTaddr) {
    if (!sht.begin(SHTaddr)) {
        Serial.println("Could not find a valid SHT30 sensor, check wiring or default address.");   
    }
    
    Wire.setClock(100000);
    uint16_t stat = sht.readStatus();
    Serial.print(stat, HEX);
    Serial.println();
}

void SHT::collect() {
    // define SHT readings as float vals
    // convert sht celsius reading to fahrenheit 
    //float sht_temp = (sht.getTemperature() * 9/5 + 32, 1);
    //float sht_hum = (sht.getHumidity(), 1);
        
    Serial.println("From SHT30 Sensor: ");
    Serial.print("Temperature:");
    Serial.print(sht.getTemperature() * 9/5 + 32, 1);
    Serial.print("\t");
    Serial.print("Humidity:");
    Serial.println(sht.getHumidity(), 1);
    /*
    Serial.print("Temperature: ");
    Serial.print(sht_temp);
    Serial.println(" *F");
        
    Serial.print("Humidity: ");
    Serial.print(sht_hum);
    Serial.println(" %");
    */    
    Serial.println(); 

}
