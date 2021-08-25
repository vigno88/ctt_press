#include "serverCommunication.hpp"

ServerCommunication::ServerCommunication(CttPress* press) : _press(press) {}

void ServerCommunication::run() {
    if(Serial1.available()) {
        uint16_t length = getLengthPacket();
        char buffer[length];
        Serial1.readBytes(buffer, length);
        processPacket(buffer, length);
    }
    if(_timeMetrics >= _samplingDelayMetrics) {
        sendMetrics();
        // _press->tcTop.print();
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
    int t = (int)doc["t"];
    if(t == 1) {
        processCommand(doc);
    }
    if(t == 2) {
        processsParameter(doc);
    }
}

void ServerCommunication::processCommand(JsonDocument& doc) {
    const char* name = doc["n"];
    const char* payload = doc["a"];
    // Motor Command
    if(strcmp(name, "motor") == 0) {
        if(strcmp(payload, "mD") == 0) {
            _press->motor.MoveDown();  
        } else if(strcmp(payload, "mU") == 0) {
            _press->motor.MoveUp();
        } else if(strcmp(payload, "mS") == 0) {
            _press->motor.StopMove();
        } else if(strcmp(payload, "mDs") == 0) {
            _press->motor.MoveDownSlow(); 
        } else if(strcmp(payload, "mUs") == 0) {
            _press->motor.MoveUpSlow();
        }
    } else if(strcmp(name, "distance") == 0) {
        if(strcmp(payload, "tare") == 0) {
            _press->motor.tareDistance();  
        }
    } else if(strcmp(name, "weight") == 0) {
        if(strcmp(payload, "tare") == 0) {
            _press->loadCell.tare();  
        }
    } else if(strcmp(name, "setT") == 0) {
         if(strcmp(payload, "so") == 0) {
            _press->tcTop.stop();
            _press->tcBottom.stop();
        } else if (strcmp(payload, "st") == 0){ 
            _press->tcTop.start();
            _press->tcBottom.start();
        } else {
            double v = atof(payload);
            _press->tcTop.setGoal(v);
            _press->tcBottom.setGoal(v);
        }
    } else if(strcmp(name, "setW") == 0) {
        if(strcmp(payload, "so") == 0) {
            _press->controller.stop();
        } else if (strcmp(payload, "st") == 0){ 
            _press->controller.start();
        } else {
            double v = atof(payload);
            _press->controller.setTo(v);
        }
    }

}

void ServerCommunication::processsParameter(JsonDocument& doc) {
    JsonObject o = doc["ps"].as<JsonArray>()[0];
    for (JsonPair kv : o) {
        const char* key = kv.key().c_str();
        Serial.printf("%s: %f\n", key,kv.value().as<double>());
        double v = kv.value().as<double>();
        if(strcmp(key, "pTop") == 0) {
            _press->tcTop.setKp(v);
        } else if(strcmp(key, "iTop") == 0) {
            _press->tcTop.setKi(v);
        } else if(strcmp(key, "dTop") == 0) {
            _press->tcTop.setKd(v);
        } else if(strcmp(key, "pBot") == 0) {
            _press->tcBottom.setKp(v);
        } else if(strcmp(key, "iBot") == 0) {
            _press->tcBottom.setKi(v);
        } else if(strcmp(key, "dTop") == 0) {
            _press->tcBottom.setKd(v);
        } else if(strcmp(key, "hC") == 0) {
            _press->controller.setDurabilityConstant(v);
        } else if(strcmp(key, "lcF") == 0) {
            _press->loadCell.setScalingFactor(v);
        }
    }
}

void ServerCommunication::sendMetrics() {
    StaticJsonDocument<800> doc;
    doc["t"] = 4;
    doc["ms"][0]["tT"] = _press->thermoTop.getTemperature();
    doc["ms"][1]["tB"] = _press->thermoBottom.getTemperature();
    doc["ms"][2]["w"] =  _press->loadCell.getWeight();
    doc["ms"][3]["d"] = _press->motor.getDistanceTravelled();
    char payload[800];
    uint16_t numBytes = serializeMsgPack(doc, payload, 800);
    // uint16_t numBytes = serializeJsonPretty(doc, payload, 800);
    printPacket(payload, numBytes);
}

void ServerCommunication::printPacket(char* packet, uint16_t byteCount){
    char length[2];
    memcpy(length, &byteCount, 2);
    Serial1.print(length[0]);
    Serial1.print(length[1]);
    for(int i = 0; i < byteCount; i++) {
        Serial1.print(packet[i]);
    }
}