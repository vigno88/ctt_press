#include "motorController.hpp"

MotorController::MotorController(Motor* motor, LoadCell* loadcell){
    _motor = motor;
    _loadCell = loadcell;
    _state = StateController::C_IDLE;
    // timeBootUp = millis();
}

void MotorController::setTo(double weight) {
    goalWeight = weight;
    isRunning = true;
}

void MotorController::stop() {
    isRunning = false;
}

void MotorController::start() {
    isRunning = true;
}
void MotorController::run() {
    if(isRunning) {
        // Wait for loadcell bootup
        // if(_state == StateController::BOOTING_UP) {
        //     if(millis() - timeBootUp > bootupDelayMS) {
        //         _state = StateController::C_IDLE;
        //     }
        //     return;
        // }
        // Get the current weight on load cell
        float currentWeight = _loadCell->getWeight();
        if(currentWeight < 0) {
            currentWeight = 0;
        }
        // Compute the new delay
        double delta = goalWeight - currentWeight;
        if(_state != StateController::IS_IN_RANGE) {
            if(delta <= 0.01 && delta >= -0.01){
                _state = StateController::IS_IN_RANGE;
            } else if(delta > 0.01){
                // Add weight until in range
                currentDelay = getDelay(delta);
                _state = StateController::GOING_DOWN;   
            } else if(delta < -0.01) {
                // Remove weight until in range
                currentDelay = getDelay(delta);
                _state = StateController::GOING_UP;
            }
        } else{
            // If the weight is in range but it cross a threshold, start ajusting again
            if(delta > 0.1) {
                // Add weight
                currentDelay = getDelay(delta);
                _state = StateController::GOING_DOWN;    
            } else if(delta < -0.1) {
                currentDelay = getDelay(delta);
                _state = StateController::GOING_UP;   
            }
        }

        if(timerPulse > currentDelay && _state != StateController::IS_IN_RANGE) {
            if(_state == StateController::GOING_DOWN) {
                _motor->sendSingleStepDown();
                timerPulse = 0;
            } else if(_state == StateController::GOING_UP) {
                _motor->sendSingleStepUp();
                timerPulse = 0;
            }
        }
    }
}

long MotorController::getDelay(float delta) {
    // Normalized
    float norm = 1-(abs(delta)/goalWeight);
    long delay = (long)(1/(10-(10*norm)) * minimumDelayMicros * durabilityConstant);
    if (delay < minimumDelayMicros) {
        return minimumDelayMicros;
    } else {
        return delay;
    }
}

void MotorController::setDurabilityConstant(double c) {
    // c is normalized over 1 and we need our durability constant to be "normalized" over 10
    durabilityConstant = c*10;
}