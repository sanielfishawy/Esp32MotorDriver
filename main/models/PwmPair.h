#pragma once

#include "esp_log.h"
#include "PwmPin.h"
#include "Adc.h"
#include "Pid.h"
#include "WaveformGen.h"
#include "FastLog.h"

#define PWM_PAIR_TAG "PwmPair: "

#ifdef __cplusplus
class PwmPair {
    public:
        PwmPair(gpio_num_t highGpioNum, 
                ledc_channel_t highChannelNum, 
                gpio_num_t lowGpioNum, 
                ledc_channel_t lowChannelNum,
                adc_channel_t adcChan,
                float phaseOffsetRad,
                bool enableLog);
        void startPwm();
        void setDuty(float duty);
        void handlePwmInterrupt();
        int  readRawAdc();
    
    private:
        PID _pid;
        float _phaseOffsetRad;
        gpio_num_t _highGpioNum;
        ledc_channel_t _highChannelNum;
        gpio_num_t _lowGpioNum;
        ledc_channel_t _lowChannelNum;
        PwmPin _highPin;
        PwmPin _lowPin;
        adc_channel_t _adcChan;
        bool _enableLog;
};

#endif // __cplusplus
