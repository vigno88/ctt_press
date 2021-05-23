#include "serverCommunication.hpp"

ServerCommunication::ServerCommunication(CttPress* press) : _press(press) {}

void ServerCommunication::run() {
     if(Serial1.available()) {
        uint16_t length = getLengthPacket();
        char buffer[length];
        Serial1.readBytes(buffer, length);
        processPacket(buffer, length);
    }
}

uint16_t ServerCommunication::getLengthPacket() {
    char buffer[2];
    Serial1.readBytes(buffer, 2);
    uint16_t value = 0;
    memcpy(&value, buffer, sizeof value);
    return value;
}

void ServerCommunication::processPacket(char* package, uint16_t length) {
    StaticJsonDocument<800> doc;
    deserializeMsgPack(doc, package, length);
    if(doc["type"] == 1) {
        processCommand(doc);
    }
    if(doc["type"] == 2) {
        processsParameter(doc);
    }
}

void ServerCommunication::processCommand(JsonDocument& doc) {

}

void ServerCommunication::processsParameter(JsonDocument& doc) {
    
}