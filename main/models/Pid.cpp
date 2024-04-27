#include "Pid.h"


PID::PID():
    _integrator(new Integrator()),
    _derivator(new Derivator()),
    _kP(PID_DEFAULT_KP),
    _kI(PID_DEFAULT_KI),
    _kD(PID_DEFAULT_KD) {
}

float PID::calculate(int setPoint, int actPoint){
    int error = setPoint - actPoint;
    float p = _kP * error;
    float i = _kI * _integrator->calculate(error);
    float d = _kD * _derivator->calculate(error);
    return _clamp(p + i + d);
}

float PID::_clamp(float value){
    if(value > 1.0){
        return 1.0;
    } else if(value < -1.0){
        return -1.0;
    } else {
        return value;
    }
}

void PID::setKp(float kP){
    _kP = kP;
}

void PID::setKi(float kI){
    _kI = kI;
}

void PID::setKd(float kD){
    _kD = kD;
}

float PID::getKp(){
    return _kP;
}

float PID::getKi(){
    return _kI;
}

float PID::getKd(){
    return _kD;
}

