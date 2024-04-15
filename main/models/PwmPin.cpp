#include "PwmPin.h"

// Public methods
PwmPin::PwmPin(int gpioNum, ledc_channel_t channelNum){
    _gpioNum = gpioNum;
    _channelNum = channelNum;
    PwmTimer::setUpTimer();
};

void PwmPin::startPwm(){
    ledc_channel_config_t chan = _getChannel();
    ESP_ERROR_CHECK(ledc_channel_config(&chan));
}

void PwmPin::setDuty(float duty){
    int dutyInt = (int)(duty * ((1 << PWM_DUTY_RESOLUTION) - 1));
    ledc_set_duty(PWM_TIMER_MODE, _channelNum, dutyInt);
    ledc_update_duty(PWM_TIMER_MODE, _channelNum);
};

// Private methods
ledc_channel_config_t PwmPin::_getChannel(){
        ledc_channel_config_t ledc_channel = {
        .gpio_num       = _gpioNum,
        .speed_mode     = PWM_TIMER_MODE,
        .channel        = _channelNum,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = PWM_TIMER_NUM,
        .duty           = 0, 
        .hpoint         = 0,
        .flags          = {
            .output_invert = 0,
        }
    };
    return ledc_channel;
};

