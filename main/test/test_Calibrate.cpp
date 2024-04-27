extern "C" {
    #include "unity.h"
}

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../models/Adc.h"

extern "C" {

    static void test_calibrate() {
        Adc::setup();
        int rawA, rawB, rawC;
        while(1){
            rawA = Adc::readRaw(PWM_A_ADC_CHANNEL_NUM);
            rawB = Adc::readRaw(PWM_B_ADC_CHANNEL_NUM);
            rawC = Adc::readRaw(PWM_C_ADC_CHANNEL_NUM);
            ESP_LOGI("test_calibrate", "A:%d B:%d C:%d", rawA, rawB, rawC);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }

    void run_test_Calibrate(){
        UNITY_BEGIN();
        RUN_TEST(test_calibrate);
        UNITY_END();
    }

}