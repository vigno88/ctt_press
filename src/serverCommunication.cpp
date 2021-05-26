#include "serverCommunication.hpp"

ServerCommunication::ServerCommunication(CttPress* press) : _press(press) {}

void ServerCommunication::run() {
    if(Serial.available()) {
        char temp = Serial.read();
        if(temp == 'u') {
            _press->motor.MoveUp();
        }
        if(temp == 's') {
            _press->motor.StopMove();
        }
        if(temp == 'd') {
            _press->motor.MoveDown();
        }
    }
    if(Serial1.available()) {
        uint16_t length = getLengthPacket();
        char buffer[length];
        Serial1.readBytes(buffer, length);
        processPacket(buffer, length);
    }
    if(_timeMetrics >= _samplingDelayMetrics) {
        sendMetrics();
        _timeMetrics = 0;
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
    const char* name = doc["name"];
    // Motor Command
    if(strcmp(name, "mDown") == 0) {
      _press->motor.MoveDown();  
    } else if(strcmp(name, "mUp") == 0) {
      _press->motor.MoveUp();
    } else if(strcmp(name, "mStop") == 0) {
        _press->motor.StopMove();
    }

}

void ServerCommunication::processsParameter(JsonDocument& doc) {
    
}

void ServerCommunication::sendMetrics() {
    StaticJsonDocument<800> doc;
    doc["type"] = 4;
    // JsonArray array = doc.createNestedArray("metrics");
    // JsonObject object;
    // object["temp1"] = _press->thermo1.getTemperature();
    // array.add(object);
    // doc["metrics"][0]["temp1"] = _press->thermo1.getTemperature();
    // doc["metrics"][1]["temp2"] = _press->thermo2.getTemperature();
    // doc["metrics"][2]["load"] = _press->loadCell.getWeight();

    char* payload[800];
    int numBytes = serializeMsgPack(doc, payload, 800);
    for(int i = 0; i < numBytes; i++) {
        Serial.print(payload[i]);
    }
}