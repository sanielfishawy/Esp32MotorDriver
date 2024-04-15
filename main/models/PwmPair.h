#include "esp_log.h"
#include "PwmPin.h"

#ifndef PWM_PAIR_H
#define PWM_PAIR_H

#define PWM_PAIR_TAG "PwmPair: "

#ifdef __cplusplus
class PwmPair {
    public:
        PwmPair(int highGpioNum, 
                ledc_channel_t highChannelNum, 
                int lowGpioNum, 
                ledc_channel_t lowChannelNum);
        void startPwm();
        void setDuty(float duty);
        void handlePwmInterrupt();
    
    private:
        int _highGpioNum;
        ledc_channel_t _highChannelNum;
        int _lowGpioNum;
        ledc_channel_t _lowChannelNum;
        PwmPin _highPin;
        PwmPin _lowPin;
};

#endif // __cplusplus

#endif // PWM_PAIR_H
