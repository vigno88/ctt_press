#include "motorController.hpp"

MotorController::MotorController(Motor* motor, LoadCell* loadcell,int pin_limit){
    _motor = motor;
    _loadCell = loadcell;
    _state = StateController::C_IDLE;

    _goalPoint = 0;
    _currentPoint = _loadCell->getWeight();
    _output = 0;
    _kp = 0.5;
    _ki = 0.0;
    _kd = 0.0;
    isRunning = false;
    _pid = new PID(&_currentPoint, &_output, &_goalPoint,_kp, _ki, _kd, DIRECT);
    _pid->SetOutputLimits(-100,100);
    //turn the PID on
    _pid->SetMode(AUTOMATIC);
    _pid->SetSampleTime(sampleTime);
    pin_limit_switch = pin_limit;

}

void MotorController::setTo(double weight) {
    _goalPoint = weight;
    // goalWeight = weight;
    isRunning = true;
}

void MotorController::stop() {
    isRunning = false;
    // if(_pid != nullptr) {
    //     delete _pid;
    // }
    // _pid = nullptr;
}

void MotorController::start() {
    isRunning = true;
     if(_pid != nullptr) {
        delete _pid;
    }
    _pid = new PID(&_currentPoint, &_output, &_goalPoint,_kp, _ki, _kd, DIRECT);
    _pid->SetOutputLimits(-100,100);
    //turn the PID on
    _pid->SetMode(AUTOMATIC);
    _pid->SetSampleTime(sampleTime);
}
void MotorController::run() {
    // if(_motor->_state != StateMotor::MOVING_DOWN) {
        // _motor->run();
    // } else 
    if(_motor->_state == StateMotor::MOVING_DOWN && (_loadCell->getWeight() < maxLoad) ||
       _motor->_state == StateMotor::IDLE ||
       _motor->_state == StateMotor::MOVING_UP && (digitalRead(pin_limit_switch) == LOW)) {
        _motor->run();
    } 
    // else if(_motor->_state == StateMotor::MOVING_UP && (digitalRead(pin_limit_switch) == LOW)){
        // _motor->run();
    // }
    if(isRunning) {
         // Get the current weight on load cell
        _currentPoint = _loadCell->getWeight();
        if(_currentPoint < 0) {
            _currentPoint = 0;
        }
        if(_currentPoint == _goalPoint) {
            _state = StateController::IS_IN_RANGE;
        } else if(_currentPoint <= _goalPoint) {
            _state = StateController::GOING_DOWN;
            // _pid->SetControllerDirection(DIRECT);
        } else if (_currentPoint > _goalPoint) {
            _state = StateController::GOING_UP;
            // _pid->SetControllerDirection(REVERSE);
        }
        _pid->Compute();
        currentDelay = getDelay();

        if(timerPulse >= currentDelay && _state != StateController::IS_IN_RANGE) {
            if(_state == StateController::GOING_DOWN  && _currentPoint < maxLoad) {
                _motor->sendSingleStepDown();
                timerPulse = 0;
            } else if(_state == StateController::GOING_UP && digitalRead(pin_limit_switch) == LOW) {
                _motor->sendSingleStepUp();
                timerPulse = 0;
            }
        }
    }
}

long MotorController::getDelay() {
    // The delay for the controller is (1 sec/(pidOut * stepMultiplier)) -> ms/step
    return 1000.0/(abs(_output)*_stepMultiplier);
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
    sampleTime = t;
}

void MotorController::setStepMultiplier(double m) {
    _stepMultiplier = m;
}
// void MotorController::setDurabilityConstant(double c) {
//     // c is normalized over 1 and we need our durability constant to be "normalized" over 10
//     durabilityConstant = c*10;
// }

void MotorController::MoveDown() {
    if( _loadCell->getWeight() < maxLoad)
        _motor->MoveDown();
}
void MotorController::MoveDownSlow() {
    if( _loadCell->getWeight() < maxLoad)
        _motor->MoveDownSlow();
}
void MotorController::MoveUp() {
    if(digitalRead(pin_limit_switch) == LOW)
        _motor->MoveUp();
}
void MotorController::MoveUpSlow(){
    if(digitalRead(pin_limit_switch) == LOW)
        _motor->MoveUpSlow();
}