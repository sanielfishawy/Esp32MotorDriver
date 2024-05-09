#include "PwmPairs.h"

bool PwmPairs::_isSetup = false;
bool PwmPairs::_isStarted = false;
float PwmPairs::_phaseOffsetRadB = M_2_PI / 3.0;
float PwmPairs::_phaseOffsetRadC = M_2_PI * 2.0 / 3.0;
bool PwmPairs::_isActive = false;

PwmPair PwmPairs::_pairA(
    PWM_A_HIGH_GPIO_NUM,
    PWM_A_HIGH_CHANNEL_NUM,
    PWM_A_LOW_GPIO_NUM,
    PWM_A_LOW_CHANNEL_NUM
    );

PwmPair PwmPairs::_pairB(
    PWM_B_HIGH_GPIO_NUM,
    PWM_B_HIGH_CHANNEL_NUM,
    PWM_B_LOW_GPIO_NUM,
    PWM_B_LOW_CHANNEL_NUM
    );

PwmPair PwmPairs::_pairC(
    PWM_C_HIGH_GPIO_NUM,
    PWM_C_HIGH_CHANNEL_NUM,
    PWM_C_LOW_GPIO_NUM,
    PWM_C_LOW_CHANNEL_NUM
    );

void PwmPairs::setup(){
    if (_isSetup) return; 

    PwmInterruptPin::setup();
    _isSetup = true;
}

void PwmPairs::startPwm(){
    if (_isStarted) return;

    _pairA.startPwm();
    _pairB.startPwm();
    _pairC.startPwm();

    PwmInterruptPin::startPwm();
    _isStarted = true;
}

void PwmPairs::setPairADuty(float duty){
    _pairA.setDuty(duty);
}

void PwmPairs::setPairBDuty(float duty){
    _pairB.setDuty(duty);
}

void PwmPairs::setPairCDuty(float duty){
    _pairC.setDuty(duty);
}

void PwmPairs::setActive(){
    _isActive = true;
}

void PwmPairs::setFloat(){
    _isActive = false;
}

bool PwmPairs::getIsActive(){
    return _isActive;
}

bool PwmPairs::getIsFloating(){
    return !_isActive;
}

void PwmPairs::handlePwmInterrupt(){
    if (!_isActive) {
        setPairADuty(0.0);
        setPairBDuty(0.0);
        setPairCDuty(0.0);
        return;
    }
    float dutyA = WaveformGen::getDuty(0.0);
    float dutyB = WaveformGen::getDuty(_phaseOffsetRadB);
    float dutyC = WaveformGen::getDuty(_phaseOffsetRadC);
    setPairADuty(dutyA);
    setPairBDuty(dutyB);
    setPairCDuty(dutyC);
}