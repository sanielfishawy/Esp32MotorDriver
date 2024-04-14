#ifndef PWM_PIN_H
#define PWM_PIN_H

#include "driver/ledc.h"
#include "esp_err.h"
#include "PwmTimer.h"

#ifdef __cplusplus

class PwmPin {
    public:
        PwmPin(int gpioNum, ledc_channel_t channelNum);
        void startPwm();
        void setDuty(float duty);
    
    private:
        int _gpioNum;
        ledc_channel_t _channelNum;
        ledc_channel_config_t _getChannel();
};
#endif

#endif // PWM_PIN_H
