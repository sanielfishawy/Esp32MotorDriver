#include "PwmPair.h"
#include <iostream>

// Public methods
PwmPair::PwmPair(int highGpioNum, ledc_channel_t highChannelNum, int lowGpioNum, ledc_channel_t lowChannelNum) : 
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
    _highPin.setDuty(0.5);
    _lowPin.setDuty(0.5);
    return;

    if (duty < -1) duty = -1;
    if (duty > 1) duty = 1;

    if (duty > 0){
        _highPin.setDuty(duty);
        _lowPin.setDuty(0);
    } else {
        _highPin.setDuty(0);
        _lowPin.setDuty(-duty);
    }
};

void PwmPair::handlePwmInterrupt(){
    static bool toggle;
    if(toggle) setDuty(0.5);
    else setDuty(-0.5);
    toggle = !toggle;
}


// Private methods