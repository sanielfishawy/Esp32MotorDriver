#include "PwmTimer.h"

bool PwmTimer::_isSetup = false;

void PwmTimer::setUpTimer(){
    if (_isSetup) return;
    
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = PWM_TIMER_MODE,
        .duty_resolution  = PWM_DUTY_RESOLUTION,
        .timer_num        = PWM_TIMER_NUM,
        .freq_hz          = PWM_FREQ,  
        .clk_cfg          = LEDC_USE_APB_CLK, 
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    _isSetup = true;
};