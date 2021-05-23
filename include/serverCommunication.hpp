#pragma once
#include <Arduino.h>
#include "ArduinoJson.h"
#include "cttPress.hpp"

const int stringLength = 30;

class ServerCommunication {
public:
    ServerCommunication(CttPress* press);
    void run();

    void sendEvent(char* name, char* payload);

private:
    CttPress* _press;

    // Get the length of the next package
    uint16_t getLengthPacket();
    // Process the received package
    void processPacket(char* package, uint16_t length);
    // Process a command package
    void processCommand(JsonDocument& doc);
    // Process a parameter package
    void processsParameter(JsonDocument& doc);

    // sendMetrics will collect all the metrics, serialize them and send them over serial
    void sendMetrics();




    // // To parse the incoming packet, deserialize the msgpack json
    // void parsePacket(char* packet, int length);
    // // To parse a parameter packet
    // void parseParameter(char* arg);
    // // To parse a command packet
    // void parseCommand(ch)

    // void parsePiston(char* arg);
    // void parseWater(char* arg);
};