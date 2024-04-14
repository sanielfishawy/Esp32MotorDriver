#ifndef PWM_PAIR_H
#define PWM_PAIR_H

#include "PwmPin.h"

#ifdef __cplusplus
extern "C" {
#endif

// C accessible functions
void PWM_PAIR_setup();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

class PwmPair {
    public:
        PwmPair(int highGpioNum, 
                ledc_channel_t highChannelNum, 
                int lowGpioNum, 
                ledc_channel_t lowChannelNum);
        void startPwm();
        void setDuty(float duty);
    
    private:
        int _highGpioNum;
        ledc_channel_t _highChannelNum;
        int _lowGpioNum;
        ledc_channel_t _lowChannelNum;
        PwmPin _highPin;
        PwmPin _lowPin;
};
#endif

#endif // PWM_PAIR_H
