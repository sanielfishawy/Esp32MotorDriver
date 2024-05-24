#pragma once

#include "math.h"
#include "esp_log.h"
#include "esp_task_wdt.h"
#include "esp_timer.h"

#include "PwmPin.h"
#include "ChargePump.h"
#include "FastLog.h"

#define PWM_PAIR_TAG "PwmPair: "

#ifdef __cplusplus
class PwmPair {
    public:
        PwmPair(gpio_num_t highGpioNum, 
                ledc_channel_t highChannelNum, 
                gpio_num_t lowGpioNum, 
                ledc_channel_t lowChannelNum
                );
        void startPwm();
        void setDuty(float duty);
        void setActive();
        void setFloat();
        bool getIsActive();
        bool getIsFloating();
    
    private:
        ChargePump _chargePump;
        gpio_num_t _highGpioNum;
        ledc_channel_t _highChannelNum;
        gpio_num_t _lowGpioNum;
        ledc_channel_t _lowChannelNum;
        PwmPin _highPin;
        PwmPin _lowPin;
        adc_channel_t _adcChan;
        bool _handleChargePump();
        void _setDuty(float duty);
        bool _isActive;
};

#endif // __cplusplus
