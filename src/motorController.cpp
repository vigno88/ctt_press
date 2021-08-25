#include "motorController.hpp"

MotorController::MotorController(Motor* motor, LoadCell* loadcell){
    _motor = motor;
    _loadCell = loadcell;
    _state = StateController::C_IDLE;

    _goalPoint = 0;
    _currentPoint = _loadCell->getWeight();
    _output = 0;
    _kp = 0;
    _ki = 0;
    _kd = 0;
    isRunning = false;
    _pid = new PID(&_currentPoint, &_output, &_goalPoint,_kp, _ki, _kd, P_ON_M, DIRECT);
    _pid->SetOutputLimits(-100,100);
    //turn the PID on
    _pid->SetMode(AUTOMATIC);
}

void MotorController::setTo(double weight) {
    _goalPoint = weight;
    // goalWeight = weight;
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
         // Get the current weight on load cell
        _currentPoint = _loadCell->getWeight();
        if(_currentPoint < 0) {
            _currentPoint = 0;
        }
        _pid->Compute();

        // // Get the current weight on load cell
        // float currentWeight = _loadCell->getWeight();
        // if(currentWeight < 0) {
        //     currentWeight = 0;
        // }

        // Compute the new delay
        // double delta = goalWeight - currentWeight;
        // double delta = _goalPoint - _currentPoint;
        // if(_state != StateController::IS_IN_RANGE) {
        //     if(delta <= 0.01 && delta >= -0.01){
        //         _state = StateController::IS_IN_RANGE;
        //     } else if(delta > 0.01){
        //         // Add weight until in range
        //         // currentDelay = getDelay(delta);
        //         currentDelay = getDelay();
        //         _state = StateController::GOING_DOWN;   
        //     } else if(delta < -0.01) {
        //         // Remove weight until in range
        //         // currentDelay = getDelay(delta);
        //         currentDelay = getDelay();
        //         _state = StateController::GOING_UP;
        //     }
        // } else{
        //     // If the weight is in range but it cross a threshold, start ajusting again
        //     if(delta > 0.1) {
        //         // Add weight
        //         // currentDelay = getDelay(delta);
        //         currentDelay = getDelay();
        //         _state = StateController::GOING_DOWN;    
        //     } else if(delta < -0.1) {
        //         // currentDelay = getDelay(delta);
        //         currentDelay = getDelay();
        //         _state = StateController::GOING_UP;   
        //     }
        // }


        if(_output == 0) {
            _state = StateController::IS_IN_RANGE;
        } else if (_output < 0) {
            _state = StateController::GOING_UP;
        } else {
            _state = StateController::GOING_DOWN;
        }
        currentDelay = getDelay();

        if(timerPulse >= currentDelay && _state != StateController::IS_IN_RANGE) {
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

// long MotorController::getDelay(float delta) {
//     // Normalized
//     float norm = 1-(abs(delta)/goalWeight);
//     long delay = (long)(1/(10-(10*norm)) * minimumDelayMicros * durabilityConstant);
//     if (delay < minimumDelayMicros) {
//         return minimumDelayMicros;
//     } else {
//         return delay;
//     }
// }

long MotorController::getDelay() {
    // The delay for the controller is (1 second/(pidOut * stepMultiplier)) -> sec/step
    // 1 seconds is 1000 ms
    return 1000.0/(_output*_stepMultiplier);
}

void MotorController::setKp(double k) {
    _kp = k;
    _pid->SetTunings(_kp,_ki, _kd);
}

void MotorController::setKi(double k) {
    _ki = k;
    _pid->SetTunings(_kp,_ki, _kd);
}

void MotorController::setKd(double k) {
    _kd = k;
    _pid->SetTunings(_kp,_ki, _kd);
}

void MotorController::setSampleTime(int t) {
    _pid->SetSampleTime(t);
}

void MotorController::setStepMultiplier(int m) {
    _stepMultiplier = m;
}
// void MotorController::setDurabilityConstant(double c) {
//     // c is normalized over 1 and we need our durability constant to be "normalized" over 10
//     durabilityConstant = c*10;
// }