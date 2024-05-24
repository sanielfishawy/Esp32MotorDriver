#include "PwmPairs.h"

bool PwmPairs::_isSetup = false;
bool PwmPairs::_isStarted = false;
float PwmPairs::_phaseOffsetRadB = 2.0 * M_PI / 3.0;
float PwmPairs::_phaseOffsetRadC = 2.0 * M_PI * 2.0 / 3.0;

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
    _pairA.setActive();
    _pairB.setActive();
    _pairC.setActive();
}

void PwmPairs::setFloat(){
    _pairA.setFloat();
    _pairB.setFloat();
    _pairC.setFloat();
}

bool PwmPairs::getIsActive(){
    return _pairA.getIsActive() || _pairB.getIsActive() || _pairC.getIsActive();
}

bool PwmPairs::getIsFloating(){
    return _pairA.getIsFloating() && _pairB.getIsFloating() && _pairC.getIsFloating();
}

void PwmPairs::handlePwmInterrupt(){
    float dutyA = WaveformGen::getDuty(0.0);
    float dutyB = WaveformGen::getDuty(_phaseOffsetRadB);
    float dutyC = WaveformGen::getDuty(_phaseOffsetRadC);
    setPairADuty(dutyA);
    setPairBDuty(dutyB);
    setPairCDuty(dutyC);
}