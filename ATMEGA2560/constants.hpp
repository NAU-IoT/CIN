/*
 * constants that will be used through this program
 */
#ifndef CONSTANTS_hpp
#define CONSTANTS_hpp
 
// define WiFi credentials
#define ssid "MyAltice d9fd0b"
#define WPA2 "8894-emerald-83"

// MQTT credentials
#define mqtt_server "192.168.1.12"      // MQTT broker IP (RPI 4 in this instance)
#define mqtt_user "akiel"
#define mqtt_pass "password"
#define clientID "CIN"

// MQTT topics
#define temp_topic "home/area/BME_temp"
#define hum_topic "home/area/BME_hum"
#define press_topic "home/area/BME_press"
#define alt_topic "home/area/BME_alt"
// #define topic_temp   "climate/BME_TEMP"
// #define topic_hum    "climate/BME_HUMIDITY"
// #define topic_press  "climate/BME_PRESS"
// #define topic_alt    "climate/BME_ALT"

// define BME 280 sea lvl pressure in hectopascals 
#define SEALEVELPRESSURE_HPA (1013.25)

/*
* define hex addresses for I2C protocol 
* for data & clock communication
*/
#define SHT_ADDR (0x44)
#define BME_ADDR (0x77)
#define LCD_ADDR (0x27)

/* 
 * define pins for LEDs that will provide visual error checking
 * when final device is on PCB... approaching final stages of development
 * hardware/software related
 */
//#define LED_RED 8
//#define LED_YELLOW 9

#endif

