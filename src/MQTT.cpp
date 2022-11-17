/*
 * source file used to test MQTT data transmission
 * with C++
 */
 
#include "PubSubClient.h"
#include <ESP8266WiFi.h>
#include <Adafruit_BME280.h>
//#include "BME280.hpp"
#include "MQTT.hpp"
#include "constants.hpp"

// initialize wifi and mqtt objects
WiFiClient wifiClient;

// declare instance of BME for this file
Adafruit_BME280 bme1;

// 1883 is being used as listener port
    // look into passing this in or redefining twice
PubSubClient client(mqtt_server, 1883, wifiClient);


MQTT::MQTT(int BMEaddr) {
    // hardware address defined here for BME280 sensor
    if (!bme1.begin(BMEaddr)) {
      Serial.println("Could not find a valid BME280 sensor, check wiring or default address!");
      //while (1);
    }
}

// function to connect to mqtt broker via wifi and return error messages
void MQTT::connect_MQTT() {
    //PubSubClient client(mqtt_server, 1883, wifiClient);
    Serial.print("Connecting to: ");  
    Serial.println(ssid);
    // connect to wifi network using defined variables 
    /******* IMPLEMENT API FOR CREDENTIALS IN LATER VERSION *******/
    WiFi.begin(ssid, WPA2);
    
    // wait for connection confirmation before continuing
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
      
    // for debugging purposes, print IP of ESP8266 module
    Serial.println("WiFi Connected!");
    Serial.print("IP Addr of ESP2866 module: ");
    Serial.println(WiFi.localIP());
    
    // connect to MQTT broker and print connection succes or failure
        // issue with scope of client, look into where/how it is defined
    if (client.connect(clientID, mqtt_user, mqtt_pass)) {
        Serial.println("**** Connected to MQTT Broker ****");
    }
    
    else {
      Serial.println("Connection failed!");
    }
}

// publish values to MQTT
void MQTT::publish_MQTT() {
    // look into transmitting values as JSON earlier in process
    // perhaps implement values as map in cpp
    // translate data from map to string to dict
    // error check if issue was actually connection
    // look into refactoring client.connect() in conditionals below
    //PubSubClient client(mqtt_server, 1883, wifiClient);
    MQTT::connect_MQTT();
    Serial.setTimeout(2000);

    // define bme readings as float vals
    // convert bme celsius reading to fahrenheit 
    float _temp = bme1.readTemperature() * 9/5 + 32;
    float _hum = bme1.readHumidity();
    // convert bme pascals reading to hectropascals
    float _press = bme1.readPressure() / 100.0;
    // convert pressure to height in feet
    float _alt = bme1.readAltitude(SEALEVELPRESSURE_HPA * 3.281);

    // print values to serial
    Serial.print("Temperature: ");
    Serial.print(_temp);
    Serial.println(" *F");

    Serial.print("Humidity: ");
    Serial.print(_hum);
    Serial.println(" %");

    Serial.print("Pressure: ");
    Serial.print(_press);
    Serial.println(" hPa");

    Serial.print("Altitude: ");
    Serial.print(_alt);
    Serial.println(" ft");

    // transmit vals as strings
    String tempStr = "Temp: " + String((float)_temp) + " F ";
    String humStr = "Hum: " + String((float)_hum) + " % ";
    String pressStr = "Press: " + String((float)_press) + "hPa ";
    String altStr = "Altitude: " + String((float)_alt) + "ft ";

    // publish to MQTT broker using previously defined topics
        // publish temperature topic using c str
    if (client.publish(temp_topic, String(_temp).c_str())) {
        Serial.println("Temperature sent.");
    }

    // if publish fails try again
    else {
        // error msg
        Serial.println("Temperature failed to send! Reconnecting to Broker for retry.");
        // reconnect using defined variables at beginning of program
        client.connect(clientID, mqtt_user, mqtt_pass);
        delay(10);  // delay ensures client.publish wont interfere with client.connect call
        client.publish(temp_topic, String(_temp).c_str());
    }

    // publish humidity topic
    if (client.publish(hum_topic, String(_hum).c_str())) {
        Serial.println("Humidity sent.");
    }

    // try again if failed
    else {
        Serial.println("Humidity failed to send. Reconnecting to Broker for retry.");
        client.connect(clientID, mqtt_user, mqtt_pass);
        delay(10);
        client.publish(hum_topic, String(_hum).c_str());
    }

    // publish pressure
    if (client.publish(press_topic, String(_press).c_str())) {
        Serial.println("Pressure Sent.");
    }

    else {
        Serial.println("Pressure failed to send. Reconnecting to Broker for retry.");
        client.connect(clientID, mqtt_user, mqtt_pass);
        delay(10);
        client.publish(press_topic, String(_press).c_str());
    }

    // publish altitude topic
    if (client.publish(alt_topic, String(_alt).c_str())) {
        Serial.println("Altitude Sent.");
    }

    else {
        Serial.println("Altitude failed to send. Reconnecting to Broker for retry.");
        client.connect(clientID, mqtt_user, mqtt_pass);
        delay(10);
        client.publish(alt_topic, String(_alt).c_str());
    }

    // client.disconnect();
    delay(1000 * 15); // print new vals every 15 seconds  
}
