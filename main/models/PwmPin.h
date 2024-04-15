#include "driver/ledc.h"
#include "esp_err.h"
#include "appConfig.h"
#include "PwmTimer.h"

#ifndef PWM_PIN_H
#define PWM_PIN_H

#define PWM_PIN_TAG "PwmPin: "

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
