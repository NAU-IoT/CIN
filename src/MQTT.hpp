/*
 * source file used to test MQTT data transmission
 * with C++
 */

#ifndef MQTT_hpp
#define MQTT_hpp

class MQTT {
    public:
        MQTT(int BMEaddr);
        void connect_MQTT();
        void publish_MQTT();
};

#endif
