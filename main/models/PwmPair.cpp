#include "PwmPair.h"

PwmPair::PwmPair(   gpio_num_t highGpioNum,
                    ledc_channel_t highChannelNum,
                    gpio_num_t lowGpioNum,
                    ledc_channel_t lowChannelNum
                    ): 
    _chargePump(),
    _highGpioNum(highGpioNum),
    _highChannelNum(highChannelNum),
    _lowGpioNum(lowGpioNum),
    _lowChannelNum(lowChannelNum),
    _highPin(highGpioNum, highChannelNum),  
    _lowPin(lowGpioNum, lowChannelNum)
{}

void PwmPair::startPwm(){
    _highPin.startPwm();
    _lowPin.startPwm();
}

void PwmPair::setDuty(float duty){
    if (!_handleChargePump()){
        _setDuty(duty);
    }
}

void PwmPair::_setDuty(float duty){
    if (duty < -1.0) duty = -1.0;
    if (duty > 1.0) duty = 1.0;

    if (duty > 0){
        _highPin.setDuty(duty);
        _lowPin.setDuty(0);
    } else {
        _highPin.setDuty(0);
        _lowPin.setDuty(-duty);
    }

    if (duty < - CP_CHARGE_TIME_IN_PWM_DUTY_CYCLE) _chargePump.reset();
}

bool PwmPair::_handleChargePump(){
    float duty = _chargePump.getDuty();
    if(duty == 0.0) return false;
    _setDuty(duty);
    FastLog::set(duty);
    return true;
}