#include "setup.h"

#ifdef __cplusplus
extern "C" {
#endif

// Methods that can be called from C
extern void setup(){
}

#ifdef __cplusplus
}
#endif

void _runPwm(){
    PwmInterruptPin::setup();
    PwmPairs* pwmPairs = PwmPairs::getInstance();
    pwmPairs->startPwm();
    PwmInterruptPin::startPwm();
}

void _testAdc(){
    Adc::setup();
    while(1){
        int r[3];
        float v[3];

        int64_t start_time = esp_timer_get_time();
        r[0] = Adc::readRaw(ADC_CHANNEL_0);
        r[1] = Adc::readRaw(ADC_CHANNEL_1);
        r[2] = Adc::readRaw(ADC_CHANNEL_2);
        v[0] = Adc::readVoltage(ADC_CHANNEL_0);
        v[1] = Adc::readVoltage(ADC_CHANNEL_1);
        v[2] = Adc::readVoltage(ADC_CHANNEL_2);
        int64_t end_time = esp_timer_get_time();

        int64_t duration = end_time - start_time;
        ESP_LOGI("VOLT", "0: %f %d", v[0], r[0]);
        ESP_LOGI("VOLT", "1: %f %d", v[1], r[1]);
        ESP_LOGI("VOLT", "2: %f %d", v[2], r[2]);
        ESP_LOGI("TIMER", "Task duration: %lld microseconds", duration);

        vTaskDelay(pdMS_TO_TICKS(1000));  // 1000 ms delay
    }
}
