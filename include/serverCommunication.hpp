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

    elapsedMillis _timeMetrics = 0;
    unsigned long _samplingDelayMetrics = 200;

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

    // printPacket takes a char array and send it to the serial port prepended by two bytes that tells its length
    void printPacket(char* packet, uint16_t byteCount);
};