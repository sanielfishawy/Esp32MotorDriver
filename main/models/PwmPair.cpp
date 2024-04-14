#include "PwmPair.h"
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif
// Methods that can be called from C
extern void PWM_PAIR_setup(){
    PwmPair p1(5, LEDC_CHANNEL_0, 6, LEDC_CHANNEL_1);
    p1.startPwm();
    p1.setDuty(0.5);
}
#ifdef __cplusplus
}
#endif

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
    _highPin.setDuty(duty);
    _lowPin.setDuty(duty / 2.0);
};


// Private methods