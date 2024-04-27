#include "PwmPairs.h"

bool PwmPairs::_isSetup = false;
bool PwmPairs::_isStarted = false;

PwmPair PwmPairs::_pairA(
    PWM_A_HIGH_GPIO_NUM,
    PWM_A_HIGH_CHANNEL_NUM,
    PWM_A_LOW_GPIO_NUM,
    PWM_A_LOW_CHANNEL_NUM,
    PWM_A_ADC_CHANNEL_NUM,
    PWM_A_PHASE_OFFSET_RAD,
    true);

PwmPair PwmPairs::_pairB(
    PWM_B_HIGH_GPIO_NUM,
    PWM_B_HIGH_CHANNEL_NUM,
    PWM_B_LOW_GPIO_NUM,
    PWM_B_LOW_CHANNEL_NUM,
    PWM_B_ADC_CHANNEL_NUM,
    PWM_B_FWD_PHASE_OFFSET_RAD,
    false);

PwmPair PwmPairs::_pairC(
    PWM_C_HIGH_GPIO_NUM,
    PWM_C_HIGH_CHANNEL_NUM,
    PWM_C_LOW_GPIO_NUM,
    PWM_C_LOW_CHANNEL_NUM,
    PWM_C_ADC_CHANNEL_NUM,
    PWM_C_FWD_PHASE_OFFSET_RAD,
    false);

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

int PwmPairs::readRawAdcA(){
    return _pairA.readRawAdc();
}

int PwmPairs::readRawAdcB(){
    return _pairB.readRawAdc();
}

int PwmPairs::readRawAdcC(){
    return _pairC.readRawAdc();
}

void PwmPairs::handlePwmInterrupt(){
    _pairA.handlePwmInterrupt();
    // _pairB.handlePwmInterrupt();
    // _pairC.handlePwmInterrupt();
}