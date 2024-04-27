#pragma once

#include "driver/ledc.h"
#include "esp_err.h"
#include "appConfig.h"
#include "PwmTimer.h"


#define PWM_PIN_TAG "PwmPin: "

#ifdef __cplusplus

class PwmPin {
    public:
        PwmPin(gpio_num_t gpioNum, ledc_channel_t channelNum);
        void startPwm();
        void setDuty(float duty);
    
    private:
        gpio_num_t _gpioNum;
        ledc_channel_t _channelNum;
        ledc_channel_config_t _getChannel();
};
#endif

